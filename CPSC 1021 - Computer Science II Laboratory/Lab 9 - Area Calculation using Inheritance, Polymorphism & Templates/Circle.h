#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"
#include<vector>

template<typename T>
class Circle : public Shape<T>// inherit publically from Shape
{
	private:
	T radius;
	const double PI{3.14};
	
	public:
	Circle() = default;
	Circle(T radius): Shape<T>("Circle"), radius (radius) {};
	T getArea() override
	{return PI* radius* radius;};
};

#endif
