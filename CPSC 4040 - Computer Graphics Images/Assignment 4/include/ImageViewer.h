// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 2
// 10/22/2025
//-------------------------------------------------------
//
//  ImageViewer.h
//
//  Custom viewer that can display images using OpenGL/GLUT
//  without depending on StarterViewer.
//
//-------------------------------------------------------

#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include "ImgProc.h"
#include <memory>
#include <string>
#include <vector>
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
    
    //! Get window dimensions
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    
    //! Parse command line arguments
    static std::string ParseCommandLine(int argc, char** argv);

  private:
    std::unique_ptr<ImgProc> imgProc;
    std::string originalFilename;
    std::unique_ptr<class ImageRenderer> renderer;
    
    // Window properties
    int width;
    int height;
    std::string title;
    
    // Zoom properties
    float zoomLevel;
    
    void CreateTexture();
    void UpdateWindowTitle();
    
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
