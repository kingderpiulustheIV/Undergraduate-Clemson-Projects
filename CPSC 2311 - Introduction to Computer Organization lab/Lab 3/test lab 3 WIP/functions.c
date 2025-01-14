/*************************
* Sean Farrell.
*CPSC 2311 Section 5
*spfarre@g.clemson.edu
*************************/
#include "functions.h"
void printMonths(FILE* Output) {
    // Enumerated types for each month
    enum month{January, February, March, April, May,
            June, July, August, September, October, November, December};

    //Pointer string array of the string of each month's name
    const char *monthNames[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
    };
    // writes the numerical order of each month and its name to the output file
    for(int i = January; i <= December; i++) {
        fprintf(Output, "%2d %12s\n", i+1, monthNames[i]);
    }
}