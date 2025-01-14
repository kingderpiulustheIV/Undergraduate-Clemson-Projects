// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 11/11/2022
// Desc: A program that reduces a ratio such as symplifying a fraction.
// Time: Approx. 20 min.
#include <iostream>
#include "Rational.h"
using namespace std;
int main() {
  int numerator;    // user input for numerator
  int denominator;  // user input for denominator
  cout << "Enter the numerator and denominator separated by a space: "; // Prompts user to enter two integers
  cin >> numerator; // gets user input for numerator
cin >> denominator; // gets user input for denominator
  Rational ratio(numerator, denominator); // puts user input as the private variables of the object ratio
    cout << "Reduced form: " // displays the reduced form of the ratio or fraction.
 << ratio.getOne() << "/"  << ratio.getTwo() << endl;
    }