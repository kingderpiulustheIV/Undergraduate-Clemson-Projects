// My Name: Seam Farrell
// My Class: CPSC 1021
// Date: September 19th, 2022
// Desc: Rectangle object that caculates area of the rectangle
// Time: Approx. 5 minutes
#ifndef  RECTANGLE_H_
#define  RECTANGLE_H_


class Rectangle{

private:
  double length;
  double width;

public:
  Rectangle();
  Rectangle(double l, double h);

  double getLength()const;
  bool setLength(double l);
 
  double getWidth()const;
  bool setWidth(double w);
  double calcArea();

};

#endif