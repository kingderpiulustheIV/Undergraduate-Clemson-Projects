#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"

class Circle : public Shape// inherit publically from Shape
{
	private:
	double radius{0.0};
	const double PI{3.14};
	
	public:
	Circle() = default;
	Circle(double radius): Shape("Circle"), radius (radius) {};
	double getArea() override;
};

#endif
