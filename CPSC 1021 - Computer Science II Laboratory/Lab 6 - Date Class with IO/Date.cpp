#include "Date.h"

const string Date::MONTHS[12] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};

Date::Date() : month{1}, day{1}, year{1900} {}
Date::Date(int m, int d, int y) : month{m}, day{d}, year{y} {}

int Date::getDay() const {
    return day;
}
void Date::setDay(int d) {
	day = d;
}
int Date::getMonth() const {
    return month;
}
void Date::setMonth(int m){
    month = m;
}

int Date::getYear() const{
    return year;
}
void Date::setYear(int y){
    year = y;
}

string Date::print()
{
  stringstream output;
  output << left << setw(10) << MONTHS[month - 1] << setw(3) << day << setw(5) << year << endl;
  return output.str();
}

bool Date::compare(const Date& d1, const Date& d2)
{
	int d1Days = d1.getYear() * 365 + (int) (d1.getMonth() * 30.437) + d1.getDay();
	int d2Days = d2.getYear() * 365 + (int) (d2.getMonth() * 30.437) + d2.getDay();
	return d1Days < d2Days;
}