#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>

using namespace std;

class Visitor {
		string name, address, email, occupation, reason;
	public:
        Visitor();
		string getName ();
		void setName (string);
		string getAddress ();
		void setAddress (string);
		string getOccupation ();
		void setOccupation (string);
		string getEmail ();
		void setEmail (string);
		string getReason ();
		bool setReason (string);
};

#endif
