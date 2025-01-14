// My Name: Seam Farrell
// My Class: CPSC 1021
// Date: September 19th, 2022
// Desc: Trapezoid object that caculates area of the trapezoid
// Time: Approx. 5 minutes
#ifndef  TRAPEZOID_H_
#define  TRAPEZOID_H_


class Trapezoid{

private:
  double baseOne;
  double baseTwo;
  double height;

public:
  Trapezoid();
  Trapezoid(double bo, double bt, double h);

  double getBase1()const;
  bool setBase1(double bo);

  double getBase2()const;
  bool setBase2(double bt);

  double getHeight()const;
  bool setHeight(double h);
  

  double calcArea();

};

#endif