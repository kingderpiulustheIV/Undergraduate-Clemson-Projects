// Sean Farrell

#include "TA.h"

TA::TA(){}

string TA::getName(){           // Returns TA's name.
  return name;
}
void TA::setName(string n){     // Sets TA's private name to public equivalnt.
  name = n;
}
void TA::setAddress(string a){  // Sets TA's address to public equivalnt.
  address = a;
}
string TA::getAddress(){        // Returns address.
  return address;
}
void TA::setEmail(string e){    // Sets TA's email to public equivalnt.
   email = e;
}
string TA::getEmail(){           // Returns email.
  return email;
}
long int TA::getGradID(){        // Returns graduate id.
  return gradID;
}
void TA::setGradID(long id){    // Sets TA's graduate id to public equivalnt.
   gradID = id;
}
string TA::getMajor(){           // Returns TA's major.
   return major;
 }
void TA::setMajor(string m){     // Sets TA's major to public equivalnt.
  major = m;
}