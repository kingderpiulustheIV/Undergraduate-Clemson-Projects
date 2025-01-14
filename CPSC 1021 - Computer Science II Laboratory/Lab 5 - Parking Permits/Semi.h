// Sean Farrell 
#ifndef SEMI_H_
#define SEMI_H_
#include <string> // Used for string variables and functions.
using namespace std;
class Semi{

// Distengushes and establishes private variables to use for class Semi.
private:
  string make {"Volvo"};  
  string model{"12 wheeler"};
  string address{"123 tiger blvd Clemson SC"};
  int year {2022};
  string comLiscense{"SC 123456789"};
  int weight {12333};

// Allows main to access pulbic functions that are in the class Semi.
public:
  Semi();
  string getMake();
  void setMake(string m);
  string getModel();
  void setModel(string m);
  void setAddress(string a);
  string getAddress();
  int getYear();
  void setYear(int y);
  string getComLiscense();
  void setComLiscense(string cl);
  int getWeight();
  void setWeight(int w);
};
#endif