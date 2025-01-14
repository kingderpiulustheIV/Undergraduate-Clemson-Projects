/*************************
* Sean Farrell
* CPSC 2310 Lab Section 5
* spfarre@g.clemson.edu
*************************/
#include "ppm_utils.h"
int main(int argc, char **argv) {

    //Error checks to make sure the user enters the correct amount of arguments
    if (argc != 3) {
        //Prompts the user if they entered the wrong amount of arguments.
        printf("Wrong CMD args.\nFormat should look like this "
        "<executable> <string average or median> <output file name>\n"
        "/a.out avarege output.ppm");
        return -1;
    }

    //Sets the method and output file name to the arguments entered.
    char *method = argv[1];
    char *outputFileName = argv[2];

    //Checks to see if the method entered by the user is average or median.
    int files = (strcmp(argv[1], "average") == 0) ? TEN : NINE;

    //Creates an array of file pointers and an array of image pointers.
    FILE *inputFiles[files];
    image_t *images[files];

    //Checks to see if the method entered by the user is valid input.
    if (strcmp(method, "average") != 0 && strcmp(method, "median") != 0) {
        printf("Invalid method. Choose 'average' or 'median'.\n");
        return -1;
    }

    //Opens the input files.
    openInputFiles(method, inputFiles);
    for (int i = 0; i < files; i++) {
        images[i] = read_ppm(inputFiles[i]);
    }
    // Creates an output image pointer.
    image_t *outputImage;

    // Checks to see if the method entered by the user is average or median.
    if (strcmp(method, "average") == 0)
        //Removes the noise average from the images.
        outputImage = removeNoiseAverage(images);
    else
        // Removes the noise median from the images.
        outputImage = removeNoiseMedian(images);
    // Creates the output file.

    FILE *outputFile = fopen(outputFileName, "wb");
    // Checks to see if the output file was created.
    if (!outputFile) {
        perror("Could not write to output file.");
        return -1;
    }
    // Writes the output image to the output file.
    write_p6(outputFile, outputImage);
    for (int i = 0; i < files; i++) {
        freeImageMemory(images[i]);
    }
    // Frees the memory of the output image and closes file pointers.
    freeImageMemory(outputImage);
    closeInputFiles(inputFiles, files);
    fclose(outputFile);
    return 0;
}