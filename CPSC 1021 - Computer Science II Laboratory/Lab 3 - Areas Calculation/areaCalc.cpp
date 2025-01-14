//My Name: Sean Farrell
//My Class: CPSC 1021
//Date: 9/19/2022
//Desc:  program that caculates area of shapes with OOP.
//Time: 2 hrs.
#include <iostream>
#include <iomanip>
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Trapezoid.h"
using namespace std;

int main() {

// Declares variables used for user input. 
  int menuSelect;
  double userInput;
  double userInputTwo;
  double userInputThree;

  // Executes following code once or executes more if a user enters invalid menu selection. 
  do {
  cout << "Program to calculate areas of objects\n";
  cout << "\t\t1 -- circle\n";
  cout << "\t\t2 -- square\n";
  cout << "\t\t3 -- rectangle\n";
  cout << "\t\t4 -- trapezoid\n";
  cout << "\t\t5 -- quit \n";
  cin >> menuSelect;


    // User selects circle.
    if ( menuSelect == 1) {  

      Circle circle;
      // Asks for user radius then checks to see if its valid input then reasks if invalid.
      do {
        cout << "Radius: ";
        cin >> userInput; 
        circle.setRadius(userInput); 
        }
      while (circle.setRadius(userInput) == false);
      cout <<"Area: "<< fixed << setprecision(1) << circle.calcArea();
      }

    // User enters square.
    if ( menuSelect == 2) {
      Square square;
      // Asks for user side of square then checks to see if its valid input then reasks if invalid.
      do {
        cout << "Side: ";
        cin >> userInput; 
        square.setSide(userInput); 
        }
      while (square.setSide(userInput) == false);
      cout <<"Area: "<< fixed << setprecision(1) << square.calcArea();
      
     }
    // User Enters Rectangle
    if ( menuSelect == 3) {
      // Asks for user length of rectangle then checks to see if its valid input then reasks if invalid.
      Rectangle rect;
      do {
        cout << "Length: ";
        cin >> userInput; 
        rect.setLength(userInput); 
        }
      while (rect.setLength(userInput) == false);
      // Asks for user width of rectangle then checks to see if its valid input then reasks if invalid.
      do {
        cout << "Width: ";
        cin >> userInputTwo; 
        rect.setWidth(userInputTwo); 
        }
      while(rect.setWidth(userInputTwo) == false);
      cout <<"Area: "<< fixed << setprecision(1) << rect.calcArea(); 
     }
    // User Enters trapazoid
    if ( menuSelect == 4) {
      Trapezoid trap;
      // Asks for user base one length of trapezoid then checks to see if its valid input then reasks if invalid.
      do {
        cout << "Base1: ";
        cin >> userInput; 
        trap.setBase1(userInput); 
      }
      while (trap.setBase1(userInput) == false);
      // Asks for user base two length of trapezoid then checks to see if its valid input then reasks if invalid.
      do {
        cout << "Base2: ";
        cin >> userInputTwo; 
        trap.setBase2(userInputTwo); 
      }
      while(trap.setBase2(userInputTwo) == false);
      // Asks for user hight of trapezoid then checks to see if its valid input then reasks if invalid.
      do {
        cout << "Height: ";
        cin >> userInputThree; 
        trap.setHeight(userInputThree); 
      }
      while(trap.setHeight(userInputThree) == false);
      cout <<"Area: "<< fixed << setprecision(1) << trap.calcArea();
      
     }
    // If user enters 5 in menu choice program ends.
    if (menuSelect == 5)
      cout << "You entered an invalid choice. Good bye! \n";
    } while((menuSelect < 1) || (menuSelect > 5));
  }