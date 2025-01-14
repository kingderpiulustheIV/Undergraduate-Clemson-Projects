/*************************
* Sean Farrell.
* CPSC 2311 Section 5
* 3/6/2024
* LAB 7 Intro to PPM
* spfarre@clemson.edu
*************************/

#ifndef ppmUtil_H
#define ppmUtil_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

// Struct stores the color data of an individual pixel of a .ppm file
typedef struct Pixel
{
    unsigned char r, g, b;
}pixel_t;

// Struct stores the header data of a .ppm file
typedef struct Header
{
    // Stores the type of the .ppm file
    char type[3];

    // Stores the width of the .ppm file
    unsigned int width;

    // Stores the height of the .ppm file
    unsigned int height;

    // Stores the maximum color value of the .ppm file
    unsigned int maxVal;
}header_t;

/* Parameters: File*- pointing to a file pointer that is the input
* .ppm to be read, header_t struct is a
* pointer of an instance of a header_t struct
* that will store the header of the input .ppm file
*
* Return: nothing
*
* This function reads a header from a .ppm file and
* stores an instance of header_t with the data from the input file
*/
void readHeader(FILE*, header_t*);

/* Parameters: File*- pointing to a file pointer that is the input
* .ppm to be read, header_t struct is an instance of header t struct
* that will be used as information on how
* to read the pixels from the input .ppm file.
*
* Return: Pointer pointing to the pixel buffer
*
* This function reads the pixels from a .ppm file and
* stores the pixels in a pixel buffer and returns a pointer to the buffer.
*/
pixel_t* readPixels(FILE*, header_t);

/* Parameters: File*- pointing to a file pointer that is the input
* .ppm to be read, header_t* struct is a
* pointer of an instance header_t struct
* that will be used as information on how
* to read the pixels from the input .ppm file.
*
* Return: Pointer pointing to the pixel buffer.
*
* This function reads the header and pixels from a .ppm file.
*/
pixel_t* read(FILE*, header_t*);

/* Parameters: File*- pointing to a file pointer that is the output
* .ppm to be written, header_t struct is an instance of header t struct
* that will print its information to the output file.
*
* Return: nothing
*
* This function writes the information from a header_t struct to a .ppm file.
*/


void writeHeader(FILE*, header_t);

/* Parameters: File*- pointing to a file pointer that is the output
* .ppm to be witten, header_t struct is an instance of header t struct
* that will be used as information on how
* to write the pixels to the output .ppm file.
* pixel_t* is a pointer of the pixel buffer
* that will be written to the output file
*
* Return: Nothing
*
* This function Writes the pixels from a pointer pointing to a pixel buffer
* to an output .ppm file.
*/
void writePixels(FILE*, pixel_t*, header_t);

/* Parameters: File*- pointing to a file pointer that is the input
* .ppm to be read, header_t struct is an instance of header t struct
* that will be used as information on how
* to write the pixels to the output .ppm file.
* pixel_t* is a pointer of the pixel buffer
* that will be written to the output file.
*
* Return: Nothing
*
* This function Writes header information from an instance of the header_t
* struct and the pixel data from a pixel buffer to an output.ppm file.
*/

void write(FILE*, header_t, pixel_t*);

/* Parameters: header_t struct is an instance header_t struct
* that will be used as information on how
* to dynamically allocate memory for the pixel buffer.
*
* Return: Pointer pointing to the pixel buffer.
*
* This function dynamic allocates memory to the pixel buffer
* using malloc function specified by the header data.
*/
pixel_t* allocatePixMemory(header_t);

/* Parameters: pixel_t* is a pointer pointing
* to the pixel buffer that will be deleted and freed from memory.
*
* Return: Nothing
*
* This function frees the memory allocated for the pixel buffer.
*/
void freeMemory(pixel_t*);

/* Parameters: File*- pointing to a file pointer that
 * is the input .ppm being read.
*
* Return: Nothing
*
* This function prevents the program from reading comments in the header.
*/
void ckComment(FILE*);
#endif