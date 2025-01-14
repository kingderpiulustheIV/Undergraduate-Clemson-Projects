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
void mergeSortLogic(std::vector<T>&, int, int);

template <class T>
void mergeSortParition(std::vector<T>&, int, int, int);

template <class T>
void swap(T*, T*);

template <class T>
int split(std::vector<T>&, int, int);

template <class T>
void quickSortLogic(std::vector<T>&, int, int);

template <class T>

// Swaps the two elements that are entered in the parameter of the fuction.

void swap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;	
}

// Function takes a pivot then plases elements to left if there data is lower than the pivot.
// If the elemnt is larger than the pivot it moves the element to the right of the pivot.

template <class T>
int split(vector<T> &list, int min, int max) {
	auto pivot = list[max];
	int index = min - 1;
	for (int i = min; i < max; i++) {
		if (list[i] < pivot) {
			index++;
			swap(&list[index], &list[i]);
		}
	}
	swap(&list[index + 1], &list[max]);
	return index + 1;
}

// Logic for quicksort 

template <class T>
void quickSortLogic(vector<T> &list, int min, int max) {
	if (min < max) {
		
		// splits the vale to pivot.
		
		int splitValue = split(list, min, max); 
		
		// sorts the elements before and after the pivot recursively,
		// to get the elements in order from smallest to largest.
		
		quickSortLogic(list, min, splitValue -1 );
		quickSortLogic(list, splitValue + 1, max);
	}
}

template <class T>
std::vector<T> quickSort(std::vector<T> lst){
	quickSortLogic(lst, 0, lst.size()-1);
	return lst;
}

// logic for subvectors divide and conquer aspect to merge sort.

template <class T> 
void mergeSortPartition(vector<T> &list, int const left, int const middle, int const right) {
	vector<T> leftPart;
	vector<T> rightPart;
	int const temp = right - middle;
	int const temp2 = middle - left +1;
	int sub  = 0;
	int sub2 = 0;
	int sub3 = left;

	// Creates sub-vectors for left and right side.
	
	for(int i = 0; i < temp2; i++) {
		leftPart.push_back(list[left + i]);
	}
	for (int j = 0; j < temp; j++) {
		rightPart.push_back(list[middle + 1+ j]);
	}

	//  Combines sub-vectors.
	
	while ( sub < temp2 && sub2 < temp) {
		if (leftPart[sub] <= rightPart[sub2]) {
			list[sub3] = leftPart[sub];
			sub++;
		}
		else {
			list[sub3] = rightPart[sub2];
			sub2++;
		}
		sub3++;
	}
	
	//  Copys remaining elements of left sub vector to list vector.
	
	while (sub < temp2) {
		list[sub3] = leftPart[sub];
		sub++;
		sub3++;
	}
	
	//  Copys remaining elements of right sub vector to list vector.
	
	while (sub2 < temp) {
		list[sub3] = rightPart[sub2];
		sub2++;
		sub3++;
	}
}

// Logic for merge sort

template <class T> 
void mergeSortLogic (vector <T> &list, int const  left, int const right) {
	if (left >= right) {
		return;
	}
	
	// splits index into two partitions
		
	int middle = left + (right - left) / 2; 

	// Sorts the elements before and after the partitions.
	
	mergeSortLogic(list, left, middle);
	mergeSortLogic(list, middle + 1, right);
	mergeSortPartition(list, left, middle, right);
}



template <class T>
std::vector<T> mergeSort(std::vector<T> list){
	mergeSortLogic(list, 0, list.size() - 1);
	return list;
}