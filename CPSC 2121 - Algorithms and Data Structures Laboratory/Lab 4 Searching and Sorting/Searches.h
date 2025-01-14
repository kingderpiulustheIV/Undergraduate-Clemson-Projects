/*
 * Name: Sean Farrell
 * Date Submitted: 9/25/2023
 * Lab Section: 6
 * Assignment Name: Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>
using namespace std;
template <class T>

// returns the elements position of vector data if it equals the target.
int linearSearch(std::vector<T> data, T target){
	int position = -1;
	for (int i = 0; i < data.size(); i++) {
		if (target == data[i]) {
			position = i;
			break;
		}
	}
	return position;
}

// Function for binary search logic needed for recursion.

template <class T> 
int binarySearchLogic(vector<T> data, T target, int left, int right) {
	if (left <= right) {
		// sets middle to middlle of vector: data.
		int middle = left + (right - left) / 2; 
		if (data[middle] == target) {\
			// Retuns the element if middle element matches the target.
			return middle; 
		}
		// Executes the following code if the target does not equal the middle element of data.
		
		if (data[middle] > target) {
			
			// Searches left side recursivly.
			
			return binarySearchLogic(data, target, left, middle -1);
		}
		else {
			
			// Searches right side recursivlu
			
			return binarySearchLogic(data, target, middle + 1, right);
		}
	}
	return -1;
}

// Binary serch that gets the vector and target that returns the recursive binarySearchLogic.

template <class T>
int binarySearch(std::vector<T> data, T target){
	return binarySearchLogic(data, target, 0, data.size()-1);
}