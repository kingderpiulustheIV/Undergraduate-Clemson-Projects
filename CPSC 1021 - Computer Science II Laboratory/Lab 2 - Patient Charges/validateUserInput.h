// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 14th, 2022
// Desc: A program that calculates persons hospital bill.
// Time: Approx. 3 hours

#ifndef VALIDATEUSERINOUT_H //Header file for function validateUserInput
#define VALIDATEUSERINPUT_H

#include <iostream>
#include <iomanip>

bool validateUserInput(int hospitalDays); // used to validate hospDays.
bool validateUserInput(double cost); //used to validate, feeTotal, roomRate, Medcharge.
bool validateUserInput(char patientType); // used to validate patient type.

#endif