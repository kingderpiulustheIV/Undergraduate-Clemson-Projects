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
#include "ImageRenderer.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace starter;
using namespace std;

// Global variables for image handling
ImgProc* g_imgProc = nullptr;
ImageRenderer* g_renderer = nullptr;
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
    if (g_renderer) {
        g_renderer->CreateTexture();
    }
}

void renderImage() {
    if (g_renderer) {
        g_renderer->Render();
    }
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
        case 'u':
        case 'U':
            printUsage("imgviewer");
            cout << endl;
            StarterViewer::Instance()->Usage();
            break;
        case 27: // ESC key
        case 'q':
        case 'Q':
            cout << "Exiting..." << endl;
            if (g_renderer) {
                g_renderer->Cleanup();
                delete g_renderer;
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
    
    // Create the image processor and renderer
    g_imgProc = new ImgProc();
    g_renderer = new ImageRenderer();
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
    
    // Set up the renderer with the loaded image
    g_renderer->SetImage(g_imgProc);
    
    // Create texture after OpenGL is initialized
    createTexture();
    
    // Override the display and keyboard callbacks
    glutDisplayFunc(cbDisplayFunc);
    glutKeyboardFunc(cbKeyboardFunc);
    
    cout << "Starting image viewer..." << endl;
    cout << "Press 'j' to save the image as demowritetoafile.jpg" << endl;
    cout << "Press 'u' to show usage information" << endl;
    cout << "Press 'q' or ESC to quit" << endl;
    
    // Start the main loop
    viewer->MainLoop();
    
    // Cleanup
    if (g_renderer) {
        g_renderer->Cleanup();
        delete g_renderer;
    }
    delete g_imgProc;
    
    return 0;
}
