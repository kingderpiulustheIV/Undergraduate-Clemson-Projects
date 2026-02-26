// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/25/2025
//-------------------------------------------------------
//
//  ImageRenderer.h
//
//  Class for rendering images using OpenGL textures
//  with proper aspect ratio preservation.
//
//-------------------------------------------------------

#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

#include "ImgProc.h"
#include <GL/gl.h>

namespace starter {

class ImageRenderer
{
  public:
    ImageRenderer();
    ~ImageRenderer();

    //! Set the image to render
    void SetImage(ImgProc* imgProc);
    
    //! Create OpenGL texture from current image
    void CreateTexture();
    
    //! Render the image maintaining aspect ratio
    void Render();
    
    //! Check if texture is loaded
    bool IsTextureLoaded() const { return textureLoaded; }
    
    //! Clean up OpenGL resources
    void Cleanup();

  private:
    ImgProc* image;
    GLuint textureID;
    bool textureLoaded;
    
    //! Calculate quad dimensions for aspect ratio preservation
    void CalculateQuadDimensions(float& quadWidth, float& quadHeight);
};

}

#endif