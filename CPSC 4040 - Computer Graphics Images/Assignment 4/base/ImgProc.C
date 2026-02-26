// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 4
// 11/12/2025
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
#include <vector>

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

    // Convert image to contrast units (subtract average, divide by RMS for each channel)
    void ImgProc::ConvertToContrastUnits()
    {
        if (!loaded) {
            cerr << "Error: No image loaded to convert to contrast units" << endl;
            return;
        }
        
        cout << "Converting to contrast units..." << endl;
        
        long total_pixels = (long)width * height;
        
        // Calculate average and RMS for each channel
        vector<float> averages(channels, 0.0f);
        vector<float> rms(channels, 0.0f);
        
        // Calculate averages
        for (int c = 0; c < channels; ++c) {
            double sum = 0.0;
            for (long p = 0; p < total_pixels; ++p) {
                sum += pixels[p * channels + c];
            }
            averages[c] = (float)(sum / total_pixels);
            cout << "Channel " << c << " average: " << averages[c] << endl;
        }
        
        // Calculate RMS (root mean square)
        for (int c = 0; c < channels; ++c) {
            double sum_squares = 0.0;
            for (long p = 0; p < total_pixels; ++p) {
                float val = pixels[p * channels + c];
                sum_squares += (val - averages[c]) * (val - averages[c]);
            }
            rms[c] = sqrt(sum_squares / total_pixels);
            cout << "Channel " << c << " RMS: " << rms[c] << endl;
        }
        
        // Convert to contrast units: (pixel - average) / RMS
    #pragma omp parallel for
        for (long p = 0; p < total_pixels; ++p) {
            for (int c = 0; c < channels; ++c) {
                
                // Avoid division by zero
                if (rms[c] > 1e-10f) { 
                    pixels[p * channels + c] = (pixels[p * channels + c] - averages[c]) / rms[c];
                } else {
                    pixels[p * channels + c] = 0.0f;
                }
            }
        }
        
        cout << "Contrast units conversion completed" << endl;
    }

    // Apply histogram equalization using 500 bins
    void ImgProc::HistogramEqualization()
    {
        if (!loaded) {
            cerr << "Error: No image loaded to apply histogram equalization" << endl;
            return;
        }
        
        cout << "Applying histogram equalization with 500 bins..." << endl;
        
        const int NUM_BINS = 500;
        long total_pixels = (long)width * height;
        
        // Process each channel separately
        for (int c = 0; c < channels; ++c) {
            
            // Find min and max values for this channel
            float min_val = pixels[c];
            float max_val = pixels[c];
            
            for (long p = 0; p < total_pixels; ++p) {
                float val = pixels[p * channels + c];
                if (val < min_val) min_val = val;
                if (val > max_val) max_val = val;
            }
            
            cout << "Channel " << c << " - Min: " << min_val << ", Max: " << max_val << endl;
            
            // Create histogram
            vector<int> histogram(NUM_BINS, 0);
            float range = max_val - min_val;
            
            // Build histogram
            for (long p = 0; p < total_pixels; ++p) {
                float val = pixels[p * channels + c];
                int bin = (int)((val - min_val) / range * (NUM_BINS - 1));
                if (bin < 0) bin = 0;
                if (bin >= NUM_BINS) bin = NUM_BINS - 1;
                histogram[bin]++;
            }
            
            // Normalize to probability distribution
            vector<float> probability(NUM_BINS);
            for (int i = 0; i < NUM_BINS; ++i) {
                probability[i] = (float)histogram[i] / total_pixels;
            }
            
            // Calculate cumulative distribution function (CDF)
            vector<float> cdf(NUM_BINS);
            cdf[0] = probability[0];
            for (int i = 1; i < NUM_BINS; ++i) {
                cdf[i] = cdf[i-1] + probability[i];
            }
            
            // Apply histogram equalization
            for (long p = 0; p < total_pixels; ++p) {
                float val = pixels[p * channels + c];
                int bin = (int)((val - min_val) / range * (NUM_BINS - 1));
                if (bin < 0) bin = 0;
                if (bin >= NUM_BINS) bin = NUM_BINS - 1;
                
                // Replace pixel value with CDF value
                pixels[p * channels + c] = cdf[bin];
            }
        }
        
        cout << "Histogram equalization completed" << endl;
    }

    // Write image as JPEG file
    bool ImgProc::WriteImageJPEG(const std::string& filename)
    {
        if (!loaded) {
            cerr << "Error: No image loaded to write as JPEG" << endl;
            return false;
        }
        
        cout << "Writing JPEG file: " << filename << endl;
        
        // Create output image
        auto out = ImageOutput::create(filename);
        if (!out) {
            cerr << "Error: Could not create JPEG output for " << filename << endl;
            return false;
        }
        
        // Define image specification for JPEG (8-bit)
        ImageSpec spec(width, height, channels, TypeDesc::UINT8);
        if (!out->open(filename, spec)) {
            cerr << "Error: Could not open " << filename << " for JPEG writing" << endl;
            return false;
        }
        
        // Convert float data to UINT8 for JPEG writing
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
            cout << "JPEG image written successfully to " << filename << endl;
        } else {
            cerr << "Error writing JPEG image to " << filename << endl;
        }
        
        return success;
    }

    // Write image as EXR file (full floating point)
    bool ImgProc::WriteImageEXR(const std::string& filename)
    {
        if (!loaded) {
            cerr << "Error: No image loaded to write as EXR" << endl;
            return false;
        }
        
        cout << "Writing EXR file with full floating point precision: " << filename << endl;
        
        // Create output image
        auto out = ImageOutput::create(filename);
        if (!out) {
            cerr << "Error: Could not create EXR output for " << filename << endl;
            return false;
        }
        
        // Define image specification for EXR (floating point)
        ImageSpec spec(width, height, channels, TypeDesc::FLOAT);
        if (!out->open(filename, spec)) {
            cerr << "Error: Could not open " << filename << " for EXR writing" << endl;
            return false;
        }
        
        // Write the image data directly as floats
        bool success = out->write_image(TypeDesc::FLOAT, pixels.get());
        out->close();
        
        if (success) {
            cout << "EXR image written successfully to " << filename << endl;
        } else {
            cerr << "Error writing EXR image to " << filename << endl;
        }
        
        return success;
    }

}
