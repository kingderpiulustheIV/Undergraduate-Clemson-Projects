//Jonathan Sanchez-Vayas

#ifndef LEV_H_
#define LEV_H_
#include <string>

using namespace std;

class Lev{ //start of "Lev" class
private:
	//Private member variable declaration
	string make {"Toyota"};
	string model {"Prius"};
	int year {2015};
	string carColor {"Blue"};
	string hybridOrElectric {"Hybrid"};

public:

    //Public Constructors
	Lev() = default; //Default constructor
	Lev (string ma, string mo, int y, string c, string h) :
	make{ma}, model{mo}, year{y}, carColor{c}, hybridOrElectric{h} {}

	string getMake()const;	
	string getModel()const;
	int getYear()const;
	string getCarColor()const;
	string getHybridOrElectric()const;

    //public member function declarations
	void setMake(string);
	void setModel(string);
	void setYear(int);
	void setCarColor(string);
	void setHybridOrElectric(string);

};  //End of "lowEmmisionVehicle" class

#endif