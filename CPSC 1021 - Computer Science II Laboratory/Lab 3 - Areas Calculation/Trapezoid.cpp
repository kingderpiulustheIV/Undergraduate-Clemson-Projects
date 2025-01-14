// My Name: Seam Farrell
// My Class: CPSC 1021
// Date: September 19th, 2022
// Desc: Trapezoid object that caculates area of the trapezoid
// Time: Approx. 10 minutes

#include "Trapezoid.h"

Trapezoid::Trapezoid() {
  //Inintializes private variables to 0
  baseOne = 0.0;
  baseTwo = 0.0;
  height  = 0.0;
}

Trapezoid::Trapezoid(double bo, double bt, double h) {
  //Inintializes sets public varibles to private variables.
  baseOne = bo;
  baseTwo = bt;
  height   = h;
}

bool Trapezoid::setBase1(double bo){
  //validates public variables then sets it is valid if so equals private base one length.
  if(bo < 0)
    return false;
  baseOne = bo;
  return true;
}

double Trapezoid::getBase1()const{
  //gets public base one from user input.
  return baseOne;
}

bool Trapezoid::setBase2(double bt){
  //validates public variables then sets it is valid if so equals private base two length.
  if(bt < 0)
    return false;
  baseTwo = bt;
  return true;
}

double Trapezoid::getBase2()const{
  //gets public base two from user input.
  return baseTwo;
}

bool Trapezoid::setHeight(double h){
  //validates public variables then sets it is valid if so equals height.
  if(h < 0)
    return false;
  height = h;
  return true;
}

double Trapezoid::getHeight()const{
  //gets public heighjt from user input.
  return height;
}
double Trapezoid::calcArea(){
  //caculates trapizoids area
  return ((baseOne + baseTwo)/2) * height;
}