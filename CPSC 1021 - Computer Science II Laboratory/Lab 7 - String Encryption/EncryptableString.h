//My Name: Jonathan Sanchez-Vayas
//Class: CPSC 1020

#ifndef ENCRYPTABLE_STRING_H_
#define ENCRYPTABLE_STRING_H_
#include <string>

using namespace std;

class EncryptableString : public string 
{
    public:
  
    EncryptableString(string letters) : string(letters) {}
    void encrypt();
};

#endif
