THIS README.md is a guide to build and operate the Optical flow program as well as trobleshooting.

Make sure your terminal for commands listed below unless specified are in this projects root folder which is "./Assignment 5". 

results_video.mp4 is located in "/optical flow output" subfolder also have a copy in the projects root folder for ease of access

### Build Instructions

```bash
# Build all components
make

# Build only optical flow program
make opticalflow

# Build only image viewer
make imgviewer

# Clean all build artifacts
make clean

# Clean only optical flow artifacts
make clean_opticalflow
```


### Complete Processing Pipeline

```bash
# 1. Extract video frames of optical flow data
# make sure your terminal is in "optical flow input" folder
ffmpeg -i input_video.mp4 "optical flow input/frame.%04d.jpg"

# 2. Apply optical flow to target image
./bin/opticalflow apply my_target.jpg

# 3. Analyze specific frame range
# this command is optional as its used for debugging/visualization purposes
./bin/opticalflow analyze 1 100

# 4. View results
./bin/imgviewer -image "optical flow output/target_flown.0050.jpg"
./bin/imgviewer -image "optical flow output/analysis_flow.0025.jpg"

# 5. Compile results into a video
# make sure your terminal is in "optical flow output" folder
 ffmpeg -i target_flown.%04d.jpg results_video.mp4
```
## More in-depth Usage guide

### 1. Video Frame Extraction

First, extract frames from your video file:

```bash
# Extract frames from video (creates frame.0001.jpg to frame.NNNN.jpg)
# make sure your terminal is in "optical flow output" folder
ffmpeg -i js.mp4 "optical flow input/frame.%04d.jpg"
```

### 2. Optical Flow Processing

#### Apply Mode - Sequential Flow Application

Apply optical flow sequentially to a target image using all available frames:

```bash
./bin/opticalflow apply <target_image>

# Example
./bin/opticalflow apply opticalflowtarget.jpg
```

**Process:**
1. Loads target image
2. Detects all available frames in `optical flow input/`
3. Computes optical flow between consecutive frames
4. Applies flow sequentially to target image
5. Saves results as `target_flown.XXXX.jpg` in `optical flow output/`

#### Analyze Mode - Flow Pattern Analysis

Analyze optical flow patterns between specific image sequences:

```bash
./bin/opticalflow analyze <start_frame> <end_frame>

# Example: Analyze frames 1 through 50
./bin/opticalflow analyze 1 50

# Example: Analyze frames 100 through 200
./bin/opticalflow analyze 100 200
```

**Process:**
1. Loads target_flown.XXXX.jpg sequences from `optical flow output/`
2. Computes optical flow between consecutive pairs
3. Generates flow visualization images
4. Saves analysis as `analysis_flow.XXXX.jpg`

### 3. Image Viewing

View any processed images using the built-in image viewer:

```bash
./bin/imgviewer -image <image_file>

# Examples
./bin/imgviewer -image "optical flow output/target_flown.0001.jpg"
./bin/imgviewer -image "optical flow output/analysis_flow.0001.jpg"
```

### Quick Analysis

```bash
# For existing target_flown sequences, analyze flow patterns
./bin/opticalflow analyze 10 20

# View flow visualization of a certian frame
./bin/imgviewer -image "optical flow output/analysis_flow.0015.jpg"
```

### 4. Video Frame creation

Takes all of the target_flownXXXX.jpg images and creates a .mp4 video file

```bash
# Copies frame images into a video (creates results_video.mp4 from target_flown.0001.jpg to target_flown.NNNN.jpg)
# # make sure your terminal is in "optical flow output" folder
 ffmpeg -i target_flown.%04d.jpg results_video.mp4
```

## Output Interpretation

### Target Flow Images (`target_flownXXXX.jpg`)
- Sequential application of optical flow to the original target
- Shows how the target image would appear if warped by the computed flow
- Useful for understanding cumulative motion effects

### Analysis Flow Images (`analysis_flowXXXX.jpg`)
- Color-coded visualization of optical flow vectors
- Red/Green channels represent horizontal/vertical flow components
- Brightness indicates flow magnitude
- Useful for debugging and flow pattern analysis

## Troubleshooting

### Common Issues

1. **"Could not open image file"**
   - Verify file paths and naming convention
   - Ensure images are in correct directories

2. **"No frames detected"**
   - Check that frames exist in `optical flow input/`
   - Verify frame numbering (0001-9999 format)

3. **Build errors**
   - Ensure OpenImageIO, OpenEXR is properly installed
   - Check compiler C++14 support
