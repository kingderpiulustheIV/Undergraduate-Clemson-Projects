// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 14th, 2022
// Desc: A program that calculates persons hospital bill.
// Time: Approx. 3 hours

#include "validateUserInput.h" //calls validateUserInput header file. 
using namespace std; 


bool validateUserInput(int hospitalDays) { // Is hospital days is valid if above 0.
	return (hospitalDays > 0);
}

bool validateUserInput(double cost) { // If room Rate, Lab and service fees total, medicene charge is valid if above 0.
	return (cost > 0.0);
}

bool validateUserInput(char patientType) { // If paitent tipe is valid as "I" or "O".
	return (patientType == 'I' || patientType == 'O');
}