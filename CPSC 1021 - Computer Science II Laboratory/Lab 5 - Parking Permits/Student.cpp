//My Name: Simon He
//My Class: CPSC 1021

#include"Student.h"
#include<string>
using namespace std;

// string name{"John"};
// 	string address{"123 clemson blvd SC"};
// 	string email{"john@gmail.com"};
// 	int year{2000};
// 	string major{"Computer Science"};

Student::Student() : name{"John"}, address{"123 clemson blvd SC"}, email{"john@gmail.com"}, year{200}, major{"Computer Science"} {}

bool Student::setName(string n)
{
	name = n;
	return true;
}

bool Student::setAddress(string a)
{
	address = a;
	return true;
}

bool Student::setEmail(string e)
{
	email = e;
	return true;
}

bool Student::setYear(int y)
{
	if (y > 0)
	{
		year = y;
		return true;
	}
	else
	{
		return false;
	}
}
	
bool Student::setMajor(string m)
{
	major = m;
	return true;
}