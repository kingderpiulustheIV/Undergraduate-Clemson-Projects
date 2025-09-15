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

namespace starter {

class ImgProc
{
  public:
    ImgProc();
    ~ImgProc();

    //! Read an image from file
    bool ReadImage(const std::string& filename);
    
    //! Write image to file
    bool WriteImage(const std::string& filename);
    
    //! Get image width
    int GetWidth() const { return width; }
    
    //! Get image height
    int GetHeight() const { return height; }
    
    //! Get number of channels
    int GetChannels() const { return channels; }
    
    //! Get pixel data
    float* GetPixels() const { return pixels.get(); }
    
    //! Check if image is loaded
    bool IsLoaded() const { return loaded; }

  private:
    int width;
    int height;
    int channels;
    std::unique_ptr<float[]> pixels;
    bool loaded;
};

}

#endif
