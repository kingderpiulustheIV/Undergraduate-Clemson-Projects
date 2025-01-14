//My Name: Simon He
//My Class: CPSC 1021

#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student
{
	private:
	string name{"John"};
	string address{"123 clemson blvd SC"};
	string email{"john@gmail.com"};
	int year{2000};
	string major{"Computer Science"};
	
	public:
	Student();
	bool setName(string n);
	bool setAddress(string a);
	bool setEmail(string e);
	bool setYear(int y);
	bool setMajor(string m);
	
	string getName()
	{return name;};
	
	string getAddress()
	{return address;};
	
	string getEmail()
	{return email;};
	
	int getYear()
	{return year;};
	
	string getMajor()
	{return major;};
};
#endif