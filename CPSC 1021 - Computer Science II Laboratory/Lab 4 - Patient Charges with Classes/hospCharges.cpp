#include <iostream>
#include "Patient.h"
using  namespace std; 
int main() {
  char patientType;
  int days;
  double rate, services, medication;
  Patient Patient;
	cout << "Enter I for in-patient or O for out-patient: " << endl;
	cin >> patientType;
  Patient.setPatientType(patientType);

  if(patientType != 'O') {

// prompts and retrieves the user's input for hosptial days if not valid it reasks.
    cout << "Number of days in the hospital: " << endl;
    cin >> days;
    Patient.setDays(days);
	
// prompts and retrieves the user's input for Room rate if not valid it reasks.
    cout << "Daily room rate ($): " << endl;
    cin >> rate;
    Patient.setRate(rate);
  }
// prompts and retrieves the user's lab and service fees if not valid it reasks.

	 cout << "Lab fees and other service charges ($): " << endl;
	 cin >> services;
   Patient.setServices(services);
// prompts and retrieves the user's input for medication charges if not valid it reasks. 
	 cout << "Medication charges ($):  " << endl;
	 cin >> medication;
   Patient.setMedication(medication);
cout << "Your total hospital bills is $"<< Patient.calcTotalCharges();
}