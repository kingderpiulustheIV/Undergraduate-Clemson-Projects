//My Name: Simon He
//My Class: CPSC 1021

#include"Pstring.h"
#include<cstring>

//initalizes string s
Pstring::Pstring(string s) : ostring {s} {}

bool Pstring::isPalindrome()
{
	int len = 0;
	
	len = ostring.length();
	
	//checks if first and last characters are the same and each subsequential char
	for(int i = 0; i < len; i++)
	{
		if(ostring[i] != ostring[len-i-1])
		{
			return false;
		}
		
		else
		{
			return true;
		}
	}
	return true;
};	





	

