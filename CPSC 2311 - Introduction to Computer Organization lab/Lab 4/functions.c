/*************************
* Sean Farrell.
*CPSC 2311 Section 5
*spfarre@g.clemson.edu
*************************/
#include "functions.h"

// Reads input file and allocates memory for 2D array.
// ALso sets information from the input file to be
// the values of the elements of the 2d array
int** readFile(FILE* fp, int *size)
{
    // Opens input .txt file (argv[1])
    fscanf(fp, "%d", size);
    int num = *size;

    // uses malloc to allocate memory for the 2d array
    // using a 2d array implementation
    int** mat = (int**)malloc(num * sizeof(int*));
    for(int index = 0; index < num; index++)
        mat[index] = (int*)malloc(num * sizeof(int));

    // Sets every element of the 2d array of data from the .txt file
    for(int row = 0; row < num; row++) {
        for(int col = 0; col < num; col++) {
            fscanf(fp, "%d", &mat[row][col]);
        }
    }

    // Returns the populated 2D int array.
    return mat;
}

// prints the content of the 2d array to the console as a matrix.
void printMatrix (int** mat, int num) {

    //loops through every element printing the contents
    // formatted to the lab 4 prompts description.
    for(int row = 0; row < num; row++) {
        for(int col = 0; col < num; col++) {
            printf("%.2d\t", mat[row][col]);
        }
        printf("\n");
    }
    
}
// Simple function that checks to see if an element of the
// array is a diagonal from bottom left to right top of the 2d array
bool isRightDiagonal( int size, int row, int col) {

    //condition that checks if an element to be in the right diagonal.
    if(row + col == size - 1)
        return true;
    return false;


}

// Simple function that checks to see if an element of the
// array is a diagonal from to left to  the bottom right of the 2d array
bool isLeftDiagonal(int row, int col) {

    //condition that checks if an element to be in the left diagonal.
    if( row == col)
        return true;
    return false;
}

// Function that calculates the sum of every element of the array excluding
// elements in the right and left diagonals
int calculateVal(int** mat, int size) {

    // initializes the sum to 0
    int total = 0;

    // Loops through every element of the 2d array
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            // Adds to the sum if the array element is
            // not in the left or right diagonals.
           if (!isRightDiagonal(size, row, col) && !isLeftDiagonal(row, col)) {
                    total += mat[row][col];
           }
        }
    }

    // Returns sum of the elements in the array
    // excluding right or left elements in the diagonals.
    return total;
}

// Function that writes to the output file (argv[2]) the matrix
// of the contents of the 2d array as well as the sum
// excluding elements int the right and left diagonals of the 2D array.
void  printOutput(FILE *fp, int **mat, int size){

    // Loops to write every element of the array as a matrix
    // formatted as specified by the prompts in lab 4 to the output file.
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            fprintf(fp,"%.2d\t", mat[row][col]);
        }
        fprintf(fp,"\n");
    }

    // Writes the sum excluding elements in right and left
    // diagonals to the output file.
    fprintf(fp, "Total = %d\n", calculateVal(mat, size));
}