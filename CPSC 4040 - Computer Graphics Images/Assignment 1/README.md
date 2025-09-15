# Image Viewer Assignment

## Overview
This assignment implements a versatile image viewer application capable of handling multiple image formats including:
- PNG (.png)
- JPEG (.jpg)
- TIFF (.tif)
- OpenEXR (.exr)

The program provides basic image viewing functionality and the ability to save images in JPEG format.

## Features
- Multi-format image support
- Image display capabilities
- JPEG export functionality
- Support for high dynamic range EXR images

## File Structure
```
Assignment 1/
├── base/           # Source code files
├── include/        # Header files
├── bin/           # Image samples and binaries
└── lib/           # Library files
```

## Sample Images
The following test images are provided in the `bin/` directory:
- `24bit.png` - Standard PNG image
- `4k.jpg` - High-resolution JPEG image
- `autumn.tif` - TIFF format image
- `CandleGlass.exr`, `Tree.exr`, `WideColorGamut.exr` - OpenEXR format images
- `dice.png`, `dice_converted.tif` - Sample conversion images
- `flag.png` - Test PNG image
- `background.jpg` - Sample JPEG image

## Building the Project
The project can be built using the provided Makefile:

```bash
make
```

## Dependencies
- OpenImageIO library for image I/O operations
- OpenEXR library for handling .exr files
- using OpenEXR 2.5.8 
- Found up one folder in the build folder.

## Implementation Details
The viewer is implemented using the following key components:
- `ImageViewer` class for handling the viewing interface
- `ImgProc` for image processing operations
- `oiiostuff` for handling image I/O operations

## Usage
After building the project, you can:
1. Load any supported image file (.png, .jpg, .tif, .exr)
2. View the image in the viewer window
3. Save the current image as a JPEG file by pressing j on the keyboard

## Notes
- The viewer supports various image formats through OpenImageIO
- EXR files are supported for high dynamic range imaging
- Images can be exported to JPEG format for compatibility