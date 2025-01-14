//Jonathan Sanchez-Vayas

#ifndef TEACHER_H_
#define TEACHER_H_

#include <string>
#include <iostream>

using namespace std;

class Teacher{ //start of "Teacher" class
private:
  //Private member variable declarations
  string name {"Jonathan"};
  string address {"123 clemson blvd, clemson SC"};
  string email {"jrsmith@clemson.edu"};
  long int TeacherID {123456789};
  string department {"Computer Science"};

public:
  //public constructor definitions
  Teacher() = default; //Default constructor
  Teacher(string n, string a, string e, long int id, string d) : 
  name{n}, address{a}, email{e}, TeacherID{id}, department{d} {}
  //public member function prototypes
  void setName(string n);
  void setAddress(string a);
  void setEmail(string e);
  void setTeacherID(long int id);
  void setDepartment(string d);
  string getName();
  string getAddress();
  string getEmail();
  long int getTeacherID();
  string getDepartment();
};//End of "Teacher" class

#endif