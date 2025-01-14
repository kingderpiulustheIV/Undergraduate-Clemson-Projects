// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 30th, 2022
// Desc: A program that determins how long you quarantene from COVID-19 based on vaxination, contact, and test status of the virus. 
// Time: Approx. 4 hours
#include <iostream>
#include <cstring>
#include "Date.h"
#include "calcDays.h"
using namespace std;

int calcQDays(bool verifyStatus, bool verifyContact, bool verifyVaxStatus);

int main() {

	cout << daysFromStart(Date{1,1,2021}) << endl;
  int day;
  int month; 
  int year;
  string status, contact, vaxStatus;
  bool verifyStatus;
  bool verifyContact;
  bool verifyVaxStatus;
  Date Date;

  cout << "Test result: ";
  cin >> status;
  if (status == "positive"){
    class Date datePositive;
    verifyStatus = true;
    cout << "Input month: ";
    cin >> month;
    datePositive.setMonth(month);
    cout << "Input day: ";
    cin >> day;
    datePositive.setDay(day);
    cout << "Input year: ";
    cin >> year;
    datePositive.setYear(year);
    cout << "Date tested positive: "  << datePositive.showDate() << "\n";
    cout << "Length of isolation: " << calcQDays(verifyStatus, verifyContact, verifyVaxStatus) << " days";
  }
  else{
    cout << "Exposed to positive case: ";
    cin >> contact;
    if (contact == "Yes") {
      class Date dateExposed;
      verifyStatus = true;
      cout << "Input month: ";
      cin >> month;
      dateExposed.setMonth(month);
      cout << "Input day: ";
      cin >> day;
      dateExposed.setDay(day);
      cout << "Input year: ";
      cin >> year;
      dateExposed.setYear(year);
      cout << "Date exposed to positive case:"  << dateExposed.showDate() << "\n";
      cout << "Second vaccination dose received: ";
      cin >> vaxStatus;
      if(vaxStatus == "Yes"){
        class Date dateSecondDose;
        verifyStatus = true;
        cout << "Input month: ";
        cin >> month;
        dateSecondDose.setMonth(month);
        cout << "Input day: ";
        cin >> day;
        dateSecondDose.setDay(day);
        cout << "Input year: ";
        cin >> year;
        dateSecondDose.setYear(year);
        cout << "Date second vaccination dose received: "  << dateSecondDose.showDate() << "\n";
        if (14 >= calcDays(dateExposed, dateSecondDose)){
          verifyVaxStatus = true;
          cout << "Vaccination status at time of exposure: fully vaccinated\n";
          cout <<  "Length of isolation: " << calcQDays(verifyStatus, verifyContact,   verifyVaxStatus) << " days";
          
        }
        else{
          verifyVaxStatus = false;
          cout << "Vaccination status at time of exposure: not fully vaccinated\n";
          cout << "Length of isolation: " << calcQDays(verifyStatus, verifyContact, verifyVaxStatus) << " days";
          
        }
        
      }
        else{
          verifyVaxStatus = false;
          cout << "Vaccination status at time of exposure: not fully vaccinated\n";
          cout << "Length of isolation: " << calcQDays(verifyStatus, verifyContact, verifyVaxStatus) << " days";
      }
    } 
    else {
        cout <<  "Length of isolation: " << calcQDays(verifyStatus, verifyContact,   verifyVaxStatus) << " days";
    }
  }
}
int calcQDays(bool verifyStatus,bool verifyContact,bool verifyVaxStatus){
  if (verifyStatus == true){
    return 5;
  }
  if ((verifyStatus == false) &&(verifyContact == false) ){
    return 0;
  }
  if (((verifyStatus == false) &&(verifyContact == true)) && (verifyVaxStatus == true)){
    return 5;
  }
  if (((verifyStatus == false) &&(verifyContact == true)) && (verifyVaxStatus == false)){
    return 10;
  }
  
}