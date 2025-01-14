//Jonahan Sanchez-Vayas

#include "Lev.h"
#include <string>


void Lev:: setMake(string ma) {
    //start of setMake 
     make = ma; //initializes to private member "make"
} //end of setMake

void Lev:: setModel(string mo) {
    //start of setModel
    model = mo; //initializes to private member "model"
} //end of setModel

void Lev:: setYear(int y) {
    //start of setyear
    year = y; //initiazlizes to private member "year"
} // end of setYear

void Lev:: setCarColor(string c) {
    //start of setCarColor
    carColor = c; //initializes to private member "carColor"
} //end of setCarColor

void Lev:: setHybridOrElectric(string h) {
    //start of setHybridorElectric
    hybridOrElectric = h; //initializes to private member "HybridorElectric"
} //end of setHybridOrElectric

string Lev:: getMake() const { 
    //start of const getMake
    return make; //return int
} //end of getMake

string Lev:: getModel() const {
    //start of const getModel
    return model; // return string
} //end of getModel

int Lev:: getYear() const {
    //start of const getYear
    return year; //return int
} //end of getYear

string Lev:: getCarColor() const {
    //start of const getCarColor 
    return carColor; //return string
}//end of getCarColor

string Lev:: getHybridOrElectric() const {
    //start of const getHybridOrElectric
    return hybridOrElectric; //return string
} //end of getHybridOrElectric