#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"

class Rectangle : public Shape// inherit publically from Shape
{
	private:
	double length{0.0};
	double width{0.0};
	
	public:
	Rectangle() = default;
	Rectangle(double length, double width): Shape("Rectangle"), length (length), width (width) {};
	double getArea() override;
};

#endif
