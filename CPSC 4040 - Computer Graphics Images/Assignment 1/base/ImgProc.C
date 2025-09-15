// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/11/2025
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

using namespace OIIO;
using namespace std;

namespace starter {

    // Constructor
    ImgProc::ImgProc() : width(0), height(0), channels(0), loaded(false)
    {
    }

    // Destructor
    ImgProc::~ImgProc()
    {
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
        pixels = std::unique_ptr<float[]>(new float[width * height * channels]);
        
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
        std::unique_ptr<unsigned char[]> byte_pixels(new unsigned char[width * height * channels]);
        for (int i = 0; i < width * height * channels; ++i) {
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

}
