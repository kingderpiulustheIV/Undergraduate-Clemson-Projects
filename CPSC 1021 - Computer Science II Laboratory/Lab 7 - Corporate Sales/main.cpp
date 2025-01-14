// My Name: Adam Varady
// My Class: CPSC 1021
// Date: November 2nd, 2022
// Desc: A program that checks four divisions of a company's quarterly sales.
// Time: Approx. 30 minutes

#include "DivSales.h"

int main (void) {
	std::vector <DivSales> salesVect;
	
	// needs an initial loop with a bunch of doubles to funnel into a DivSales variable to push to the back of the above vector
	for (int i = 1; i < 5; ++i) {
		DivSales tempDivSales;
		std::vector <double> tempVect;
		
		std::cout << "Enter sales data for division " << i << std::endl; 
		
		// pushes back four numbers entered by the user to the back of a vector
		for (int j = 1; j < 5; ++j) {
			double temp = -1;
			
			std::cout << "Quarter " << j << ": ";
			std::cin >> temp;
			
			while (temp < 0) {
				std::cout << "Please enter 0 or greater: ";
				std::cin >> temp;
			}
			
			tempVect.push_back(temp);
		}
		
		// puts the four variables into the temporary DivSales, then adds it to the vector. rinse and repeat four times.
		tempDivSales.setSales (tempVect[0], tempVect[1], tempVect[2], tempVect[3]);
		salesVect.push_back(tempDivSales);
	}
	
	std::cout << std::fixed << std::setprecision(2);
	
	// reports the total sales for every division with two decimal places as entered above
	for (size_t i = 0; i < salesVect.size(); ++i) {
		std::cout << "Total sales for Division " << i+1 << ": $" << salesVect[i].getDivSales() << std::endl;
	}
	
	// outputs the static variable counting everything, then closes
	std::cout << "Total Corporate Sales: $" << DivSales::totalSales;
	
	return 0;	
}
