// Adam Varady, CPSC 1021

#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include <iostream>

using namespace std;

class Motorcycle {
	string make{""};
	string model{""};
	int year{0};
	int mpg{0};
	int yearPurchased{0};
	public:
        Motorcycle();
		string getMake();
		bool setMake(string);
		string getModel();
		bool setModel(string);
		int getYear();
		bool setYear (int);
		int getMPG();
		bool setMPG (int);
		int getYearPurchased();
		bool setYearPurchased (int);
};
#endif