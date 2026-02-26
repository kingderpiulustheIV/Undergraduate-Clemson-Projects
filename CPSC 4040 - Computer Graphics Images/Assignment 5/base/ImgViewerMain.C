// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 4
// 11/12/2025
//-------------------------------------------------------
//
//  imgviewer.C
//
//  Simplified main program for the image viewer.
//  All functionality is now handled by ImageViewer class.
//
//-------------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include "ImageViewer.h"

using namespace starter;
using namespace std;

// Main function 
int main(int argc, char** argv)
{
    // Parse command line arguments
    string imageFilename = ImageViewer::ParseCommandLine(argc, argv);
    
    if (imageFilename.empty()) {
        cout << "Error: No image file specified!" << endl;
        cout << "Usage: " << argv[0] << " -image <image_file>" << endl;
        return 1;
    }
    
    // Create and initialize the image viewer
    ImageViewer viewer;
    
    // Load the image
    if (!viewer.LoadImage(imageFilename)) {
        cout << "Error: Failed to load image: " << imageFilename << endl;
        return 1;
    }
    
    // Initialize the viewer with command line arguments
    vector<string> args(argv, argv + argc);
    viewer.Init(args);
    
    // Print usage information
    cout << "--------------------------------------------------------------" << endl;
    cout << "Image Processing Controls:" << endl;
    cout << "  C             Convert to contrast units (subtract avg, divide by RMS)" << endl;
    cout << "  H             Apply histogram equalization (500 bins)" << endl;
    cout << "  g             Apply gamma correction (gamma = 0.9)" << endl;
    cout << "  G             Apply gamma correction (gamma = 1.111111)" << endl;
    cout << "  s             Apply random stencil convolution (11x11)" << endl;
    cout << "  j             Save current processed image as JPEG file" << endl;
    cout << "  o             Save current processed image as EXR file (full float)" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "Julia Set Controls:" << endl;
    cout << "  J             Generate 9 Julia set images:" << endl;
    cout << "                julia.0001.jpg to julia.0003.jpg (range=1.0, iteration=100/250/500)" << endl;
    cout << "                julia.0004.jpg to julia.0006.jpg (range=1e-3, iteration=100/250/500)" << endl;
    cout << "                julia.0007.jpg to julia.0009.jpg (range=1e-6, iteration=100/250/500)" << endl;
    cout << "                Colors: Psychedelic" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "View Controls:" << endl;
    cout << "  +/=           Zoom in (magnify image)" << endl;
    cout << "  -/_           Zoom out (reduce image)" << endl;
    cout << "  1             Reset zoom to 100% (1:1 pixel-for-pixel)" << endl;
    cout << "  0             Fit to window" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "General Controls:" << endl;
    cout << "  u/U           Show this usage information" << endl;
    cout << "  q/Q/ESC       Quit" << endl;
                cout << "--------------------------------------------------------------" << endl;
    // Start the main loop
    viewer.MainLoop();
    
    return 0;
}
