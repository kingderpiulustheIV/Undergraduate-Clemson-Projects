/*************************
* Sean Farrell.
* CPSC 2311 Section 5
* 3/6/2024
* LAB 7 Intro to PPM
* spfarre@clemson.edu
*************************/

#include "ppmUtil.h"

// Function that Reads the input .ppm file
pixel_t* read(FILE* fp, header_t* header) {

    // Reads the header of the ppm file
    readHeader(fp, header);

    // Reads the pixels of the ppm file
    return readPixels(fp, *(header));

}

// Function that sets an instance of the header_t struct
// to the header of the ppm file
void readHeader(FILE* fp, header_t* header) {

    // Reads the type of ppm
    ckComment(fp);
    fscanf(fp, "%2s\n", header->type);

    // Read width, height, and maximum color value
    ckComment(fp);
    fscanf(fp, "%u\n", &header->width);
    ckComment(fp);
    fscanf(fp, "%u", &header->height);
    ckComment(fp);
    fscanf(fp, "%u", &header->maxVal);
    ckComment(fp);
    fscanf(fp, "%u", &header->maxVal);
}

// Function that skips comments in the ppm file
void ckComment(FILE* fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '#') {
            while ((c = fgetc(fp)) != EOF && c != '\n') {
                // Skip characters until file pointer reaches a \n
            }
        } else if (c != '#') {

            // Put back the non-comment characters in the header
            ungetc(c, fp);
            break;
        }
    }
}

pixel_t* allocatePixMemory(header_t header) {
    // Allocates memory for the pixels using malloc
    pixel_t* buffer = (pixel_t*)malloc(sizeof(pixel_t)
            * header.width* header.height);

    // Checks to make sure if memory was allocated
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory to pixel buffer.\n");
        exit(-2);
    }
    return buffer;
}

// Function that reads the pixels of the ppm file and returns
// the pixel buffer.
pixel_t* readPixels(FILE* fp, header_t header) {

    // Allocates memory for the pixels using the allocatePixMemory function
    pixel_t* buffer = allocatePixMemory(header);

    // Calculates the number of pixels in the ppm file
    size_t numPixels = header.width * header.height;

    // Reads the pixel data from the ppm file and sets it to the buffer
    size_t readCount = fread(buffer, sizeof(pixel_t), numPixels, fp);

    // Checks to make sure if the pixel data was read properly.
    if (readCount != numPixels) {
        fprintf(stderr, "Failed to read pixel data.\n");
        free(buffer);
        exit(-3);
    }

    // Returns the pixel buffer with the pixel data
    return buffer;
}

// Function that writes the header of the ppm file with no comments
void writeHeader(FILE* fp, header_t header) {
    fprintf(fp, "%s\n%u %u %u",
            header.type, header.width, header.height, header.maxVal);
}

// Function that writes the pixel data to the ppm file.
void writePixels(FILE* fp, pixel_t* pixels, header_t header) {

    // Had to increase the image size by 1 to get it to work with Imagemagik.
    // Otherwise, it worked with all other imageviewer 
	// programs in the SOC Vms.
    size_t imageSize = header.width * header.height + 1;
    fwrite(pixels, sizeof(pixel_t), imageSize, fp);
}

// Function that writes the header and pixel data to the output .ppm file
void write(FILE* fp, header_t header, pixel_t* pixels) {
    writeHeader(fp, header);
    writePixels(fp, pixels, header);
}
// Frees the memory allocated for the pixel buffer
void freeMemory(pixel_t* pixels) {
    free(pixels);
}