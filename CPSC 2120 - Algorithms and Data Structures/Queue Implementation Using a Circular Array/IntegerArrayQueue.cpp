 /*
 * Date Submitted: 9/26/2023
 * Lab Section: 6
 * Assignment Name: Queue Implementation Using a Circular Array
 */
#include "IntegerArrayQueue.h"

// Function that sets the element of the array from the int parameter
// Also returns true or false if the last element in the array is not populated.
bool IntegerArrayQueue::enqueue(int value) {
	
	// returns false if the back array element is equal to the front or populated. 
	
	if ((back + 2) % size == front)
		return false;
	
	//Returns true if the back is not populated and sets the back array to int value.
	
	else {
		back = (1 + back) % size;
		array[back] = value;
		return true;
	}
}

// Fuctuion that checks if the queue is empty if not it outputs the current value of the q and deques the front element.

int IntegerArrayQueue::dequeue(){
	
 // Returns 0 if the back is equal meaining if it the queue is empty.	
    if (((back + 1) % size) == front)
		return 0;
 
 else {
	 
	// If the queue is full or populated the fuction returns the front element of the array.
	
	int temp = array[front];
	    // Decreases the front size due to decreacing the q by 1.
	    
		front = (1 + front) % size;
	    return temp;	 
 	}
 }
	