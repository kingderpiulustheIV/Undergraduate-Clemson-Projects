// Adam Varady, CPSC 1021

#include "Motorcycle.h"

Motorcycle::Motorcycle() {}

string Motorcycle::getMake() {
	return make;
}

bool Motorcycle::setMake(string ma) {
	if ((ma != "Honda") && (ma != "Ducati") && (ma != "Triumph")) {
		return false;
	}
	make = ma;
	return true;
}

string Motorcycle::getModel() {
	return model;
}

bool Motorcycle::setModel(string mo) {
	if (((mo == "CB750") || (mo == "CB125F")) && (make == "Honda")) {  
		model = mo;
		return true;
	}

	if (((mo == "V4") || (mo == "916")) && (make == "Ducati")) {
		model = mo;
		return true;
	}

	if(((mo == "Thruxton") || (mo == "Tigersport")) && (make == "Triumph")) {
		model = mo;
		return true;
	}
	return false;
}

int Motorcycle::getYear() {
	return year;
}

bool Motorcycle::setYear (int y) {
	if (year < 1980) {
		return false;
	}
	year = y;
	return true;
}

int Motorcycle::getMPG() {
	return mpg;
}

bool Motorcycle::setMPG (int mp) {
	if (mpg < 0) {
		return false;
	}
	mpg = mp;
	return true;
}

int Motorcycle::getYearPurchased() {
	return yearPurchased;
}

bool Motorcycle::setYearPurchased (int yp) {
	if (yp < year) {
		return false;
	}
	yearPurchased = yp;
	return true;
}