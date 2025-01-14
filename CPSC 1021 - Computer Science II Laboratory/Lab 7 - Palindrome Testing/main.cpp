//My Name: Simon He
//My Class: CPSC 1021

#include"Pstring.h"
#include<iostream>
#include<string>

using namespace std;

int main()
{
	string userInput;
	
	//asks user to input a string
	cout << "This is a palindrome-testing program. Enter a string to test: ";
	cin  >> userInput;
	
	//creates an object of Pstring
	Pstring pstring(userInput);
	
	//outputs the statements depending on if the string is a palindrome
	if(pstring.isPalindrome() == true)
	{
		cout << userInput << " is a palindrome" << endl;
	}
	
	else
	{
		cout << userInput << " is not a palindrome" << endl;
	}

	return 0;
}


	

