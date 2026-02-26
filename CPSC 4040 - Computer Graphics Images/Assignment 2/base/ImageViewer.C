// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 2
// 10/22/2025
//-------------------------------------------------------
//
//  ImageViewer.C
//
//  Implementation of ImageViewer that displays images 
//  using OpenGL textures without depending on StarterViewer.
//
//-------------------------------------------------------

#include "ImageViewer.h"
#include "ImageRenderer.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace starter::img;  // For BoundedLinearConvolution and GenerateRandomStencil

namespace starter {

    // Static instance pointer for callbacks
    ImageViewer* ImageViewer::instance = nullptr;

    // Constructor
    ImageViewer::ImageViewer() : 
        imgProc(nullptr),
        width(800),
        height(600),
        title("Image Viewer"),
        zoomLevel(1.0f)
    {
        imgProc = std::unique_ptr<ImgProc>(new ImgProc());
        renderer = std::unique_ptr<ImageRenderer>(new ImageRenderer());
        instance = this;
    }

    // Destructor
    ImageViewer::~ImageViewer()
    {
        if (renderer) {
            renderer->Cleanup();
        }
        instance = nullptr;
    }

    // Load an image from file
    bool ImageViewer::LoadImage(const std::string& filename)
    {
        originalFilename = filename;
        
        if (!imgProc->ReadImage(filename)) {
            return false;
        }
        
        // Set the image in the renderer (but don't create texture yet)
        // Texture creation will happen after OpenGL context is initialized
        renderer->SetImage(imgProc.get());
        return true;
    }

    // Initialize the viewer
    void ImageViewer::Init(const std::vector<std::string>& args)
    {
        // Convert args to argc/argv for glutInit
        int argc = (int)args.size();
        char** argv = new char*[argc];
        for (int i = 0; i < argc; i++)
        {
            argv[i] = new char[args[i].length() + 1];
            std::strcpy(argv[i], args[i].c_str());
        }

        // Calculate window size based on image aspect ratio if image is loaded
        if (imgProc && imgProc->IsLoaded()) {
            int imgWidth = imgProc->GetWidth();
            int imgHeight = imgProc->GetHeight();
            float aspectRatio = (float)imgWidth / (float)imgHeight;
            
            // Set maximum window dimensions (don't exceed screen size)
            const int MAX_WIDTH = 1920;
            const int MAX_HEIGHT = 1080;
            
            // Calculate window size maintaining aspect ratio
            if (imgWidth > MAX_WIDTH || imgHeight > MAX_HEIGHT) {
                // Scale down to fit
                if (aspectRatio > (float)MAX_WIDTH / MAX_HEIGHT) {
                    // Image is wider - fit to width
                    width = MAX_WIDTH;
                    height = (int)(MAX_WIDTH / aspectRatio);
                } else {
                    // Image is taller - fit to height
                    height = MAX_HEIGHT;
                    width = (int)(MAX_HEIGHT * aspectRatio);
                }
            } else {
                // Use image dimensions directly
                width = imgWidth;
                height = imgHeight;
            }
        }

        // Prepare window title (but don't set it yet - need GLUT initialized)
        if (!originalFilename.empty() && imgProc && imgProc->IsLoaded()) {
            std::ostringstream oss;
            oss << "Image Viewer - " << originalFilename 
                << " [" << imgProc->GetWidth() << "x" << imgProc->GetHeight() << "]"
                << " Zoom: " << (int)(zoomLevel * 100) << "%";
            title = oss.str();
        } else if (!originalFilename.empty()) {
            title = "Image Viewer - " + originalFilename;
        }

        // Initialize GLUT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow(title.c_str());
        glClearColor(0.5, 0.5, 0.6, 0.0);

        // Clean up argv
        for (int i = 0; i < argc; i++) {
            delete[] argv[i];
        }
        delete[] argv;

        // Now that OpenGL context is initialized, create texture if image is loaded
        if (imgProc && imgProc->IsLoaded()) {
            renderer->CreateTexture();
        }
        
        // Set up GLUT callbacks
        glutDisplayFunc(DisplayCallback);
        glutKeyboardFunc(KeyboardCallback);
        glutReshapeFunc(ReshapeCallback);
        
        cout << "ImageViewer Initialized\n";
    }

    // Start the main loop
    void ImageViewer::MainLoop()
    {
        glutMainLoop();
    }

    // Set window dimensions
    void ImageViewer::SetWidth(int w)
    {
        width = w;
    }

    void ImageViewer::SetHeight(int h)
    {
        height = h;
    }

    // Create OpenGL texture using ImageRenderer
    void ImageViewer::CreateTexture()
    {
        if (renderer && imgProc->IsLoaded()) {
            renderer->SetImage(imgProc.get());
            renderer->CreateTexture();
        }
    }

    // Update window title with image info and zoom level
    void ImageViewer::UpdateWindowTitle()
    {
        if (!originalFilename.empty() && imgProc && imgProc->IsLoaded()) {
            std::ostringstream oss;
            oss << "Image Viewer - " << originalFilename 
                << " [" << imgProc->GetWidth() << "x" << imgProc->GetHeight() << "]"
                << " Zoom: " << (int)(zoomLevel * 100) << "%";
            title = oss.str();
            glutSetWindowTitle(title.c_str());
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
        
        if (renderer && renderer->IsTextureLoaded() && imgProc->IsLoaded()) {
            RenderImage();
        }
        
        glutSwapBuffers();
        glutPostRedisplay();
    }

    // Render the loaded image using ImageRenderer
    void ImageViewer::RenderImage()
    {
        if (renderer && imgProc->IsLoaded()) {
            renderer->Render(width, height, zoomLevel);
        }
    }

    // Reshape the window
    void ImageViewer::Reshape(int w, int h)
    {
        width = w;
        height = h;
        
        // Update viewport for image display
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
    }

    // Handle keyboard input
    void ImageViewer::Keyboard(unsigned char key, int x, int y)
    {
        switch(key) {
            case '+':
            case '=':
                // Zoom in
                zoomLevel *= 1.25f;
                if (zoomLevel > 10.0f) zoomLevel = 10.0f; // Max zoom
                cout << "Zoom: " << (int)(zoomLevel * 100) << "%" << endl;
                UpdateWindowTitle();
                break;
            case '-':
            case '_':
                // Zoom out
                zoomLevel /= 1.25f;
                if (zoomLevel < 0.1f) zoomLevel = 0.1f; // Min zoom
                cout << "Zoom: " << (int)(zoomLevel * 100) << "%" << endl;
                UpdateWindowTitle();
                break;
            case '1':
                // Reset zoom to 1:1 (100%)
                zoomLevel = 1.0f;
                cout << "Zoom reset to 100% (1:1 pixel)" << endl;
                UpdateWindowTitle();
                break;
            case '0':
                // Fit to window
                zoomLevel = 1.0f;
                cout << "Zoom reset to fit window" << endl;
                UpdateWindowTitle();
                break;
            case 'j':
            case 'J':
                if (imgProc->IsLoaded()) {
                    string outputFilename = "demowritetoafile.jpg";
                    cout << "Saving image to " << outputFilename << "..." << endl;
                    if (imgProc->WriteImage(outputFilename)) {
                        cout << "Image saved successfully!" << endl;
                        cout << "--------------------------------------------------------------" << endl;  
                    } else {
                        cout << "Failed to save image!" << endl;
                        cout << "--------------------------------------------------------------" << endl;
                    }
                } else {
                    cout << "No image loaded to save!" << endl;
                    cout << "--------------------------------------------------------------" << endl;
                }   
                break;
            case 'g':
                if (imgProc->IsLoaded()) {
                    cout << "Applying gamma correction gamma = 0.9..." << endl;
                    // Create a deep copy for processing
                    ImgProc processedImage(*imgProc);
                    processedImage.ApplyGamma(0.9f);
                    
                    // Replace original with processed image using assignment operator (deep copy)
                    *imgProc = processedImage;
                    
                    // Update texture with new image data
                    CreateTexture();
                    cout << "Gamma correction applied and display updated!" << endl;
                    cout << "--------------------------------------------------------------" << endl;
                } else {
                    cout << "No image loaded for gamma correction!" << endl;
                    cout << "--------------------------------------------------------------" << endl;
                }
                break;
            case 'G':
                if (imgProc->IsLoaded()) {
                    cout << "Applying gamma correction gamma = 1.111111..." << endl;
                    // Create a deep copy for processing
                    ImgProc processedImage(*imgProc);
                    processedImage.ApplyGamma(1.111111f);
                    
                    // Replace original with processed image using assignment operator (deep copy)
                    *imgProc = processedImage;
                    
                    // Update texture with new image data
                    CreateTexture();
                    cout << "Gamma correction applied and display updated!" << endl;
                    cout << "--------------------------------------------------------------" << endl;
                } else {
                    cout << "No image loaded for gamma correction!" << endl;
                    cout << "--------------------------------------------------------------" << endl;
                }
                break;
            case 's':
            case 'S':
                if (imgProc->IsLoaded()) {
                    cout << "Applying random stencil filter..." << endl;
                    
                    // Generate a random 11x11 stencil (width=11 for 11x11)
                    const int STENCIL_WIDTH = 11;  // Easy to change for grader
                    starter::Stencil stencil = GenerateRandomStencil(STENCIL_WIDTH);
                    
                    // Create output image for convolution result
                    starter::ImgProc filteredImage;
                    BoundedLinearConvolution(stencil, *imgProc, filteredImage);
                    
                    // Replace original with filtered image using assignment operator (deep copy)
                    *imgProc = filteredImage;
                    
                    // Update texture with new image data
                    CreateTexture();
                    cout << "Stencil filter applied and display updated!" << endl;
                    cout << "--------------------------------------------------------------" << endl;

                } else {
                    cout << "No image loaded for stencil filtering!" << endl;
                    cout << "--------------------------------------------------------------" << endl;
                }
                break;
            case 'u':
            case 'U':
                cout << "--------------------------------------------------------------" << endl;
                cout << "Image Processing Controls:" << endl;
                cout << "--------------------------------------------------------------" << endl;
                cout << "  g             Apply gamma correction (gamma = 0.9)" << endl;
                cout << "  G             Apply gamma correction (gamma = 1.111111)" << endl;
                cout << "  s             Apply random stencil convolution (11x11)" << endl;
                cout << "  j/J           Save current processed image as JPEG file" << endl;
                cout << "View Controls:" << endl;
                cout << "  +/=           Zoom in (magnify image)" << endl;
                cout << "  -/_           Zoom out (reduce image)" << endl;
                cout << "  1             Reset zoom to 100% (1:1 pixel-for-pixel)" << endl;
                cout << "  0             Fit to window" << endl;
                cout << "General Controls:" << endl;
                cout << "  u/U           Show this usage information" << endl;
                cout << "  q/Q/ESC       Quit" << endl;
                cout << "--------------------------------------------------------------" << endl;
                break;
            case 27: // ESC key
            case 'q':
            case 'Q':
                cout << "Exiting..." << endl;
                exit(0);
                break;
            default:
                // Ignore unrecognized keys
                break;
        }
    }

    // Static function to parse command line arguments
    std::string ImageViewer::ParseCommandLine(int argc, char** argv) {
        for (int i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "-image" && i + 1 < argc) {
                return std::string(argv[i + 1]);
            }
        }
        return "";
    }

}
