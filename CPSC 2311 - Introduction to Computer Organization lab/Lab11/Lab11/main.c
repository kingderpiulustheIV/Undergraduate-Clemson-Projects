/*************************
* Sean Farrell
* CPSC 2310 Lab Section 5
* spfarre@g.clemson.edu
*************************/
#include <stdio.h>

int absVal(int* arr, int length);

int main(){
	int a[] = {1, 2, 3, 4, 5};
	int b[] = {-1, 1};
	int c[] = {20, 2, -3, 5};
	
	printf("Absolute value of array a: %d\n", absVal(a, 5));
	printf("Absolute value of array b: %d\n", absVal(b, 2));
	printf("Absolute value of array c: %d\n", absVal(c, 4));

	return 0;

}
