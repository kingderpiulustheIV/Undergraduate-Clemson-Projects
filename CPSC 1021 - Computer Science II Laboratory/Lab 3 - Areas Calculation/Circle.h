// My Name: Seam Farrell
// My Class: CPSC 1021
// Date: September 19th, 2022
// Desc: Circle object that caculates area of the object.
// Time: Approx. 5 minutes
#ifndef  CIRCLE_H_
#define  CIRCLE_H_ 

class Circle{ //Defines and calls the circle class. 

private:
  double radius; // private radius

public:
  Circle(); 
  Circle(double r); //public variable used for input to pass through for raidus.

// function Initializes the radius
  double getRadius()const; 

//Fuction that sets the radius and makes shure the user input is valid
bool setRadius(double r);

// Function in class that calulates and returns circles area
  double calcArea();

};

#endif