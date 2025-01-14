/*************************
* Sean Farrell.
* CPSC 2311 Section 5
* 3/6/2024
* LAB 7 Intro to PPM
* spfarre@clemson.edu
*************************/

#include "ppmUtil.h"

int main(int argc, char** argv) {
    // Creates a file pointer pointing to the input .ppm file
    // the user specified the name of the input .ppm file in args.
    if (argc < 3) {
        printf("Not enough arguments\n");
        exit(-1);
    }
    FILE* input = fopen(argv[1], "rb");

    // Exits the program and prompts the user
    // if file could not be read or is NULL
    assert(input != NULL);

    //Creates a file pointer pointing to the output .ppm file
    //the user specified the name of the output .ppm file in args.
    FILE* output = fopen(argv[2], "wb");

    // Exits the program and prompts the user
    // if file could not be created or is NULL
    assert(output != NULL);

    // Declares a header_t struct to store the header of the .ppm file.
    header_t header;

    // Reads the input ppm file.
    pixel_t* pixels = read(input, &header);

    // Writes the output ppm file.
    write(output, header, pixels);

    //Closes the input and output file pointers.
    fclose(input);
    fclose(output);

    //Frees the memory allocated for the pixels.
    freeMemory(pixels);
    return 0;
}