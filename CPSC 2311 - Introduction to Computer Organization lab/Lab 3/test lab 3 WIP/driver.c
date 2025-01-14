/*************************
* Sean Farrell.
*CPSC 2311 Section 5
*spfarre@g.clemson.edu
*************************/
#include "functions.h"

int main(int argc, char* argv[]){
    //Writes and or creates a file specified by the command line argument
    FILE* Out = fopen(argv[1], "w");

    //Makes sure the file is open properly
    assert(Out != NULL);

    //executes the print program with the open file
    printMonths(Out);

    //Closes program
    fclose(Out);

    // end of main
    return 0;
}




