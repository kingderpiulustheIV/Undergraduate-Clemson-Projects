// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 14th, 2022
// Desc: A program that calculates persons hospital bill.
// Time: Approx. 3 hours

#include "calcTotalCharges.h" 
#include "validateUserInput.h"

// function prototype that declares calcTotalCharges
// function for user enters I for paitent type.

double calcTotalCharges(int hospDays, double roomRate,  double feeTotal, double medCharge){ 
  return (hospDays * roomRate) + medCharge + feeTotal; // calcualtes the total charge of the paitent based on the user's input for in patient.
}
// function for user enters O for paitent type.

double calcTotalCharges(double feeTotal, double medCharge){ //caculates the total charge of the paitent based on user input for out patient
  return medCharge + feeTotal;
}