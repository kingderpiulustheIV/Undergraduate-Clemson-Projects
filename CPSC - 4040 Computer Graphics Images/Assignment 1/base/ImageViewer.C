// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/11/2025
//-------------------------------------------------------
//
//  ImageViewer.C
//
//  Implementation of ImageViewer that works with the 
//  StarterViewer singleton to display images using OpenGL textures.
//
//-------------------------------------------------------

#include "ImageViewer.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>

using namespace std;

namespace starter {

// Static instance pointer for callbacks
ImageViewer* ImageViewer::instance = nullptr;

// GLUT Callbacks
ImageViewer::ImageViewer() : imgProc(nullptr), viewer(nullptr), textureID(0), textureLoaded(false)
{
    imgProc = std::unique_ptr<ImgProc>(new ImgProc());
    instance = this;
}

// Destructor
ImageViewer::~ImageViewer()
{
    DeleteTexture();
    instance = nullptr;
}

// Load an image from file
bool ImageViewer::LoadImage(const std::string& filename)
{
    originalFilename = filename;
    
    if (!imgProc->ReadImage(filename)) {
        return false;
    }
    
    CreateTexture();
    return true;
}

// Initialize the viewer
void ImageViewer::Init(const std::vector<std::string>& args)
{
    viewer = StarterViewer::Instance();
    
    // Update window title to include image name
    string title = "Image Viewer - " + originalFilename;
    viewer->SetTitle(title);
    
    viewer->Init(args);
}

// Start the main loop
void ImageViewer::MainLoop()
{
    if (viewer) {
        viewer->MainLoop();
    }
}

// Set window dimensions
void ImageViewer::SetWidth(int w)
{
    if (viewer) {
        viewer->SetWidth(w);
    }
}

void ImageViewer::SetHeight(int h)
{
    if (viewer) {
        viewer->SetHeight(h);
    }
}

// Create OpenGL texture from loaded image
void ImageViewer::CreateTexture()
{
    // Check if image is loaded
    if (!imgProc->IsLoaded()) return;
    
    // Clean up any existing texture
    DeleteTexture(); 
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // Determine format based on number of channels
    GLenum format;
    switch(imgProc->GetChannels()) {
        case 1: format = GL_LUMINANCE; break;
        case 2: format = GL_LUMINANCE_ALPHA; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: format = GL_RGB; break;
    }
    
    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, 
                 imgProc->GetWidth(), imgProc->GetHeight(), 0,
                 format, GL_FLOAT, imgProc->GetPixels());
    
    textureLoaded = true;
    
    cout << "Texture created successfully" << endl;
}

void ImageViewer::DeleteTexture()
{
    if (textureLoaded && textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
        textureLoaded = false;
    }
}

// Static callback functions
void ImageViewer::DisplayCallback()
{
    if (instance) {
        instance->Display();
    }
}

void ImageViewer::KeyboardCallback(unsigned char key, int x, int y)
{
    if (instance) {
        instance->Keyboard(key, x, y);
    }
}

void ImageViewer::ReshapeCallback(int w, int h)
{
    if (instance) {
        instance->Reshape(w, h);
    }
}

// Instance methods
void ImageViewer::Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (textureLoaded && imgProc->IsLoaded()) {
        RenderImage();
    }
    
    glutSwapBuffers();
    glutPostRedisplay();
}

// Render the loaded image as a textured quad
void ImageViewer::RenderImage()
{
    // Set up orthographic projection for 2D image display
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // Set up coordinate system where image fits in [-1,1] range
    float aspect = (float)imgProc->GetWidth() / (float)imgProc->GetHeight();
    float windowAspect = (float)viewer->GetWidth() / (float)viewer->GetHeight();
    
    if (aspect > windowAspect) {
        // Image is wider than window
        gluOrtho2D(-1.0, 1.0, -1.0/aspect*windowAspect, 1.0/aspect*windowAspect);
    } else {
        // Image is taller than window  
        gluOrtho2D(-aspect/windowAspect, aspect/windowAspect, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Draw textured quad
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,  1.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    // Restore matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Handle keyboard input
void ImageViewer::Keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'j':
        case 'J':
            if (imgProc->IsLoaded()) {
                string outputFilename = "demowritetoafile.jpg";
                cout << "Saving image to " << outputFilename << "..." << endl;
                if (imgProc->WriteImage(outputFilename)) {
                    cout << "Image saved successfully!" << endl;
                } else {
                    cout << "Failed to save image!" << endl;
                }
            } else {
                cout << "No image loaded to save!" << endl;
            }
            break;
        case 27: // ESC key
        case 'q':
        case 'Q':
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            // Pass other keys to the original StarterViewer
            if (viewer) {
                viewer->Keyboard(key, x, y);
            }
            break;
    }
}

// Reshape the window
void ImageViewer::Reshape(int w, int h)
{
    if (viewer) {
        viewer->Reshape(w, h);
    }
    // Update viewport for image display
    glViewport(0, 0, w, h);
}

}
