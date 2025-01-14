//My Name: Simon He
//My Class: CPSC 1021

#include"Ev.h"
#include<string>
using namespace std;

	// string make;
	// string model;
	// int year;
	// int battery;
	// char size;

Ev::Ev() : make{""}, model{""}, year{2001}, battery{0}, size{'s'} {}

void Ev::setMake(string m)
{
	make = m;
}

void Ev::setModel(string mo)
{
	model = mo;
}

void Ev::setYear(int y)
{
	year = y;
}

void Ev::setBattery(int b)
{
	battery = b;
}

void Ev::setSize(char s)
{
	size = s;
}

string Ev::getMake() {return make;};

string Ev::getModel() {return model;};

int Ev::getYear() {return year;};

int Ev::getBattery() {return battery;};

char Ev::getSize() {return size;};