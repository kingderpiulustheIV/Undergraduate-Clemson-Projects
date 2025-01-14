/*
 * Name: Sean Farrell
 * Date Submitted: 9/5/2023
 * Lab Section: 001
 * Assignment Name: Lab 1: Linked List Based Stacks and Queues
 */

#pragma once
#include "List.h"

// This class represents a Stack implemented via Linked List
// Do not modify anything in the class interface
template <class T> class ListStack {

private:
  List<T> stack;

public:
  ListStack();
  ~ListStack();
  int size();
  bool empty();
  void push(T);
  T pop();
  // Print the name and this ListStack's size and values to stdout
  // This function is already implemented (no need to change it)
  void print(string name) { stack.print(name); }

}; // end of class interface (you may modify the code below)

// Implement all of the functions below

// Construct an empty ListStack by initializing this ListStack's instance
// variables
template <class T>
ListStack<T>::ListStack() : stack{List<T>()} {}

//Destroy all nodes in this ListStack to prevent memory leaks
template <class T>
ListStack<T>::~ListStack(){
	
} 
 //Return the size of this 
template <class T> 
int ListStack<T>::size(){
	return stack.size();
} 
 
//Return true if //Otherwise, return false  
template <class T> 
bool ListStack<T>::empty(){
	return stack.empty();
} 
 //Create a node with value <value T> 
template <class T> 
void ListStack<T>::push(T value) {
	stack.insertStart(value);
}
 
// Pop a node from the Stack.
//Note that here t //AND returning its v a
template <class T> 
T ListStack<T>::pop() {
	// sets a t object that returns the top node in the stack
	T end = stack.getFirst();
	// delets the top node of the stack
	stack.removeStart();
	return end;
}