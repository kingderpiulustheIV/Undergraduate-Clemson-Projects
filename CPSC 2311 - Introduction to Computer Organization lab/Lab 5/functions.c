/**************************
Sean Farrell
CPSC 2310 spring 2024
Lab Section 5
UserName: spfarre
Instructor: Dr. Yvon Feaster
*************************/
#include "functions.h"


// Function that writes information from an input file
// to a node of a linked list.
node_t* readNodeInfo(FILE* input) {

    // Allocates memory on the heap of the new node
    node_t* node = (node_t*)malloc(sizeof(node_t));

    // populates the node from the input file.
    if(fscanf(input, "%49[^,],%49[^,],%d,%d,%d,%9[^,],%14[^\n]\n",
              node->lastName, node->firstName, &node->birthday.month, &node->birthday.day,
              &node->birthday.year, node->major, node->classStanding) == 7) {
        node->next = NULL;
        return node;
    }

    // Deletes the node if it cant be populated.
    else {
        free(node);
        return NULL;
    }

}
// Adds a node to the linked list
void add(node_t** node, node_t** head) {
    if (*head == NULL) {
        *head = *node;
        return;
    }
    else {
        node_t* temp = *head;

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = *node;
    }
}

// Creates a list.
node_t* createList(FILE* fp , node_t** head) {

    while(!feof(fp)) {
        node_t *newNode = readNodeInfo(fp);
        if (newNode != NULL) {
            add(&newNode, head);
        }
//        add(newNode, head);
    }

    return *head;

}

// Deletes the list and nodes to free up memory
void deleteList(node_t** head) {
    node_t* current = *head;
    node_t* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
}


// Prints a formatted boarder to the output file.
void printBorder(FILE* fp) {
    fprintf(fp, "**********"
                "**********************************************************************");
}

// Prints each student information from a linked list to an output file.
void printList(FILE* fp, node_t* list) {
    if(list == NULL) {
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }

    printBorder(fp);
    fprintf(fp, "\nList Info:\n");

    for (node_t* current = list; current != NULL; current = current->next) {
        fprintf(fp, "Name:\t%s %s\n", current->firstName, current->lastName);
        fprintf(fp, "Date of Birth:\t%d %d, %d\n", current->birthday.month,
        current->birthday.day, current->birthday.year);
        fprintf(fp, "Major:\t%s\n", current->major);
        fprintf(fp, "Year:\t%s\n\n", current->classStanding);
    }
    printBorder(fp);
    
}
