// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 1
// 9/11/2025
//-------------------------------------------------------
//
//  imgviewer.C
//
//  Main program for the image viewer that reads command
//  line arguments, loads images, and displays them.
//
//-------------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include "StarterViewer.h"
#include "ImgProc.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace starter;
using namespace std;

// Global variables for image handling
ImgProc* g_imgProc = nullptr;
GLuint g_textureID = 0;
bool g_textureLoaded = false;
string g_originalFilename;

// Function to parse command line arguments
string parseCommandLine(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-image" && i + 1 < argc) {
            return string(argv[i + 1]);
        }
    }
    return "";
}

void printUsage(const char* programName) {
    cout << "Usage: " << programName << " -image <image_file>" << endl;
    cout << "Example: " << programName << " -image tahoe.tif" << endl;
    cout << endl;
    cout << "Supported formats: jpg, jpeg, png, tif, tiff, exr, and others supported by OpenImageIO" << endl;
    cout << endl;
    cout << "Controls:" << endl;
    cout << "  j/J - Save image as demowritetoafile.jpg" << endl;
    cout << "  q/Q/ESC - Quit" << endl;
    cout << "  u - Show usage information" << endl;
}

void createTexture() {
    if (!g_imgProc || !g_imgProc->IsLoaded()) return;
    
    if (g_textureLoaded && g_textureID != 0) {
        glDeleteTextures(1, &g_textureID);
    }
    
    glGenTextures(1, &g_textureID);
    glBindTexture(GL_TEXTURE_2D, g_textureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // Determine format based on number of channels
    GLenum format;
    switch(g_imgProc->GetChannels()) {
        case 1: format = GL_LUMINANCE; break;
        case 2: format = GL_LUMINANCE_ALPHA; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: format = GL_RGB; break;
    }
    
    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, 
                 g_imgProc->GetWidth(), g_imgProc->GetHeight(), 0,
                 format, GL_FLOAT, g_imgProc->GetPixels());
    
    g_textureLoaded = true;
    cout << "Texture created successfully" << endl;
}

void renderImage() {
    if (!g_textureLoaded || !g_imgProc->IsLoaded()) return;
    
    StarterViewer* viewer = StarterViewer::Instance();
    
    // Set up orthographic projection for 2D image display
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // Set up coordinate system where image fits in [-1,1] range
    float aspect = (float)g_imgProc->GetWidth() / (float)g_imgProc->GetHeight();
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
    
    // Disable depth testing for 2D rendering
    glDisable(GL_DEPTH_TEST);
    
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_textureID);
    
    // Draw textured quad
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f,  1.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    
    // Restore matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Custom display function
void cbDisplayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderImage();
    glutSwapBuffers();
    glutPostRedisplay();
}

// Custom keyboard function
void cbKeyboardFunc(unsigned char key, int x, int y) {
    switch(key) {
        case 'j':
        case 'J':
            if (g_imgProc && g_imgProc->IsLoaded()) {
                string outputFilename = "demowritetoafile.jpg";
                cout << "Saving image to " << outputFilename << "..." << endl;
                if (g_imgProc->WriteImage(outputFilename)) {
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
            if (g_textureLoaded && g_textureID != 0) {
                glDeleteTextures(1, &g_textureID);
            }
            delete g_imgProc;
            exit(0);
            break;
        default:
            // Pass other keys to the original StarterViewer
            StarterViewer::Instance()->Keyboard(key, x, y);
            break;
    }
}

int main(int argc, char** argv)
{
    // Parse command line arguments
    string imageFilename = parseCommandLine(argc, argv);
    
    if (imageFilename.empty()) {
        cout << "Error: No image file specified!" << endl;
        printUsage(argv[0]);
        return 1;
    }
    
    // Create the image processor
    g_imgProc = new ImgProc();
    g_originalFilename = imageFilename;
    
    // Try to load the image
    if (!g_imgProc->ReadImage(imageFilename)) {
        cout << "Error: Failed to load image: " << imageFilename << endl;
        delete g_imgProc;
        return 1;
    }
    
    // Create the viewer
    StarterViewer* viewer = StarterViewer::Instance();
    
    // Set up viewer parameters
    viewer->SetWidth(800);
    viewer->SetHeight(600);
    
    // Update window title to include image name
    string title = "Image Viewer - " + imageFilename;
    viewer->SetTitle(title);
    
    // Convert command line arguments for GLUT
    vector<string> args;
    for (int i = 0; i < argc; i++) {
        args.push_back(string(argv[i]));
    }
    
    // Initialize the viewer
    viewer->Init(args);
    
    // Create texture after OpenGL is initialized
    createTexture();
    
    // Override the display and keyboard callbacks
    glutDisplayFunc(cbDisplayFunc);
    glutKeyboardFunc(cbKeyboardFunc);
    
    cout << "Starting image viewer..." << endl;
    cout << "Press 'j' to save the image as demowritetoafile.jpg" << endl;
    cout << "Press 'q' or ESC to quit" << endl;
    
    // Start the main loop
    viewer->MainLoop();
    
    // Cleanup
    if (g_textureLoaded && g_textureID != 0) {
        glDeleteTextures(1, &g_textureID);
    }
    delete g_imgProc;
    
    return 0;
}
