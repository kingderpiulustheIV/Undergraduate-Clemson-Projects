
// My Name: Seam Farrell
// My Class: CPSC 1021
// Date: September 19th, 2022
// Desc: Circle object that caculates area of the object.
// Time: Approx. 5 minutes
#include "Circle.h"

// premakes the radius 0 by defult for class
Circle::Circle() { 
  radius = 0.0;
}

//sets  public r as private radius
Circle::Circle(double r) { //sets  public r as private radius
  radius = r;
}


// User creates a Circle with user inputed input.
bool Circle::setRadius(double r){ 
// If radius is below 0 reask for user input for radius.
  if(r <= 0)  
    return false;
  radius = r; // sets private radius value as public r.
  return true;
}

// Initializes the radius.
double Circle::getRadius()const{ 
  return radius;
}

// Returns caculated area of a circle .
double Circle::calcArea(){       
  return radius * radius * 3.14159;
}