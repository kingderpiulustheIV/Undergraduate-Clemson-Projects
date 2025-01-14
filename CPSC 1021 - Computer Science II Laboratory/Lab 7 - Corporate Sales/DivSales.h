// My Name: Adam Varady
// My Class: CPSC 1021

#ifndef DIVSALES_H
#define DIVSALES_H

#include <iostream>
#include <iomanip>
#include <vector>

// the class. has three variables, a mutator, and two accessors.
class DivSales {
		std::vector <double> sales;
		double divSales;
	public:
		static double totalSales;
		void setSales (double, double, double, double);
		double getDivSales () {return divSales;};
		double getCorpSales () {return totalSales;};
};

#endif
