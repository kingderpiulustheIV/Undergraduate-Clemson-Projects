// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 4
// 11/12/2025
//-------------------------------------------------------
//
//  ImageRenderer.C
//
//  Implementation of image rendering using OpenGL textures
//  with proper aspect ratio preservation.
//
//-------------------------------------------------------

#include "ImageRenderer.h"
#include <GL/glu.h>
#include <iostream>
#include <memory>

using namespace std;

namespace starter {

    // Constructor
    ImageRenderer::ImageRenderer() : image(nullptr), textureID(0), textureLoaded(false)
    {
    }

    // Destructor
    ImageRenderer::~ImageRenderer()
    {
        Cleanup();
    }

    // Set the image to render
    void ImageRenderer::SetImage(ImgProc* imgProc)
    {
        image = imgProc;
    }

    // Create OpenGL texture from current image
    void ImageRenderer::CreateTexture()
    {
        if (!image || !image->IsLoaded()) return;
        
        if (textureLoaded && textureID != 0) {
            glDeleteTextures(1, &textureID);
        }
        
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        // Determine format based on number of channels
        GLenum format;
        switch(image->GetChannels()) {
            case 1: format = GL_LUMINANCE; break;
            case 2: format = GL_LUMINANCE_ALPHA; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
            default: format = GL_RGB; break;
        }
        
        // For images with alpha channel, we need to handle premultiplied alpha
        // or ensure proper blending is set up
        if (image->GetChannels() == 4) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        
        // Upload texture data directly - OpenImageIO should provide properly formatted data
        glTexImage2D(GL_TEXTURE_2D, 0, format, 
                     image->GetWidth(), image->GetHeight(), 0,
                     format, GL_FLOAT, image->GetPixels());
        
        textureLoaded = true;
        cout << "Texture created successfully" << endl;
    }

    // Calculate quad dimensions for aspect ratio preservation with zoom
    void ImageRenderer::CalculateQuadDimensions(float& quadWidth, float& quadHeight, int windowWidth, int windowHeight, float zoomLevel)
    {
        if (!image || !image->IsLoaded()) {
            quadWidth = quadHeight = 1.0f;
            return;
        }
        
        // Calculate aspect ratios
        float imageAspect = (float)image->GetWidth() / (float)image->GetHeight();
        float windowAspect = (float)windowWidth / (float)windowHeight;
        
        // Calculate quad dimensions to maintain aspect ratio
        quadWidth = 1.0f;
        quadHeight = 1.0f;
        
        if (imageAspect > windowAspect) {
            // Image is wider than window - fit to width, letterbox top/bottom
            quadHeight = windowAspect / imageAspect;
        } else {
            // Image is taller than window - fit to height, letterbox left/right
            quadWidth = imageAspect / windowAspect;
        }
        
        // Apply zoom factor
        quadWidth *= zoomLevel;
        quadHeight *= zoomLevel;
    }

    // Render the image maintaining aspect ratio with zoom
    void ImageRenderer::Render(int windowWidth, int windowHeight, float zoomLevel)
    {
        if (!textureLoaded || !image || !image->IsLoaded()) return;
        
        // Set up orthographic projection for 2D image display
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        
        // Calculate quad dimensions to maintain aspect ratio with zoom
        float quadWidth, quadHeight;
        CalculateQuadDimensions(quadWidth, quadHeight, windowWidth, windowHeight, zoomLevel);
        
        // Disable depth testing for 2D rendering
        glDisable(GL_DEPTH_TEST);
        
        // Enable texturing
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        // Draw textured quad with correct aspect ratio
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-quadWidth, -quadHeight);
            glTexCoord2f(1.0f, 1.0f); glVertex2f( quadWidth, -quadHeight);
            glTexCoord2f(1.0f, 0.0f); glVertex2f( quadWidth,  quadHeight);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-quadWidth,  quadHeight);
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_DEPTH_TEST);
        
        // Restore matrices
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    // Clean up OpenGL resources
    void ImageRenderer::Cleanup()
    {
        if (textureLoaded && textureID != 0) {
            glDeleteTextures(1, &textureID);
            textureID = 0;
            textureLoaded = false;
        }
    }

}