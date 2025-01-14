// Sean Farrell
#ifndef TA_H_
#define TA_H_
#include <string> // needed for string variables and functions.
using namespace std;

class TA{

private: 
  // pre sets and calls public variables of the class to be used.
  string name {"sean"};
  string address{"123 tiger blvd clemson sc"};
  string email{"sean@gmail.com"};
  long int gradID {123456789};
  string major {"Computer science"};

public: 
  // allows public funtions to be accessed throgh main.
  TA();
  string getName();
  void setName(string n);
  string getAddress();
  void setAddress(string a);
  string getEmail();
  void setEmail(string e);
  string getMajor();
  void setMajor(string m);
  long int getGradID();
  void setGradID(long int id);
};
#endif