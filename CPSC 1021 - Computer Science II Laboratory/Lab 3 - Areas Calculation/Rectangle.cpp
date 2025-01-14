// My Name: Seam Farrell
// My Class: CPSC 1021
// Date: September 19th, 2022
// Desc: Rectangle object that caculates area of the rectangle
// Time: Approx. 5 minutes
#include "Rectangle.h"


Rectangle::Rectangle() { 
  //initializes the local variables to 0
  length = 0.0;
  width  = 0.0;
}

Rectangle::Rectangle(double l, double w) {
  //sets local variables from the public variables
  length = l;
  width  = w;
}

bool Rectangle::setLength(double l){
  // validates public input for length if valid sets the local length variable.
  if(l < 0)
    return false;
  length = l;
  return true;
}

double Rectangle::getLength()const{ 
  //gets length varuible from user input.
  return length;
}

bool  Rectangle::setWidth(double w){
    // validates public input for width if valid sets the local length variable.
    if(w < 0)
      return false;
    width = w;
    return true;
}

double Rectangle::getWidth()const{
  //gets width varuible from user input.
  return width;
}
double Rectangle::calcArea(){
  //caclulates area of rectangle
  return length * width;
}