//My Name: Jonathan Sanchez-Vayas
//Class: CPSC 1020

#include "EncryptableString.h"
#include <iostream>

using namespace std;

int main()
{
string letters;

cout << "This is an Encryption program: Enter a string to encrypt: ";
getline(cin,letters);
EncryptableString encryptableString(letters);

encryptableString.encrypt();

cout << "Here is the encrypted string: " << encryptableString;

return 0;

}
