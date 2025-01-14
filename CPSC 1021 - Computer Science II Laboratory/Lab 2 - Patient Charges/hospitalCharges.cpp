// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 14th, 2022
// Desc: A program that calculates persons hospital bill.
// Time: Approx. 3 hours
#include <iostream>
#include <iomanip>
#include "calcTotalCharges.h" // Header file for function calcTotalCharges.
#include "validateUserInput.h" // Header file for function ValidateUserInput.
using namespace std;


int main() {
  
// varibles used for verfifcation in validateUserInput function.
  char patientType;
  int hospDays;
  double roomRate, feeTotal, medCharge, billTotal;

// Calls validateUserInput function and returns the valid user inputs. 
//validateUserInput(hospDays, roomRate, feeTotal, medCharge, patientType);

do {
	cout << "Enter I for in-patient or O for out-patient: " << endl;
	cin >> patientType;
} while (!validateUserInput(patientType)); //keeps exectuding do while loop if input is invalid.

if(patientType == 'I') {

// prompts and retrieves the user's input for hosptial days if not valid it reasks.
  do {
  cout << "Number of days in the hospital: " << endl;
  cin >> hospDays;
	} while (!validateUserInput(hospDays)); //keeps exectuding do while loop if input is invalid.
	
// prompts and retrieves the user's input for Room rate if not valid it reasks.
   do{
   cout << "Daily room rate ($): " << endl;
   cin >> roomRate;
   } while (!validateUserInput(roomRate)); //keeps exectuding do while loop if input is invalid.
}  
// prompts and retrieves the user's lab and service fees if not valid it reasks.

	 do{
	 cout << "Lab fees and other service charges ($): " << endl;
	 cin >> feeTotal;
	 } while (!validateUserInput(feeTotal)); //keeps exectuding do while loop if input is invalid.
// prompts and retrieves the user's input for medication charges if not valid it reasks.
	 do{  
	 cout << "Medication charges ($):  " << endl;
	 cin >> medCharge;
	 } while (!validateUserInput(medCharge)); //keeps exectuding do while loop if input is invalid.


//sets bill total to the CalcTotalCharges function if in patient. 
if (patientType == 'O'){
billTotal = calcTotalCharges(feeTotal, medCharge);
  cout << "Your total hospital bills is $" << billTotal; //keeps exectuding do while loop if input is invalid. 
 }

//sets bill total to the overloaded CalcTotalCharges function if out patient.   
if (patientType == 'I'){
billTotal = calcTotalCharges(hospDays, roomRate, feeTotal, medCharge);
  cout << "Your total hospital bills is $" << billTotal;
  }
}