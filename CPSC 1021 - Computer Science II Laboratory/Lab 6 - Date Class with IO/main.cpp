#include <iostream>
#include "Date.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
int main(int argc, char const *argv[])  {
    ifstream myFile;
	string fileName = argv[1];
	myFile.open(fileName/*, std::ios_base::in*/);
	int totalDates = 0;
	myFile >> totalDates;
	myFile.ignore();
	//cout << "totalDates: " << totalDates << endl;
	string d = "";
	//getline(myFile, d);
	vector<Date> dateVector;
     while(getline(myFile,d) && !myFile.eof()) {
		 stringstream dStrStream{d};
		 //cout << dStrStream.str() << endl;
		 int mTemp;
		 dStrStream >> mTemp;
		 int dTemp;
		 dStrStream >> dTemp;
		 int yTemp;
		 dStrStream >> yTemp;
         dateVector.push_back(Date(mTemp, dTemp, yTemp));
    }
    ofstream output;
    output.open("ouput.txt");
	std::sort(dateVector.begin(), dateVector.end(), Date::compare);
	for (int i = 0; i < totalDates; i++) {
		output << dateVector[i].print();
        cout << dateVector[i].print();
	}

	myFile.close();
	output.close();

	//SEAN MAKES THE OFSTREAM OUPUT HERE
	
	return 0;
}