#include "Shape.h"
#include "Rectangle.h"
#include "Square.h"
#include "Circle.h"
#include "Trapezoid.h"
#include <iostream>
#include <iomanip>

#include <vector>


int main()
{
  	//Template for double types initialized at set values
  	Circle<double> circle1{2.0};
  	Square<double> square1{2.0};
  	Rectangle<double> rectangle1{2.5, 3.0};
  	Trapezoid<double> trapezoid1{2.5, 3.5, 4.0};

  
  	// make a vector 'vector<Type>shapeVect {element0, element1, element2, element3}'
  	// where 'Type' is a pointer to class Shape and each element is the memory address
  	// of one of objects you have instantiated above

	std::vector<Shape<double>*>shapeVect1{&circle1, &square1, &rectangle1, &trapezoid1};
  	
  	// use a range-based for loop to print the name and area of each object using
  	// functions printName() and getArea() accessed through the base class pointer
  	
  	for (int i = 0; i < 4; i++)
  	{
  		std::cout << "Area of " << std::setprecision(1) << std::fixed << shapeVect1[i]->printName() << " is: " << shapeVect1[i]->getArea() << std::endl;
  	}
  	
  	//Template for int types initialized at set values
  	Circle<int> circle2{2};
  	Square<int> square2{2};
  	Rectangle<int> rectangle2{2, 3};
  	Trapezoid<int> trapezoid2{2, 6, 5};

  
  	// make a vector 'vector<Type>shapeVect {element0, element1, element2, element3}'
  	// where 'Type' is a pointer to class Shape and each element is the memory address
  	// of one of objects you have instantiated above

	std::vector<Shape<int>*>shapeVect2{&circle2, &square2, &rectangle2, &trapezoid2};
  	
  	// use a range-based for loop to print the name and area of each object using
  	// functions printName() and getArea() accessed through the base class pointer
  	
  	for (int i = 0; i < 4; i++)
  	{
  		std::cout << "Area of " << std::setprecision(1) << std::fixed << shapeVect2[i]->printName() << " is: " << shapeVect2[i]->getArea() << std::endl;
  	}
  
   return 0;
}
