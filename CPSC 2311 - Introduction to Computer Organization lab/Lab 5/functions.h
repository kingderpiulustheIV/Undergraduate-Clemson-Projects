/**************************
Sean Farrell
CPSC 2310 spring 2024
Lab Section 5
UserName: spfarre
Instructor: Dr. Yvon Feaster
*************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>

// Struct that contains date information with months,
// days, and years for students.
typedef struct birthday {
    int month;
    int day;
    int year;

}birth_day;
// Struct that contains all information of a student
// profile thats a node of a linked list.
typedef struct LinkedList{
    char firstName[50];
    char lastName[50];
    char major[10];
    char classStanding[15];
    birth_day birthday;
    struct LinkedList *next;

}node_t;

/* Parameters: File pointer of file of a file to be
 * read. Second Parameter double pointer pointing to the head node
 * of a linked list
 *
 * Return: Returns a pointer to the head node of the linked list
 *
 * Description: This function adds all the nodes able to be populated from
 * the specified input file creating a populated linked list using the add function.
 */
node_t* createList(FILE*, node_t**);

/* Parameters: pointer pointing to a node to be added to the list.
 *  pointer pointing to the head node of the linked list.
 *
 * Return: Returns void.
 *
 * Description:  This function adds a node to the linked list.
 */
void add(node_t** node, node_t** head);

/* Parameters: File pointer of file of a file to be
 * read.
 *
 * Return: Returns a populated node of the linked list struct of
 * students information from the file specified by the file pointer parameter.
 *
 * Description: This function reads from a file and stores its information to a node
 * to be added to a linked list
 */
node_t* readNodeInfo(FILE* input);

/* Parameters: File pointer of file of a file to be
 * written. Second Parameter double pointer pointing to the head node
 * of a linked list
 *
 * Return: nothing
 *
 * Description: THis function writes the entire linked list data of each node to a .txt
 * file formatted to meet the labs direction's specifications.
*/
void printList(FILE*, node_t*);

/* Parameters: File pointer of file of a file to be written.
 *
 * Return: nothing
 *
 * Description: This function prints "*" to the specified file 80
 * times to meet the formatting guidelines of this lab.
 */
void printBorder(FILE*);

/* Parameters: double pointer pointing to the head node
 * of a linked list
 *
 * Return: nothing
 *
 * Description: This function deletes the Linked list frees up the memory.
*/
void deleteList(node_t** );
#endif //FUNCTIONS_H
