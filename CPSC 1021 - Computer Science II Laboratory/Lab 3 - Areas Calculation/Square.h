//My Name: Simon He
//My Class: CPSC 1021
//Date: 9/19/2022
//Desc: Creates a class Square
//Time: 10 minutes


#ifndef SQUARE_H
#define SQUARE_H

class Square
{
	private:
		double side{1.0};
	
	public:
		Square();
		Square(double);
		bool setSide(double side);
		double getSide();
		double calcArea();	
		
};
		
#endif
