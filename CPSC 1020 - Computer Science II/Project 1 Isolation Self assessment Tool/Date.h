
// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: September 30th, 2022
// Desc: h file for Date.cpp.
// Time: Approx. 5 min.
#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>
using namespace std;


class Date{
private:
  int day;
  int month;
  int year;

public:
  int m;
  int d;
  int y;
  Date();
  Date(int d, int m, int y);
  bool setDay(int d);
  bool setMonth(int m);
  bool setYear(int y);
  int getDay();
  int getMonth();
  int getYear();
  string showDate();
};
#endif