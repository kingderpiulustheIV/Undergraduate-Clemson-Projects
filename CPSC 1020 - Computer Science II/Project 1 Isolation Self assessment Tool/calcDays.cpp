// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 30th, 2022
// Desc: A program that calculates days inbetween covid contact and 2nd covid vaxination.
// Time: Approx. 1 hour
#include "calcDays.h"
#include "Date.h"
// 01/10/2021
// 30 + 10 + 0 = 40
// 01/01/2021
// 30 + 1 + 0 = 31
// 

int calcDays(Date d1, Date d2) {
	int daysDiff1 = daysFromStart(d1);
	int daysDiff2 = daysFromStart(d2);
	return abs(daysDiff1 - daysDiff2);
}

int daysFromStart(Date d1) {
	// 01/01/2021
	int monthMultiplier;
	int yearMultiplier;

 if ((((d1.getMonth()  % 2 !=0)&& d1.getMonth() < 8 ) || ((d1.getMonth()  % 2 ==0)&&( d1.getMonth() <= 12 )))&& ((d1.getDay() < 32)&&(d1.getDay() > 0))){
    monthMultiplier = 31;
 }
else if ((((d1.getMonth()  % 2 ==0)&& d1.getMonth() <= 6 ) || ((d1.getMonth()  % 2 !=0)&&( d1.getMonth() >= 9 )))&& ((d1.getDay() < 31)&&(d1.getDay() > 0))){
  monthMultiplier = 30;
  
 } 
else if ((d1.getMonth() == 2)&& ((d1.getDay() < 29)&&(d1.getDay() > 0))){
  monthMultiplier = 28;
 }

	if (d1.getYear() == 2021) {
		yearMultiplier = 0;
	}
	else {
		yearMultiplier = 1;
	}
	
	
	int days = stoi(d1.showDate().substr(0,3));
	int mDays = stoi(d1.showDate().substr(3, 5)) * monthMultiplier;
	int yDays = 365 * yearMultiplier;

	return (days + mDays + yDays - 32);
}