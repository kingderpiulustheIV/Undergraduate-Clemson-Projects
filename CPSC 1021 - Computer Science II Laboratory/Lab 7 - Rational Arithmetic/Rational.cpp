// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 11/11/2022
// Desc: A program that reduces a ratio such as symplifying a fraction.
// Time: Approx. 30 min.
#include "Rational.h"
#include <iostream>
using namespace std;
Rational::Rational(){ //defult constructor initalizes private variables to zero.
     one = 0;
     two = 0;
     reduce();
}
Rational::Rational(int a, int b){ //overloaded constructor that initializes private variables as the user input.
     one = a;
     two = b;
     reduce();
}

int Rational::getOne(){  //returns private numerator
    return one;
}

void Rational::setOne(int a){ // sets private numerator as the user input.
    one = a;
}

int Rational::getTwo(){ // gets private denominator
    return two;
}

void Rational::setTwo(int b){ //sets private denominator as user input.
    two = b;
}
void Rational::reduce(){  // function inside a rational object that reduces the private varaibles
    int large;
    if (one > two)  // finds which number is the larger number.
        large = one;
    else
        large = two;
    int divisor = 2; 
    while (divisor <= large) { //repeats until the divisor equals the large number
        if (one % divisor == 0 && two % divisor == 0) { //divides numerator and denominator by divisor has no remainders. 
            one /= divisor;
            two /= divisor;
            divisor = 2;
        }
        else
            divisor++; // increases the divisor by 1
    }
    if (two < 0) {     //formatting for negutive numbers.
        one *= -1;
        two *= -1;    
    }
}

