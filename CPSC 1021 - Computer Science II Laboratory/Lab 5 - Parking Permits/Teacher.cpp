//Jonathan Sanchez-Vayas

#include <iostream>
#include "Teacher.h"
#include <string>
#include <iostream>


void Teacher::setName(string n){ //start of setName
  name = n; //initializes to private member "name"
}//end of setName

void Teacher::setAddress(string a){ //start of setAddress
  address = a; //initalizes to private member "address"
}//end of setAddress

void Teacher::setEmail(string e){ //start of setEmail
  email = e; //initalizes to private member "email"
}//end of setEmail

void Teacher::setTeacherID(long int id){ //start of setTeacherID
  TeacherID = id; //initalizes to private member "TeacherID"
}//end of setTeacherID

void Teacher::setDepartment(string d){ //start of setDepartment
  department = d; //initalizes to private member "department"
}//end of setDepartment

string Teacher::getName(){ //start of getName
  return name;//return string
}//end of getName

string Teacher::getAddress(){ //start of getAddress
  return address;//return string
}//end of getAddress

string Teacher::getEmail(){ //start of getEmail
  return email;//return string
}//end of getEmail

long int Teacher::getTeacherID(){ //start of getTeacherID
  return TeacherID;//return long int
}//end of getTeacherID

string Teacher::getDepartment(){ //start of getDepartment
  return department;//return string
}//end of getDepartment