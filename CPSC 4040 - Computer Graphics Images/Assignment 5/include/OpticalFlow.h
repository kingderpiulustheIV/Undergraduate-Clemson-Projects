// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 5
// 12/5/2025
//-------------------------------------------------------
//
//  OpticalFlow.h
//
//  Optical flow computation and application class
//
//-------------------------------------------------------

#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H

#include "ImgProc.h"
#include <vector>
#include <string>

namespace starter {

struct FlowVector {
    float u, v;  // horizontal and vertical flow components
    FlowVector() : u(0), v(0) {}
    FlowVector(float u_, float v_) : u(u_), v(v_) {}
};

class OpticalFlow {
public:
    OpticalFlow();
    ~OpticalFlow();
    
    // Compute optical flow between two frames using Lucas-Kanade method
    bool ComputeFlow(const ImgProc& frame1, const ImgProc& frame2, 
                     std::vector<std::vector<FlowVector>>& flow);
    
    // Apply optical flow to an image (backward warping)
    bool ApplyFlow(const ImgProc& input, const std::vector<std::vector<FlowVector>>& flow, 
                   ImgProc& output);
    
    // Save flow field as image (for visualization)
    bool SaveFlowAsImage(const std::vector<std::vector<FlowVector>>& flow, 
                         const std::string& filename, int width, int height);
    
private:
    // Compute gradients using Sobel operators
    void ComputeGradients(const ImgProc& image, ImgProc& Ix, ImgProc& Iy);
    
    // Convert RGB image to grayscale for flow computation
    void ConvertToGrayscale(const ImgProc& input, ImgProc& output);
    
    // Bilinear interpolation for sub-pixel sampling
    float BilinearInterpolate(const ImgProc& image, float x, float y, int channel);
};

}

#endif 