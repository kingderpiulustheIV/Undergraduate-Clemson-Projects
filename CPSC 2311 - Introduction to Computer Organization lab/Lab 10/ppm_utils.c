/*************************
* Sean Farrell
* CPSC 2310 Lab Section 5
* spfarre@g.clemson.edu
*************************/
#include "ppm_utils.h"

// Function that reads the header of the .ppm file.
header_t readHeader(FILE* fp) {
    header_t header;
    // Reads the header of the .ppm file
    fscanf(fp, "%2s", header.MAGIC_NUMBER);
    fscanf(fp, "%d", &header.WIDTH);
    fscanf(fp, "%d", &header.HEIGHT);
    fscanf(fp, "%d", &header.MAX_VAL);
    fgetc(fp);
    return header;
}
// Function that writes reads the header to a .ppm file.
void writeHeader(FILE* fp, header_t header) {
    fprintf(fp, "%s\n%d %d\n%d\n",
            header.MAGIC_NUMBER, header.WIDTH, header.HEIGHT, header.MAX_VAL);
}

// Function that writes the contents of a p6 .ppm file.
void write_p6(FILE* fp, image_t* image) {
writeHeader(fp, image->header);
// Writes the pixel data to the .ppm file
for (int i = 0; i < image->header.HEIGHT; i++) {
    for (int j = 0; j < image->header.WIDTH; j++) {
        fwrite(&image->pixels[i][j].R, sizeof(unsigned char), 1, fp);
        fwrite(&image->pixels[i][j].G, sizeof(unsigned char), 1, fp);
        fwrite(&image->pixels[i][j].B, sizeof(unsigned char), 1, fp);
    }
}
}

// Merge Sorts for pixel values for the removeNoise median
void sort (unsigned int* array, unsigned int size) {
    // If the size of the array is less than 2 no need to sort.
    if (size < 2)
        return;
    // Sets the pivot to the middle element of the array.
    unsigned int pivot = array[size / 2];
    unsigned int i, j;
    // Sorts the array
    for(i = 0, j = size - 1; i < j; i++, j--) {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i >= j)
            break;
        swap(&array[i], &array[j]);
    }
    sort(array, i);
    sort(array + i, size - i);

}

// Swaps the values of two unsigned integers for sort function
void swap(unsigned int* a, unsigned int* b) {

    // Swaps the values of two unsigned integers.
    unsigned int temp = *a;
    *a = *b;
    *b = temp;

}


// Allocates memory for a ppm image to be stored in the heap.
image_t* allocateMemory(header_t* header)  {
    // Allocates memory for the image_t struct instance.
    image_t* image = (image_t*)malloc(sizeof(pixel_t));
    image->header = *header;
    image->pixels = (pixel_t**)malloc(sizeof(pixel_t*) * header->HEIGHT);
    for ( int i = 0; i < header->HEIGHT; i++) {
        image->pixels[i] = (pixel_t*)malloc(sizeof(pixel_t) * header->WIDTH);
    }
    // Checks to make sure if memory was allocated
    if (image == NULL) {
        fprintf(stderr, "Failed to allocate memory for a an image.\n");
        exit(-2);
    }
    return image;

}

// Reads pixel data from a .ppm image
pixel_t readPixel(FILE* fp) {
    pixel_t pixel;
    fread(&pixel.R, sizeof(unsigned char), 1, fp);
    fread(&pixel.G, sizeof(unsigned char), 1, fp);
    fread(&pixel.B, sizeof(unsigned char), 1, fp);
    return pixel;
}

// Reads a .ppm image file
image_t* read_ppm(FILE* fp) {
        header_t header = readHeader(fp);
        image_t* image = allocateMemory(&header);
        for (int i = 0; i < header.HEIGHT; i++) {
            for (int j = 0; j < header.WIDTH; j++) {
                image->pixels[i][j] = readPixel(fp);
            }
        }
        return image;
}

// Frees memory of a ppm image stored in the heap
void freeImageMemory(image_t* image) {
    for (int i = 0; i < image->header.HEIGHT; i++) {
        free(image->pixels[i]);
    }
    free(image->pixels);
    free(image);
}
//Closes all file pointers of all .ppm images used in the program
void closeInputFiles(FILE* input[], int files) {
    for (int i = 0; i < files; i++) {
        fclose(input[i]);
    }
}

// Function that removes noise Average .ppm images
image_t* removeNoiseAverage(image_t* img[]) {
    header_t header = img[0]->header;
    // Allocates memory for the output image.
    image_t* output = allocateMemory(&header);
    // Loops through the pixels of the image and averages the pixel values.
    for (int i = 0; i < header.HEIGHT; i++) {
        for(int j = 0; j < header.WIDTH; j++) {
            int R = 0, G = 0, B = 0;
            for (int k = 0; k < TEN; k++) {
                R += img[k]->pixels[i][j].R;
                G += img[k]->pixels[i][j].G;
                B += img[k]->pixels[i][j].B;
            }
            // sets the pixel values as the average values between .ppm files.
            output->pixels[i][j].R = R / TEN;
        	output->pixels[i][j].G = G / TEN;
            output->pixels[i][j].B = B / TEN;
        }
    }
    return output;
}

// Function that removes noise Median .ppm images
image_t* removeNoiseMedian(image_t* image[]) {
    header_t header = image[0]->header;
    // Allocates memory for the output image.
    image_t* output = allocateMemory(&header);
    unsigned int R[NINE], G[NINE], B[NINE];
    // Loops through the pixels of the image and sorts the pixel values.
    for (int i = 0; i < header.HEIGHT; i++) {
        for(int j = 0; j < header.WIDTH; j++) {
            for (int k = 0; k < NINE; k++) {
                R[k] = image[k]->pixels[i][j].R;
                G[k] = image[k]->pixels[i][j].G;
                B[k] = image[k]->pixels[i][j].B;
            }
            sort(R, NINE);
            sort(G, NINE);
            sort(B, NINE);
            // sets the pixel values as the median values between .ppm files.
            output->pixels[i][j].R = R[4];
        	output->pixels[i][j].G = G[4];
            output->pixels[i][j].B = B[4];
        }
    }
    return output;
}

// Function that opens multiple input .ppm  files to be stored in the heap
void openInputFiles(char* argv, FILE* userInput[]) {
    char fileName[20];
    int files = (strcmp(argv, "average") == 0) ? TEN : NINE;
    for (int i = 0; i < files; i++) {
        sprintf(fileName, "%s_%03d.ppm", argv, i + 1);
        userInput[i] = fopen(fileName, "rb");
        // Checks to make sure the file was opened successfully.
        if (!userInput[i]) {
            perror("Error opening files");
            break; 
           }
    }
}