// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 5
// 12/5/2025
//-------------------------------------------------------
//
//  OpticalFlow.C
//
//  Implementation of optical flow computation and application
//
//-------------------------------------------------------

#include "OpticalFlow.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <omp.h>

using namespace std;

namespace starter {

    OpticalFlow::OpticalFlow() {}

    OpticalFlow::~OpticalFlow() {}

    // Convert RGB image to grayscale for flow computation
    void OpticalFlow::ConvertToGrayscale(const ImgProc& input, ImgProc& output) {
        int width = input.GetWidth();
        int height = input.GetHeight();
        
        // Single channel for grayscale
        output.clear(width, height, 1);  
        
        #pragma omp parallel for collapse(2) schedule(static)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float gray = 0.0f;
                int channels = input.GetChannels();
                
                if (channels >= 3) {
                    
                    // Standard RGB to grayscale conversion
                    float r = input.GetPixel(x, y, 0);
                    float g = input.GetPixel(x, y, 1);
                    float b = input.GetPixel(x, y, 2);
                    gray = 0.299f * r + 0.587f * g + 0.114f * b;
                } else {
                    
                    // Already grayscale or single channel
                    gray = input.GetPixel(x, y, 0);
                }
                
                output.SetPixel(x, y, 0, gray);
            }
        }
    }

    // Compute gradients using Sobel operators
    void OpticalFlow::ComputeGradients(const ImgProc& image, ImgProc& Ix, ImgProc& Iy) {
        int width = image.GetWidth();
        int height = image.GetHeight();
        
        Ix.clear(width, height, 1);
        Iy.clear(width, height, 1);
        
        // Sobel operator for gradient computation
        float sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
        float sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
        
        #pragma omp parallel for collapse(2) schedule(static)
        for (int y = 1; y < height - 1; ++y) {
            for (int x = 1; x < width - 1; ++x) {
                float gx = 0.0f, gy = 0.0f;
                
                // Apply Sobel operators
                for (int j = -1; j <= 1; ++j) {
                    for (int i = -1; i <= 1; ++i) {
                        float pixel = image.GetPixel(x + i, y + j, 0);
                        gx += sobelX[j + 1][i + 1] * pixel;
                        gy += sobelY[j + 1][i + 1] * pixel;
                    }
                }

                // Normalize gradients
                Ix.SetPixel(x, y, 0, gx / 8.0f);  
                Iy.SetPixel(x, y, 0, gy / 8.0f);
            }
        }
    }

    // Compute optical flow between two frames using Lucas-Kanade method
    bool OpticalFlow::ComputeFlow(const ImgProc& frame1, const ImgProc& frame2, 
                                vector<vector<FlowVector>>& flow) {
        if (!frame1.IsLoaded() || !frame2.IsLoaded()) {
            cerr << "Error: Input frames not loaded" << endl;
            return false;
        }
        
        int width = frame1.GetWidth();
        int height = frame1.GetHeight();
        
        // Convert to grayscale
        ImgProc gray1, gray2;
        ConvertToGrayscale(frame1, gray1);
        ConvertToGrayscale(frame2, gray2);
        
        // Compute spatial gradients
        ImgProc Ix, Iy;
        ComputeGradients(gray1, Ix, Iy);
        
        // Compute temporal gradient
        ImgProc It;
        It.clear(width, height, 1);
        
        #pragma omp parallel for collapse(2) schedule(static)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float it = gray2.GetPixel(x, y, 0) - gray1.GetPixel(x, y, 0);
                It.SetPixel(x, y, 0, it);
            }
        }
        
        // Initialize flow field
        flow.resize(height);
        for (int y = 0; y < height; ++y) {
            flow[y].resize(width);
        }
        
        // Lucas-Kanade optical flow in windows
        int windowSize = 5;  // 5x5 window
        int halfWindow = windowSize / 2;
        
        cout << "Computing optical flow..." << endl;
        
        #pragma omp parallel for collapse(2) schedule(dynamic, 8)
        for (int y = halfWindow; y < height - halfWindow; ++y) {
            for (int x = halfWindow; x < width - halfWindow; ++x) {
                
                // Build matrices A and b for least squares solution
                float A11 = 0, A12 = 0, A22 = 0;
                float b1 = 0, b2 = 0;
                
                // Sum over the window
                for (int j = -halfWindow; j <= halfWindow; ++j) {
                    for (int i = -halfWindow; i <= halfWindow; ++i) {
                        float ix = Ix.GetPixel(x + i, y + j, 0);
                        float iy = Iy.GetPixel(x + i, y + j, 0);
                        float it = It.GetPixel(x + i, y + j, 0);
                        
                        A11 += ix * ix;
                        A12 += ix * iy;
                        A22 += iy * iy;
                        b1 -= ix * it;
                        b2 -= iy * it;
                    }
                }
                
                // Solve the 2x2 system using Cramer's rule
                float det = A11 * A22 - A12 * A12;
                
                if (fabs(det) > 1e-6) {  // Check for non-singular matrix
                    float u = (A22 * b1 - A12 * b2) / det;
                    float v = (A11 * b2 - A12 * b1) / det;
                    
                    // Clamp flow vectors to reasonable range
                    u = max(-10.0f, min(10.0f, u));
                    v = max(-10.0f, min(10.0f, v));
                    
                    flow[y][x] = FlowVector(u, v);
                } else {
                    flow[y][x] = FlowVector(0, 0);
                }
            }
        }
        
        cout << "Optical flow computation completed" << endl;
        return true;
    }

    // Bilinear interpolation for sub-pixel sampling
    float OpticalFlow::BilinearInterpolate(const ImgProc& image, float x, float y, int channel) {
        int width = image.GetWidth();
        int height = image.GetHeight();
        
        // Out of bounds check
        if (x < 0 || x >= width - 1 || y < 0 || y >= height - 1) {
            return 0.0f;  
        }
        
        int x0 = (int)x;
        int y0 = (int)y;
        int x1 = x0 + 1;
        int y1 = y0 + 1;
        
        float fx = x - x0;
        float fy = y - y0;
        
        float p00 = image.GetPixel(x0, y0, channel);
        float p01 = image.GetPixel(x0, y1, channel);
        float p10 = image.GetPixel(x1, y0, channel);
        float p11 = image.GetPixel(x1, y1, channel);
        
        float p0 = p00 * (1 - fx) + p10 * fx;
        float p1 = p01 * (1 - fx) + p11 * fx;
        
        return p0 * (1 - fy) + p1 * fy;
    }

    // Apply optical flow to an image (backward warping)
    bool OpticalFlow::ApplyFlow(const ImgProc& input, const vector<vector<FlowVector>>& flow, 
                                ImgProc& output) {
        if (!input.IsLoaded()) {
            cerr << "Error: Input image not loaded" << endl;
            return false;
        }
        
        int width = input.GetWidth();
        int height = input.GetHeight();
        int channels = input.GetChannels();
        
        output.clear(width, height, channels);
        
        // Apply backward warping
        #pragma omp parallel for collapse(2) schedule(static)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (y < static_cast<int>(flow.size()) && x < static_cast<int>(flow[y].size())) {
                    // Get flow vector
                    float u = flow[y][x].u;
                    float v = flow[y][x].v;
                    
                    // Backward warping: sample from previous location
                    float srcX = x - u;
                    float srcY = y - v;
                    
                    for (int c = 0; c < channels; ++c) {
                        float value = BilinearInterpolate(input, srcX, srcY, c);
                        output.SetPixel(x, y, c, value);
                    }
                } else {
                    // No flow information, copy original pixel
                    for (int c = 0; c < channels; ++c) {
                        float value = input.GetPixel(x, y, c);
                        output.SetPixel(x, y, c, value);
                    }
                }
            }
        }
        
        return true;
    }

    // Save flow field as image (for visualization)
    bool OpticalFlow::SaveFlowAsImage(const vector<vector<FlowVector>>& flow, 
                                    const string& filename, int width, int height) {
        ImgProc flowImg;
        flowImg.clear(width, height, 3);
        
        // Convert flow to color image (u -> red, v -> green)
        #pragma omp parallel for collapse(2) schedule(static)
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (y < static_cast<int>(flow.size()) && x < static_cast<int>(flow[y].size())) {
                    float u = flow[y][x].u;
                    float v = flow[y][x].v;
                    
                    // Normalize and scale flow for visualization
                    float r = (u + 5.0f) / 10.0f;  // Assuming flow range -5 to 5
                    float g = (v + 5.0f) / 10.0f;
                    float b = 0.5f;  // Constant blue component
                    
                    r = max(0.0f, min(1.0f, r));
                    g = max(0.0f, min(1.0f, g));
                    
                    flowImg.SetPixel(x, y, 0, r);
                    flowImg.SetPixel(x, y, 1, g);
                    flowImg.SetPixel(x, y, 2, b);
                } else {
                    flowImg.SetPixel(x, y, 0, 0.5f);
                    flowImg.SetPixel(x, y, 1, 0.5f);
                    flowImg.SetPixel(x, y, 2, 0.5f);
                }
            }
        }
        
        return flowImg.WriteImage(filename);
    }
}