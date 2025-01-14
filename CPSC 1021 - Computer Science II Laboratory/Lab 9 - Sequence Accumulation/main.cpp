// Group members: Sean Farrell, Simon He, Jonathan Sanchez-Vayas, Adam Varady
// My Class: CPSC 1021
// Date: 12/1/22022
// Desc: Accumulater that displays 4 numbers and 4 strings
// Time: Approx. 10 min
#include"accum.h"
int main() {
    vector<int> vf;             // Creates a vector for user inputed integer.
    cout << "Enter 4 numbers";  // Prompts the user to enter 4 numbers.
    int num; 					// Variblue used for integer user input.
    for(int i= 0; i < 4; i++) { // Gets the user input for the 4 numbers.
        cin >> num;
        vf.push_back(num);
    }
    cout << "The sum of the numbers is " << accum(vf) << endl; // Displays the 4 numbers the user inputed.
    cout << "Enter 4 strings: ";                               // Prompts the user to enter 4 strings.
    vector<string> vs;										   // Creates a vector for user inputed strings.
    string name;											   // Variblue used for string user input.
    for (int j = 0; j < 4; j++ ) { // Gets the user input for the 4 strings.
        cin >> name;
    if(j <3)
        name = name + ", "; // Adds a coma inbetween each sting added to the vector.
    vs.push_back(name);
    }
    cout << "The sum of the strings is " << accum(vs) << endl;  // Displays the 4 numbers the user inputed.
    return 0;    
}