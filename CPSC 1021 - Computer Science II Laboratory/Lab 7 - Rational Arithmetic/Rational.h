// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 11/11/2022
// Desc: A program that reduces a ratio such as symplifying a fraction.
// Time: Approx. 5min
#ifndef RATIONAL_H_
#define RATIONAL_H_ 
#include <iostream>
using namespace std;
class Rational{ 
private: 
    int one; //private variable for numerator
    int two; //private variable for denominator
    void reduce(); // function inside a rational object that reduces the private varaibles
public:
    Rational(); //defult constructor
    Rational(int a, int b); //initializes private variables as the user input 
    int getOne(); //returns private numerator
    void setOne(int a); // sets private numerator as the user input.
    int getTwo(); // gets private denominator
    void setTwo(int b); //sets private denominator as user input.
};
#endif