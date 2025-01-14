// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 7th, 2022
// Desc: A program that executes the formula for calculating interest of a bank account.
// Time: Approx. 3 hours


#include "compoundCalc.h" // includes header file.

double compoundCalc (double p, double r, double t) { // function that retrives user input caculates interest based on the intrest equation.
double calcVal;
calcVal = p * pow((1+r), t);
return calcVal;
}
