// My Name: Adam Varady
// My Class: CPSC 1021

#include "DivSales.h"

// the static variable needs initialized out here
double DivSales::totalSales = 0;

// puts the four doubles into the sales double, then adds them up for divSales, then adds that to the static variable
void DivSales::setSales (double q1, double q2, double q3, double q4) {
	sales.push_back (q1);
	sales.push_back (q2);
	sales.push_back (q3);
	sales.push_back (q4);
	
	divSales = q1 + q2 + q3 + q4;
	
	totalSales += divSales;
}	
