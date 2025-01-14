//My Name: Simon He
//My Class: CPSC 1021

#ifndef EV_H
#define EV_H
#include<string>
using namespace std;

class Ev
{
	private:
	string make;
	string model;
	int year;
	int battery;
	char size;
	
	public:
    Ev();
	void setMake(string m);
	void setModel(string mo);
	void setYear(int y);
	void setBattery(int b);
	void setSize(char s);
	
	string getMake();
	
	string getModel();
	
	int getYear();
	
	int getBattery();
	
	char getSize();
};
#endif