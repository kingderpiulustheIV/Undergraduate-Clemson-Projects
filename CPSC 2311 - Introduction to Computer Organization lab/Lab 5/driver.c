/**************************
Sean Farrell
CPSC 2310 spring 2024
Lab Section 5
UserName: spfarre
Instructor: Dr. Yvon Feaster
*************************/
#include "functions.h"
int main(int argc, char** argv) {
    // Checks to see if there are enough args
    // to specify input and output file
    if (argc < 3) {
        printf("not enought arguments.\n");
        exit(-1);
    }

    // Creates a file pointer pointing to the input file
    // the user specified the name of the input file in args.
    FILE* input = fopen(argv[1], "r");

    // Exits the program and prompts the user
    // if file could not be read or is NULL
    assert(input != NULL);

    //Creates a file pointer pointing to the output file
    //the user specified the name of the output file in args.
    FILE* output = fopen(argv[2], "w");

    // Exits the program and prompts the user
    // if file could not be created or is NULL
    assert(output != NULL);

    //Creates the head node of the linked list
    node_t* head = NULL;

    // populates the linked list of student information from the input file.
    createList(input, &head);

    // Writes to an output file of the information stored in the Linked list.
    printList(output, head);

    // Deletes the linked list frees memory.
    deleteList(&head);
    
    // Closes input and output file pointers.
    fclose(input);
    fclose(output);
    return 0;

}
