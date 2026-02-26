// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 3
// 10/23/2025
//-------------------------------------------------------
//
//  ImgProc.C
//
//  Implementation of image processing operations using
//  OpenImageIO for reading and writing images.
//
//-------------------------------------------------------

#include "ImgProc.h"
#include <OpenImageIO/imageio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <random>

using namespace OIIO;
using namespace std;

namespace starter {

    // Stencil implementation
    Stencil::Stencil(int w) : width(w), data((long)w * w, 0.0f)
    {
        if (width % 2 == 0) {
            std::cerr << "Warning: Stencil width should be odd for proper centering" << std::endl;
        }
    }

    float& Stencil::operator()(int i, int j)
    {
        return data[(long)i * width + j];
    }

    const float& Stencil::operator()(int i, int j) const
    {
        return data[(long)i * width + j];
    }

    // BoundedLinearConvolution function
    namespace img {
        void BoundedLinearConvolution(const Stencil& stencil, const ImgProc& in, ImgProc& out)
        {
            if (!in.IsLoaded()) {
                std::cerr << "Error: Input image not loaded for convolution" << std::endl;
                return;
            }
            
            int width = in.GetWidth();
            int height = in.GetHeight();
            int channels = in.GetChannels();
            
            // Clear and allocate output image
            out.clear(width, height, channels);
            
            int radius = stencil.GetRadius();
            int stencilWidth = stencil.GetWidth();
            
            std::cout << "Applying bounded linear convolution with " << stencilWidth << "x" << stencilWidth << " stencil..." << std::endl;
            
            // Apply convolution to each pixel
        #pragma omp parallel for collapse(3)
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    for (int c = 0; c < channels; ++c) {
                        float sum = 0.0f;
                        
                        // Apply stencil
                        for (int sy = 0; sy < stencilWidth; ++sy) {
                            for (int sx = 0; sx < stencilWidth; ++sx) {
                                int px = x + sx - radius;
                                int py = y + sy - radius;
                                
                                // Use safe accessor with automatic bounds checking
                                // Returns 0.0f (black) for out-of-bounds pixels
                                float pixelValue = in.GetPixelSafe(px, py, c);
                                
                                sum += stencil(sy, sx) * pixelValue;
                            }
                        }
                        
                        // Use safe setter
                        out.SetPixel(x, y, c, sum);
                    }
                }
            }
            
            std::cout << "Bounded linear convolution completed" << std::endl;
        }
        
        Stencil GenerateRandomStencil(int width)
        {
            std::cout << "Generating " << width << "x" << width << " random stencil..." << std::endl;
            
            Stencil stencil(width);
            int radius = width / 2;
            
            // Random number generator for values between -0.1 and 0.1
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(-0.1f, 0.1f);
            
            float sum = 0.0f;
            
            // Fill all non-center values with random numbers
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < width; ++j) {
                    if (i == radius && j == radius) {
                        // Skip center - will be set later
                        continue;
                    } else {
                        float val = dis(gen);
                        stencil(i, j) = val;
                        sum += val;
                    }
                }
            }
            
            // Set center value so total sum is 1
            stencil(radius, radius) = 1.0f - sum;
            
            std::cout << "Random stencil generated with center value: " << stencil(radius, radius) << std::endl;
            std::cout << "Sum of off-center Stencil values: "<< sum << std::endl;
            std::cout << "Total sum of all stencil values: " << (sum + stencil(radius, radius)) << std::endl;
            
            return stencil;
        }
    }

    // Constructor
    ImgProc::ImgProc() : width(0), height(0), channels(0), loaded(false)
    {
    }

    // Copy constructor
    ImgProc::ImgProc(const ImgProc& other) 
        : width(other.width), height(other.height), channels(other.channels), loaded(other.loaded)
    {
        if (other.pixels && loaded) {
            long size = (long)width * height * channels;
            pixels = std::unique_ptr<float[]>(new float[size]);
        #pragma omp parallel for
            for (long i = 0; i < size; ++i) {
                pixels[i] = other.pixels[i];
            }
        }
    }

    // Copy assignment operator
    ImgProc& ImgProc::operator=(const ImgProc& other)
    {
        if (this != &other) {
            width = other.width;
            height = other.height;
            channels = other.channels;
            loaded = other.loaded;
            
            if (other.pixels && loaded) {
                long size = (long)width * height * channels;
                pixels = std::unique_ptr<float[]>(new float[size]);
    #pragma omp parallel for
                for (long i = 0; i < size; ++i) {
                    pixels[i] = other.pixels[i];
                }
            } else {
                pixels.reset();
            }
        }
        return *this;
    }

    // Destructor
    ImgProc::~ImgProc()
    {
        clear();
    }

    // Read an image from file
    bool ImgProc::ReadImage(const std::string& filename)
    {
        // Open the image file
        auto inp = ImageInput::open(filename);
        if (!inp) {
            cerr << "Error: Could not open image file " << filename << endl;
            return false;
        }
        
        const ImageSpec& spec = inp->spec();
        width = spec.width;
        height = spec.height;
        channels = spec.nchannels;
        
        cout << "Reading image: " << filename << endl;
        cout << "Dimensions: " << width << "x" << height << " with " << channels << " channels" << endl;
        
        // Allocate memory for pixels
        long size = (long)width * height * channels;
        pixels = std::unique_ptr<float[]>(new float[size]);
        
        // Read the image data as floats
        bool success = inp->read_image(0, 0, 0, channels, TypeDesc::FLOAT, &pixels[0]);
        inp->close();
        
        if (success) {
            loaded = true;
            cout << "Image loaded successfully!" << endl;
        } else {
            cerr << "Error reading image data from " << filename << endl;
            loaded = false;
        }
        
        return success;
    }

    // Write an image to file
    bool ImgProc::WriteImage(const std::string& filename)
    {
        // Ensure image is loaded
        if (!loaded) {
            cerr << "Error: No image loaded to write" << endl;
            return false;
        }
        
        // Create output image
        auto out = ImageOutput::create(filename);
        if (!out) {
            cerr << "Error: Could not create output for " << filename << endl;
            return false;
        }
        
        // Define image specification
        ImageSpec spec(width, height, channels, TypeDesc::UINT8);
        if (!out->open(filename, spec)) {
            cerr << "Error: Could not open " << filename << " for writing" << endl;
            return false;
        }
        
        // Convert float data to UINT8 for writing
        long total_pixels = (long)width * height * channels;
        std::unique_ptr<unsigned char[]> byte_pixels(new unsigned char[total_pixels]);
    #pragma omp parallel for
        for (long i = 0; i < total_pixels; ++i) {
            
            // Clamp and convert float [0,1] to byte [0,255]
            float val = pixels[i];
            if (val < 0.0f) val = 0.0f;
            if (val > 1.0f) val = 1.0f;
            byte_pixels[i] = (unsigned char)(val * 255.0f);
        }

        // Write the image data
        bool success = out->write_image(TypeDesc::UINT8, &byte_pixels[0]);
        out->close();
        
        if (success) {
            cout << "Image written successfully to " << filename << endl;
        } else {
            cerr << "Error writing image to " << filename << endl;
        }
        
        return success;
    }

    // Clear the image data
    void ImgProc::clear()
    {
        pixels.reset();
        width = 0;
        height = 0;
        channels = 0;
        loaded = false;
    }

    // Clear and allocate new image data
    void ImgProc::clear(int nx, int ny, int nc)
    {
        if (nx <= 0 || ny <= 0 || nc <= 0) {
            clear();
            return;
        }
        
        width = nx;
        height = ny;
        channels = nc;
        
        long size = (long)width * height * channels;
        pixels = std::unique_ptr<float[]>(new float[size]);
        
        // Initialize to zero with parallel processing
    #pragma omp parallel for
        for (long i = 0; i < size; ++i) {
            pixels[i] = 0.0f;
        }
        
        loaded = true;
        
        cout << "Allocated new image: " << width << "x" << height << " with " << channels << " channels" << endl;
    }

    // Safe pixel accessor - get pixel value at (x, y, channel)
    float ImgProc::GetPixel(int x, int y, int c) const
    {
        if (!loaded) {
            cerr << "Error: Image not loaded" << endl;
            return 0.0f;
        }
        
        // Direct access - assumes caller has checked bounds
        long index = ((long)y * width + x) * channels + c;
        return pixels[index];
    }

    // Safe pixel setter - set pixel value at (x, y, channel)
    void ImgProc::SetPixel(int x, int y, int c, float value)
    {
        if (!loaded) {
            cerr << "Error: Image not loaded" << endl;
            return;
        }
        
        // Direct access - assumes caller has checked bounds
        long index = ((long)y * width + x) * channels + c;
        pixels[index] = value;
    }

    // Get pixel with bounds checking - returns 0.0f if out of bounds
    float ImgProc::GetPixelSafe(int x, int y, int c) const
    {
        if (!loaded) return 0.0f;
        if (x < 0 || x >= width) return 0.0f;
        if (y < 0 || y >= height) return 0.0f;
        if (c < 0 || c >= channels) return 0.0f;
        
        long index = ((long)y * width + x) * channels + c;
        return pixels[index];
    }

    // Apply gamma correction to the image
    void ImgProc::ApplyGamma(float gamma)
    {
        if (!loaded) {
            cerr << "Error: No image loaded to apply gamma correction" << endl;
            return;
        }
        
        long total_pixels = (long)width * height * channels;

    #pragma omp parallel for
        for (long i = 0; i < total_pixels; ++i) {
            // Apply gamma correction: output = input^gamma
            pixels[i] = pow(pixels[i], gamma);
        }
    }

}
