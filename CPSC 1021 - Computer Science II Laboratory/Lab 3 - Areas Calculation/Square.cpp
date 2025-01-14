//My Name: Simon He
//My Class: CPSC 1021
//Date: 9/19/2022
//Desc: Constructs the object Square
//Time: 10 minutes


#include"Square.h"
#include<iostream>

Square::Square() {}
Square::Square(double s) : side {s} {}

//checks if user inputs a positive number
bool Square::setSide(double s)
{
	if (s > 0)
	{
		side = s;
		return true;
	}
	else
	{	
		return false;
	}
}

double Square::getSide()
{
	return side;
}
//calculates the area of a square
double Square::calcArea()
{
	return (side*side);
}

