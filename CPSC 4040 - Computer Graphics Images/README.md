# CPSC 4040 - Computer Graphics Images

## Course Description
Introduction to computer graphics with a focus on image processing, rendering, and manipulation. Students learn fundamental graphics algorithms, color theory, transformations, and image filtering. Course covers both theoretical concepts and practical implementation of graphics applications using modern libraries. note all assignments are constructive and build off the previous assignment. 

## Learning Objectives
- Understand fundamental concepts of computer graphics and image processing
- Implement image manipulation algorithms (filtering, transformations, compositing)
- Master color spaces and color management
- Apply linear algebra to graphics transformations
- Work with image file formats and libraries (OpenImageIO)
- Develop interactive image viewing applications
- Understand rendering pipelines and rasterization
- Implement fractal generation and procedural graphics
- Create animations and video sequences

## Assignments

### Assignment 1
Introduction to image processing basics and OpenImageIO library. Implementation of basic image viewers and renderers.

### Assignment 2
Advanced image manipulation including compositing, blending, and transformation operations.

### Assignment 3
Image filtering, convolution, and spatial domain operations. Complex image processing algorithms.

### Assignment 4
Procedural image generation including Julia set fractals and animation sequences. Creation of video from image sequences.

### Assignment 5
Advanced rendering techniques and final project incorporating optical flow of a series of images into a video. Video output generation.

## Technology Stack

### Programming Language
- **C++**: Primary language for graphics programming (using .C file extension)

### Graphics Libraries
- **OpenImageIO**: Open-source library for reading, writing, and processing images
- Support for multiple image formats (.exr, .jpg, .png, .tif)
- High Dynamic Range (HDR) image support

### Image Formats
- **EXR**: High dynamic range format
- **JPEG**: Standard compressed image format
- **PNG**: Lossless compressed format
- **TIFF**: Tagged Image File Format

### Mathematics
- **Linear Algebra**: Matrix operations and transformations
- **Complex Numbers**: For fractal generation (Julia sets)
- **Color Theory**: Color space transformations and management

### Build Tools
- **Makefile**: Build automation
- **GCC/G++**: C++ compiler
- Static libraries (.a files)

### Development Environment
- C++ compiler with C++11 or later support
- OpenImageIO library and dependencies
- Image viewing capabilities
- Video encoding tools (for animation output)

### Components Implemented
- Image renderers
- Interactive image viewers
- Image processing algorithms
- Matrix operations
- Procedural generation algorithms
- Animation frame generation

## Setup and Requirements

### Software Requirements
- C++ compiler GCC 7.0+,
- OpenImageIO library installed
- Make utility for building
- Image viewer for testing outputs
- Video encoder (FFmpeg) for creating animations

### Hardware Requirements
- Quad core CPU for image processing
- Sufficient RAM for handling large images

### Build Environment
- Unix-like environment (Linux, macOS, or WSL on Windows)
- Standard C++ build tools
- OpenImageIO development headers and libraries
- Xubuntu x86-64

### Project Structure
- `base/`: Source code files (.C)
- `include/`: Header files
- `lib/`: Static libraries
- `bin/`: Compiled executables and output images
- `Makefile`: Build configuration

## Work Type
This class entails **individual assignments** with implementation in C++ using computer graphics libraries.

## Key Concepts Covered
- Image I/O and file format handling
- Color spaces and color management
- Image transformations and geometric operations
- Filtering and convolution
- Image compositing and alpha blending
- Procedural generation and fractals
- Animation and video sequence creation
- OpenImageIO API and image processing pipelines
