// Sean Farrell
#include "Semi.h"

// string make {"Volvo"};  
//   string model{"12 wheeler"};
//   string address{"123 tiger blvd Clemson SC"};
//   int year {2022};
//   string comLiscense{"SC 123456789"};
//   int weight {12333};

Semi::Semi() : make{"Volvo"}, model{"12 wheeler"}, address{"123 tiger bldvd Clemson SC"}, year{2022}, comLiscense{"SC 123456789"}, weight{12333} {}
//Sets private address to public address.
void  Semi::setAddress(string a){
  address = a;
}
//Returns private Address.
string Semi::getAddress(){
  return address;
}
//Sets commercail liscene to public commercail liscene .
void Semi::setComLiscense(string cl){
   comLiscense = cl;
 }
//Returns private commecail liscense.
string Semi::getComLiscense(){
  return comLiscense;
}
//Sets make of semi to public make of semi.
void Semi::setMake(string m) {
  make = m;
}
//Returns private make of semi.
string Semi::getMake() {
  return make;
}
//Sets model of semi to public model of semi.
void Semi::setModel(string m) {
  model = m;
}
//Returns private model of semi.
string Semi::getModel(){
  return model;
}
//Sets weight of semi to public weight of semi.
void Semi::setWeight(int w) {
  weight = w;
}
//Returns private weight of semi.
int Semi::getWeight() {
  return weight;
}
//Sets year of semi to public year of semi.
void Semi::setYear(int y) {
	year = y;
}
//Returns private  year of semi.  
int Semi::getYear() {
  return year;
}