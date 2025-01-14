#ifndef SQUARE_H_
#define SQUARE_H_

#include "Shape.h"

class Square : public Shape // inherit publically from Shape
{
	private:
	double side{0.0};
	
	public:
	Square() = default;
	Square(double side): Shape("Square"), side (side) {};
	double getArea() override;
};

#endif
