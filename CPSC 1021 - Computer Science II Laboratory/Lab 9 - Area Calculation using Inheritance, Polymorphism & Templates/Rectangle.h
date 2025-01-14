#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"
#include<vector>

template<typename T>
class Rectangle : public Shape<T>// inherit publically from Shape
{
	private:
	T length;
	T width;
	
	public:
	Rectangle() = default;
	Rectangle(T length, T width): Shape<T>("Rectangle"), length (length), width (width) {};
	T getArea() override
	{return length * width;};
};

#endif
