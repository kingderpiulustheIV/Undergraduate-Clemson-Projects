/*************************
* Sean Farrell.
*CPSC 2311 Section 5
*spfarre@g.clemson.edu
*************************/
#include "functions.h"
/* Main function that takes in strings as parameters
* of input and output .txt files.
*/
int main(int argc, char** argv) {

    //Tells the user its checking the command line args.
    printf("cheking command line arguments\n");

    if (argc < 3) {
        printf("not enought argument: ./exe filename\n"); 
        exit(-1);
    }
    // Creates a file pointer pointing to the input file
    // the user specified the name of the input file in args.
    FILE* input = fopen(argv[1], "r");

    // Exits the program and prompts the user
    // if file could not be read or is NULL
    if(input==NULL) {
        printf("fp did not open\n"); 
        exit(-1);
    }

    //Creates a file pointer pointing to the output file
    //the user specified the name of the output file in args.
    FILE* output = fopen(argv[2], "w");

    // Exits the program and prompts the user
    // if file could not be created or is NULL
    if(output==NULL) {
        printf("fp did not open\n");
        exit(-1);
    }
    // Creates and reads from the input files to initialize a 2d array.
    int size = 0;
    int **mat = readFile(input, &size);

    // Prints the output of the 2d array to console.
    printMatrix(mat, size);

    // Prints the sum of the 2d array excluding elements in right and
    // left diagonals to the console.
    printf("Total = %d", calculateVal(mat, size));

    // writes the output of the 2d array to the outfile.
    // also writes the sum of the 2d array excluding elements in right and
    // left diagonals to the console.
    printOutput(output, mat, size);
    return 0;
}
