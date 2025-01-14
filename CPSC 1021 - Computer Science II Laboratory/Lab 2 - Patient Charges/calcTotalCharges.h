// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 14th, 2022
// Desc: A program that calculates persons hospital bill.
// Time: Approx. 3 hours

#ifndef CALCTOTALCHARGES_H //Header file for calcTotalCharges
#define CALCTOTALCHARGES_H

#include "validateUserInput.h"
double calcTotalCharges(int hospDays, double roomRate,  double feeTotal, double medCharge);  // Function for inpateint total.
double calcTotalCharges(double feeTotal, double medCharge); // Function for outpatient total.
#endif
