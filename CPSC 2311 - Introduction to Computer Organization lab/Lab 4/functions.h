/*************************
* Sean Farrell.
*CPSC 2311 Section 5
*spfarre@g.clemson.edu
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/* Parameters: File pointer fp pointing to input file to be read.
* *int size is an int pointer that specifies the dimensions of the square 2d array.
* Return:
* Returns and populates a 2d array of integers read from the file point fp.
 * This function reads input from a file into a 2d array.
*/
int** readFile(FILE* fp, int *size);


/* Parameters:  int** is a pointer pointing to a 2d array
* *int size is an int pointer that specifies the dimensions of the square 2d array.
* Return: Displays the 2d array as a matrix to the console.
* This function displays the 2d array as a matrix to the console.
*/
void printMatrix (int** mat, int num);


/* Parameters:  int** is a pointer pointing to a 2d array
* *int size is an int pointer that specifies the dimensions of the square 2d array.
* Return: outputs an int of the sum of all the elements that are not a diagonal
* from the top left to bottom right or a diagonal from bottom right
* to top right the 2d array.
* This function returns a sum of all elements in the 2d array that are
* not a diagonal element.
*/
int calculateVal(int** mat, int size);


/* Parameters: int size is the dimensions of the 2d square array.
* int row is the current row of the element being checked.
* int col is the current col of the element being checked.
* Return: true if a element is in the diagonal
* from bottom left to top right elements of 2d array. Otherwise, returns false.
* This function Returns true or false
* if the indexes of the element checked are a right diagonal.
*/
bool isRightDiagonal(int size, int row, int col);


/* Parameters: int row is the current row of the element being checked.
* int col is the current col of the element being checked.
* Return: returns true  if a element is in the diagonal
* from top left to bottom right elements of 2d array. Otherwise, returns false.
* This function Returns true or false
* if the indexes of the element checked are a left diagonal.
*/
bool isLeftDiagonal(int row, int col);


/* Parameters:   File pointer fp pointing to output file to be written.
* int** mat is a pointer pointing to a 2d array
* int size is an int pointer that specifies the dimensions of the square 2d
* array.
* Return: writes to the output file the 2d array as a matrix as well as well
* as the sum of the matrixexlcuding diangolasbelow the contents of the matrix.
* This function writes to the output file the 2d array and the total sum of
* the array excluding diagonals.
*/
void  printOutput(FILE *fp, int** mat, int size);

#endif