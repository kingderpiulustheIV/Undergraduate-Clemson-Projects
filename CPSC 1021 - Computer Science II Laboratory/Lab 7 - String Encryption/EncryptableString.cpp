//My Name: Jonathan Sanchez-Vayas
//Class: CPSC 1020

#include "EncryptableString.h"

using namespace std;

void EncryptableString:: encrypt() 
{
	int last = length();

	for( int i = 0; i < last; i++) 
	{ 
		if( ((*this)[i] >= 'a' && (*this)[i] < 'z') || ((*this)[i] >= 'A' && (*this)[i] < 'Z'))
		{
		    (*this)[i] += 1;
		}
		else if((*this)[i] == 'z' || (*this)[i] == 'Z')
		{
			(*this)[i] -= 25;
		}
	}	
}
