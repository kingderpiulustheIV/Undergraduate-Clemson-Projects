// Group members: Sean Farrell, Simon He, Jonathan Sanchez-Vayas, Adam Varady
// My Class: CPSC 1021
// Date: 12/1/22022
// Desc: Accumulater that displays 4 numbers and 4 strings
// Time: Approx. 5 min
#ifndef ACCUM_H_
#define ACCUM_H_
#include <iostream> 
#include <vector>  // Needed for vectors.
#include <list>	   // Neded for template.
using namespace std;

template<typename s> s accum(vector<s> v) { //creates a template that returns the sum of the vector regardless of data type.
    s sum =s();
    for(auto iter =v.begin(); iter != v.end(); iter++)
        sum += *iter;
    return sum;
    }

#endif