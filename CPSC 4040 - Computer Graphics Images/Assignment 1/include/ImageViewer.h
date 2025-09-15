// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/11/2025
//-------------------------------------------------------
//
//  ImageViewer.h
//
//  Custom viewer that can display images using the
//  StarterViewer framework and handle image-specific functionality.
//
//-------------------------------------------------------

#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include "StarterViewer.h"
#include "ImgProc.h"
#include <memory>
#include <GL/gl.h>   // For GLuint definition

namespace starter {

class ImageViewer
{
  public:
    ImageViewer();
    ~ImageViewer();

    //! Load an image from file
    bool LoadImage(const std::string& filename);
    
    //! Initialize the viewer
    void Init(const std::vector<std::string>& args);
    
    //! Start the main loop
    void MainLoop();
    
    //! Set window dimensions
    void SetWidth(int w);
    void SetHeight(int h);

  private:
    std::unique_ptr<ImgProc> imgProc;
    StarterViewer* viewer;
    GLuint textureID;
    bool textureLoaded;
    std::string originalFilename;
    
    void CreateTexture();
    void DeleteTexture();
    
    // Static callback functions for the viewer
    static void DisplayCallback();
    static void KeyboardCallback(unsigned char key, int x, int y);
    static void ReshapeCallback(int w, int h);
    
    // Instance pointer for callbacks
    static ImageViewer* instance;
    
    // Instance methods called by callbacks
    void Display();
    void Keyboard(unsigned char key, int x, int y);
    void Reshape(int w, int h);
    void RenderImage();
};

}

#endif
