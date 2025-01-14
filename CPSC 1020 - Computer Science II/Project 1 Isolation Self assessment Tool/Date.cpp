// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 30th, 2022
// Desc: A class  that finds out the date of the user for test date, contact date, 2nd vax status.
// Time: Approx. 1 hour

#include "Date.h"


Date::Date(){
  day   = 1;
  month = 1;
  year  = 2021;
  
}
Date::Date(int d, int m, int y) {
  day   = d;
  month = m;
  year  = y;
}

bool Date::setMonth(int m) {
 if (m > 0 && m < 13){
    month = m;
    return true;
 }
 return false;   
}

int Date::getMonth(){
  return month;
};

bool Date::setYear(int y) {
 if (y == 2021 || y == 2022){
    year = y;
    return true;
 }
 return false;   
}
int Date::getYear(){
  return year;  
}

bool Date::setDay(int d) {
 if ((((m  % 2 !=0)&& m < 8 ) || ((m  % 2 ==0)&&( m <= 12 )))&& ((d < 32)&&(d > 0))){
    day = d;
    return true;
 }
else if ((((m  % 2 ==0)&& m <= 6 ) || ((m  % 2 !=0)&&( m >= 9 )))&& ((d < 31)&&(d > 0))){
  day = d;
  return true;
  
 } 
else if ((m == 2)&& ((d < 29)&&(d > 0))){
  day = d;
  return true;
 }
 else return false;   
};

int Date::getDay(){
  return day;
};

string Date::showDate(){
	string date = "";

	if(month > 9) {
		date += to_string(month);
		date += "/";
	}
	else {
		date += "0";
		date += to_string(month);
		date += "/";
	}

	if(day > 9) {
		date += to_string(day);
		date += "/";
	}
	else {
		date += "0";
		date += to_string(day);
		date += "/";
	}

	date += to_string(year);

	return date;
};