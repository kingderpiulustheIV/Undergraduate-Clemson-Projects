/*
 * Name: Sean Farrell
 * Date Submitted: 11/27/2023
 * Lab Section: Section 006
 * Assignment Name: Min-Heap Implementation Using a Vector
 */
#include <iostream>
#include "minHeap.h"

using namespace std;

// function that Moves the elemets upwards in the heap
void minHeap::siftUp(int spot) { 
    int child = spot;
    int parent = (spot - 1) / 2;

 // compares the child elemets 
    while (child != 0 && heap[parent] > heap[child]) {
        
        //swap child and parent elemets 
        int temp = heap[parent]; 
        heap[parent] = heap[child];
        heap[child] = temp;

        // Current parent element is a child element
        child = parent;  
        
        // Creates a new parent element
        parent = (parent - 1) / 2;  
    }
}

// Function that moves an element down the heap 
void minHeap::siftDown(int pos) {

    int parent = pos;  // Parent element
    int left = 2 * parent + 1; //left child element
    int right = 2 * parent + 2; //right child element
    int swap = -1;
    
    // Checks left element
    if (left < (int)heap.size() && heap[left] < heap[parent])  
        swap = left;
   
    // checks right element
    if (right < (int)heap.size() && heap[right] < heap[parent]) 
    {
        // Swaps elements
        if (swap == -1)
            swap = right;
        else if (heap[right] < heap[left])
            swap = right; 
    }

    // does not swap element if swap value doesn't change
    if (swap == -1)
        return; 
    // Swaps parent element with the swapped element
    int temp = heap[parent]; 
    heap[parent] = heap[swap];
    heap[swap] = temp;
    
    // Calls the current function recursively. 
    siftDown(swap); 

}
minHeap::minHeap(vector<int> data) {
    // resets heap size
    heap.resize(0); 

    // populates the vector in the heap.
    for (int i = 0; i < (int)data.size(); i++) {
        heap.push_back(data[i]);
    }
    
    // Bottom up insertion for the heap
    for (int i = heap.size() - 1; i >= 0; i--) {
        siftDown(i);
    }
}

// Function that inserts a integer value into the heap
void minHeap::insert(int value) {
    // Inserts integer
    heap.push_back(value);
    
    // moves the element up in the heap
    int spot = heap.size() - 1;
    siftUp(spot);
}

// Function that removes the element at the end of the heap and returns its value
int minHeap::removeMin() {
    // Returns -1 if the heap size is 0.
    if (heap.size() == 0)
        return -1; 

    // Sets heap[0] to the last elements value in the heap
    int temp = heap[0]; 
    heap[0] = heap[heap.size() - 1];
    
    // Sets the last heap element value to temp
    heap[heap.size() - 1] = temp;
    
    // Deletes element of the heap
    heap.pop_back(); 
    
    // Moves heap[0] to maintain minHeap
    siftDown(0); 

    return temp;
}