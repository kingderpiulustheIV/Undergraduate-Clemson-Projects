// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/11/2025
//-------------------------------------------------------
//
//  ImgProc.h
//
//  Class for handling image processing operations using
//  OpenImageIO for reading and writing images.
//
//-------------------------------------------------------

#ifndef IMGPROC_H
#define IMGPROC_H

#include <string>
#include <memory>
#include <vector>

namespace starter {

// Stencil class for linear filtering
class Stencil {
public:
    Stencil(int width);
    ~Stencil() = default;
    
    float& operator()(int i, int j);
    const float& operator()(int i, int j) const;
    
    int GetWidth() const { return width; }
    int GetRadius() const { return width / 2; }
    
private:
    int width;
    std::vector<float> data;
};

class ImgProc
{
  public:
    ImgProc();
    ImgProc(const ImgProc& other);  // Copy constructor
    ImgProc& operator=(const ImgProc& other);  // Copy assignment operator
    ~ImgProc();

    //! Read an image from file
    bool ReadImage(const std::string& filename);
    
    //! Write image to file
    bool WriteImage(const std::string& filename);
    
    //! Clear the image data
    void clear();
    
    //! Clear and allocate new image data
    void clear(int nx, int ny, int nc);
    
    //! Get image width
    int GetWidth() const { return width; }
    
    //! Get image height
    int GetHeight() const { return height; }
    
    //! Get number of channels
    int GetChannels() const { return channels; }
    
    //! Get pixel data (raw pointer - use only when necessary for legacy APIs like OpenGL)
    float* GetPixels() const { return pixels.get(); }
    
    //! Safe pixel accessor - get pixel value at (x, y, channel)
    float GetPixel(int x, int y, int c) const;
    
    //! Safe pixel setter - set pixel value at (x, y, channel)
    void SetPixel(int x, int y, int c, float value);
    
    //! Get pixel with bounds checking - returns 0.0f if out of bounds
    float GetPixelSafe(int x, int y, int c) const;
    
    //! Check if image is loaded
    bool IsLoaded() const { return loaded; }
    
    //! Apply gamma correction to the image
    void ApplyGamma(float gamma);
    
    //! Convert image to contrast units (subtract average, divide by RMS for each channel)
    void ConvertToContrastUnits();
    
    //! Apply histogram equalization using 500 bins
    void HistogramEqualization();
    
    //! Write image as JPEG file
    bool WriteImageJPEG(const std::string& filename);
    
    //! Write image as EXR file (full floating point)
    bool WriteImageEXR(const std::string& filename);

  private:
    int width;
    int height;
    int channels;
    std::unique_ptr<float[]> pixels;
    bool loaded;
};

// Function for bounded linear convolution
namespace img {
    void BoundedLinearConvolution(const Stencil& stencil, const ImgProc& in, ImgProc& out);
    Stencil GenerateRandomStencil(int width);  // Configurable stencil width (make this easy to change)
}

}

#endif
