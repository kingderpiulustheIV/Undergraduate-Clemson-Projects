#ifndef DATE_H_
#define DATE_H_
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
class Date{
private:
    int month;
    int day;
    int year;
public:
    const string static MONTHS[];
	Date();
	Date(int m, int d, int y);
    //const static string MONTHS[12];
    int getMonth() const;
    void setMonth(int m);
    int getDay() const;
    void setDay(int d);
    int getYear() const;
    void setYear(int y);
    string print();
    static bool compare(const Date& d1, const Date& d2);
};
#endif