// Sean Farrell
// CPSC 4040 Tessendorf
// Assignment 5
// 12/5/2025
//-------------------------------------------------------
//
//  OpticalFlowMain.C
//
//  Main program to compute optical flow and apply it to target image
//  Supports reading frame sequences from 1-9999 images
//
//-------------------------------------------------------

#include "OpticalFlow.h"
#include "ImgProc.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace starter;
using namespace std;

// Print usage instructions
void printUsage(const char* programName) {
    cout << "Usage: " << programName << " [mode] [arguments]" << endl;
    cout << "Modes:" << endl;
    cout << "  apply <target_image>  - Apply flow from input frames to target image" << endl;
    cout << "  analyze [start] [end] - Analyze flow between target_flown sequences" << endl;
    cout << endl;
    cout << "Examples:" << endl;
    cout << "  " << programName << " apply opticalflowtarget.jpg" << endl;
    cout << "  " << programName << " analyze" << endl;
    cout << "  " << programName << " analyze 1 100" << endl;
}

// Find the maximum frame number available in the specified folder with given prefix
int findMaxFrameNumber(const string& folder, const string& prefix) {
    int maxFrame = 0;
    
    // Validate inputs
    if (folder.empty() || prefix.empty()) {
        cerr << "Error: Invalid folder or prefix in findMaxFrameNumber" << endl;
        return 0;
    }
    
    // Search for frames in the valid range (1-9999)
    for (int i = 1; i <= 9999; ++i) {
        ostringstream oss;
        oss << folder << prefix << "." << setw(4) << setfill('0') << i << ".jpg";
        ImgProc testImage;
        
        if (testImage.ReadImage(oss.str())) {
            maxFrame = i;
        } else if (maxFrame > 0) {
            // Found some frames but this one doesn't exist, likely reached the end
            // Continue checking a few more in case there are gaps
            bool foundMore = false;
            for (int j = i + 1; j <= min(i + 10, 9999); ++j) {
                ostringstream oss2;
                oss2 << folder << prefix << "." << setw(4) << setfill('0') << j << ".jpg";
                ImgProc testImage2;
                if (testImage2.ReadImage(oss2.str())) {
                    foundMore = true;
                    break;
                }
            }
            if (!foundMore) {
                break; // No more frames found, stop searching
            }
        }
    }
    
    return maxFrame;
}

// Run in apply mode
bool runApplyMode(const string& targetImageName) {
    cout << "=== Apply Mode: Optical Flow Processing ===" << endl;
    
    OpticalFlow flowProcessor;
    ImgProc frame1, frame2, targetImage, outputImage;
    vector<vector<FlowVector>> flow;
    
    // Define folder paths
    string inputFolder = "optical flow input/";
    string outputFolder = "optical flow output/";
    
    // Load the target image (look in output folder first, then current directory)
    string targetFilename = outputFolder + targetImageName;
    if (!targetImage.ReadImage(targetFilename)) {
        // Try current directory
        targetFilename = targetImageName;
        if (!targetImage.ReadImage(targetFilename)) {
            cerr << "Error: Cannot load target image: " << targetImageName << endl;
            cerr << "Looked in: " << outputFolder << targetImageName << endl;
            cerr << "       and: " << targetImageName << endl;
            return false;
        }
    }
    
    cout << "Loaded target image: " << targetFilename << endl;
    cout << "Target image size: " << targetImage.GetWidth() << "x" << targetImage.GetHeight() << endl;
    
    // Copy target image to output folder if not already there
    string outputTargetPath = outputFolder + targetImageName;
    if (targetFilename != outputTargetPath) {
        if (!targetImage.WriteImage(outputTargetPath)) {
            cerr << "Warning: Could not copy target image to output folder" << endl;
        } else {
            cout << "Copied target image to: " << outputTargetPath << endl;
        }
    }
    
    // Start with the original target image
    outputImage = targetImage;
    
    // Find available frames in input folder (1-9999 range)
    int frameCount = findMaxFrameNumber(inputFolder, "frame");
    
    cout << "Found " << frameCount << " frames in input folder" << endl;
    
    if (frameCount < 2) {
        cerr << "Error: Need at least 2 frames for optical flow computation" << endl;
        return false;
    }
    
    cout << "Processing " << (frameCount - 1) << " frame pairs..." << endl;
    
    // Process each pair of consecutive frames
    for (int frameIdx = 1; frameIdx < frameCount; ++frameIdx) {
        cout << "Processing frame pair " << frameIdx << "/" << (frameCount - 1) << "..." << endl;
        
        // Generate filenames for consecutive frames in input folder
        ostringstream oss1, oss2;
        oss1 << inputFolder << "frame." << setw(4) << setfill('0') << frameIdx << ".jpg";
        oss2 << inputFolder << "frame." << setw(4) << setfill('0') << (frameIdx + 1) << ".jpg";
        
        string frame1Name = oss1.str();
        string frame2Name = oss2.str();
        
        // Load the frames
        if (!frame1.ReadImage(frame1Name)) {
            cerr << "Error: Cannot load frame: " << frame1Name << endl;
            continue;
        }
        
        if (!frame2.ReadImage(frame2Name)) {
            cerr << "Error: Cannot load frame: " << frame2Name << endl;
            continue;
        }
        
        cout << "  Loaded frames: " << frame1Name << " and " << frame2Name << endl;
        
        // Compute optical flow between the frames
        if (!flowProcessor.ComputeFlow(frame1, frame2, flow)) {
            cerr << "Error: Failed to compute optical flow for frame pair " << frameIdx << endl;
            continue;
        }
        
        cout << "  Computed optical flow" << endl;
        
        // Apply the flow to the current state of the target image
        ImgProc tempOutput;
        if (!flowProcessor.ApplyFlow(outputImage, flow, tempOutput)) {
            cerr << "Error: Failed to apply optical flow for frame pair " << frameIdx << endl;
            continue;
        }
        
        // Update the output image for the next iteration
        outputImage = tempOutput;
        
        cout << "  Applied optical flow to target image" << endl;
        
        // Save the result to output folder
        ostringstream outputOss;
        outputOss << outputFolder << "target_flown." << setw(4) << setfill('0') << frameIdx << ".jpg";
        string outputFilename = outputOss.str();
        
        if (!outputImage.WriteImage(outputFilename)) {
            cerr << "Error: Failed to save output image: " << outputFilename << endl;
            continue;
        }
        
        cout << "  Saved output: " << outputFilename << endl;
        
        // Optional: Save flow visualization for debugging (only for first few frames)
        if (frameIdx <= 5) {
            ostringstream flowOss;
            flowOss << inputFolder << "flow_viz." << setw(4) << setfill('0') << frameIdx << ".jpg";
            string flowVizFilename = flowOss.str();
            
            flowProcessor.SaveFlowAsImage(flow, flowVizFilename, 
                                          frame1.GetWidth(), frame1.GetHeight());
            cout << "  Saved flow visualization: " << flowVizFilename << endl;
        }
    }
    
    cout << "\n=== Apply Mode Complete ===" << endl;
    cout << "Generated " << (frameCount - 1) << " output frames" << endl;
    cout << "Files saved in: " << outputFolder << endl;
    
    return true;
}

// Run in analyze mode
bool runAnalyzeMode(int startFrame = 1, int endFrame = 9999) {
    cout << "=== Analyze Mode: Target_Flown Sequence Analysis ===" << endl;
    
    OpticalFlow flowProcessor;
    ImgProc frame1, frame2;
    vector<vector<FlowVector>> flow;
    
    string inputFolder = "optical flow output/";  // target_flown files are here
    string outputFolder = "optical flow output/"; // save analysis results here
    
    // Find available target_flown files
    int detectedMax = findMaxFrameNumber(inputFolder, "target_flown");
    
    if (detectedMax < 2) {
        cerr << "Error: Need at least 2 target_flown.XXXX.jpg files in " << inputFolder << endl;
        return false;
    }
    
    cout << "Detected target_flown files: 0001 to " << setw(4) << setfill('0') << detectedMax << endl;
    
    // Limit the range to what's available
    int actualStart = max(startFrame, 1);
    int actualEnd = min(endFrame, detectedMax);
    
    if (actualStart >= actualEnd) {
        cerr << "Error: Invalid frame range" << endl;
        return false;
    }
    
    cout << "Analyzing frames: " << setw(4) << setfill('0') << actualStart 
         << " to " << setw(4) << setfill('0') << actualEnd << endl;
    
    // Process each pair of consecutive target_flown images
    for (int frameIdx = actualStart; frameIdx < actualEnd; ++frameIdx) {
        cout << "Analyzing pair " << (frameIdx - actualStart + 1) 
             << "/" << (actualEnd - actualStart) << ": " 
             << setw(4) << setfill('0') << frameIdx << " -> " 
             << setw(4) << setfill('0') << (frameIdx + 1) << "..." << endl;
        
        
        // Generate filenames for consecutive target_flown images
        ostringstream oss1, oss2;
        oss1 << inputFolder << "target_flown." << setw(4) << setfill('0') << frameIdx << ".jpg";
        oss2 << inputFolder << "target_flown." << setw(4) << setfill('0') << (frameIdx + 1) << ".jpg";
        
        string frame1Name = oss1.str();
        string frame2Name = oss2.str();
        
        // Load the frames
        if (!frame1.ReadImage(frame1Name)) {
            cerr << "Error: Cannot load frame: " << frame1Name << endl;
            continue;
        }
        
        if (!frame2.ReadImage(frame2Name)) {
            cerr << "Error: Cannot load frame: " << frame2Name << endl;
            continue;
        }
        
        cout << "  Loaded: " << frame1Name << " and " << frame2Name << endl;
        
        // Compute optical flow between the frames
        if (!flowProcessor.ComputeFlow(frame1, frame2, flow)) {
            cerr << "Error: Failed to compute optical flow for frame pair " << frameIdx << endl;
            continue;
        }
        
        cout << "  Computed optical flow" << endl;
        
        // Save flow visualization for analysis
        ostringstream flowVizOss;
        flowVizOss << outputFolder << "analysis_flow." << setw(4) << setfill('0') << frameIdx << ".jpg";
        string flowVizFilename = flowVizOss.str();
        
        if (flowProcessor.SaveFlowAsImage(flow, flowVizFilename, 
                                          frame1.GetWidth(), frame1.GetHeight())) {
            cout << "  Saved flow analysis: " << flowVizFilename << endl;
        }
    }
    
    cout << "\n=== Analysis Complete ===" << endl;
    cout << "Analyzed " << (actualEnd - actualStart) << " frame pairs" << endl;
    cout << "Results saved in: " << outputFolder << endl;
    
    return true;
}

// Main function for program
int main(int argc, char* argv[]) {
    cout << "=== Enhanced Optical Flow Processor ===" << endl;
    
    // If no arguments, show usage
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    string mode = argv[1];
    
    if (mode == "apply") {
        
        // Apply mode - apply optical flow to target image
        if (argc != 3) {
            cerr << "Error: Apply mode requires target image filename" << endl;
            printUsage(argv[0]);
            return 1;
        }
        
        string targetImageName = argv[2];
        return runApplyMode(targetImageName) ? 0 : 1;
        
    } else if (mode == "analyze") {
        
        // Analyze mode - analyze target_flown sequence
        int startFrame = 1;
        int endFrame = 9999;
        
        if (argc >= 3) {
            startFrame = atoi(argv[2]);
        }
        if (argc >= 4) {
            endFrame = atoi(argv[3]);
        }
        
        // Basic input validation
        if (startFrame < 1 || endFrame < startFrame || endFrame > 9999) {
            cerr << "Error: Invalid frame range. Must be between 1 and 9999." << endl;
            return 1;
        }
        
        // Check available frames and validate against them
        string inputFolder = "optical flow output/";
        int detectedMax = findMaxFrameNumber(inputFolder, "target_flown");
        
        if (detectedMax < 2) {
            cerr << "Error: Need at least 2 target_flown.XXXX.jpg files in " << inputFolder << endl;
            return 1;
        }
        
        // Validate that requested range is within available frames
        if (startFrame > detectedMax) {
            cerr << "Error: Start frame " << startFrame << " is beyond available frames (1-" << detectedMax << ")" << endl;
            return 1;
        }
        
        if (endFrame > detectedMax) {
            cout << "Warning: End frame " << endFrame << " is beyond available frames. Limiting to " << detectedMax << endl;
            endFrame = detectedMax;
        }
        
        return runAnalyzeMode(startFrame, endFrame) ? 0 : 1;
        
    } else {
        cerr << "Error: Unknown mode '" << mode << "'" << endl;
        printUsage(argv[0]);
        return 1;
    }
}