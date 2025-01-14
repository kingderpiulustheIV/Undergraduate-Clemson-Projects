// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 7th, 2022
// Desc: A program that executes the formula for calculating interest of a bank account.
// Time: Approx. 3 hours

#include "compoundCalc.h"
using namespace std;

int main()
{
    
    int principal, years; // Declare variables for user input.
    double rate, totalValue;
    cout << "(user prompt to enter P): "; // Promps the user to enter Principal, intrest ratre and years passed.
    cin >> principal;
    cout << "\n";
    cout << "(user prompt to enter r as a decimal): ";
    cin >> rate;
    cout << "\n";
    cout << "(user prompt to enter t): ";
    cin >> years;
    cout << "\n";
    totalValue = compoundCalc(principal, rate, years);
    cout << "Your retirement savings will be $" << totalValue; // Shows the  account balance that is the result of compound intrest.
  return 0;
}