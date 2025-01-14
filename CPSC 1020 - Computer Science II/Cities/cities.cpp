// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 11/30/2022
// Desc: A program that outputs how many cities are in the same state from the textfile.
// Time: Approx. 3 hours
#include <iostream>
#include <fstream>       // Needed to read cities.txt.
#include <string>        // Needed for string variables.
#include <sstream>   	 // Nneeded for string stream.
#include <unordered_set> // Needed for Unorderd set.
using namespace std;

int main(int argc,  char* argv[]) { 	 // Allows user to enter arguments rather than executing the .out file.
    unordered_multiset<string> cities;   // Created an unorderd multiset. 
    ifstream myFileStream("cities.txt"); // Opens cities.txt.
    string  state, line; 			 // string variables for state and line.
    while(getline(myFileStream,line)) {  //  Reads cities.txt.
        stringstream ss(line);			 // creates a string stream variabke that stores infromation from the .txt file.
        getline(ss, state, ',');	     // Stores every state name for the corrisponding city in cities .txt sperated by ",".
        cities.emplace(state);			 // Stores each individual state
    }

    for (int i =1; i < argc; i++) { 
        cout << cities.count(argv[i]) << endl; // for every state the user inputs it will display how many cities listed in cities.txt are in that state followed by a new line. 

    }

    myFileStream.close(); // closes cities.txt
    return 0; //end of program
}