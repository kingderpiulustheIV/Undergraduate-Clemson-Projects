#ifndef TRAPEZOID_H_
#define TRAPEZOID_H_

#include "Shape.h"
#include<vector>

template<typename T>
class Trapezoid : public Shape<T>// inherit publically from Shape
{
	private:
	T base1;
	T base2;
	T height;
	
	public:
	Trapezoid() = default;
	Trapezoid(T base1, T base2, T height): Shape<T>("Trapezoid"), base1 (base1), base2 (base2), height (height) {};
	T getArea() override
	{return height * ((base1 + base2)/2);};
};

#endif
