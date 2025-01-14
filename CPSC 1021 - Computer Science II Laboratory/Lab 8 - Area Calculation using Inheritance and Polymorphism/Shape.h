#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>

class Shape
{
	private:
  		std::string name{"Shape"};
	public:
  		Shape() = default;
  		Shape(std::string name) : name(name) {};

  		// implement printName() and tag it as 'final'
  		// to prevent derived-classes from overriding it
  		virtual std::string printName() final
  		{return name;};

  		// implement getArea() as an abstract function
		virtual double getArea()
		{return 0;};
};

#endif
