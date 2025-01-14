// This program asks for how many time the user has rode thier bike this semester.
// The program then Calculates how many points earned this semester based on the numerical value of the user's input.
// Sean Farrell
#include <iostream>
using namespace std;

int main()
{
    int bikeRides; // variable stores the users input.

    // Asks the user how many times they have rode thier bike this semester to campus.
    cout << "Please enter the number of bike rides you have taken to campus this semester: ";
    cin >> bikeRides;


    // If the user enters invalid input such as neguitve number it re-asks the user for input until its valid.
    while (bikeRides < 0) {
        cout << "Input was invalid, ender a new number: ";
        cin >> bikeRides;
    }


    //if-else statements assign points to the different positive numbers based on the user's input.
    if (bikeRides == 0) {
        cout << "You earned 0 points this semester\n";
    }
    else if (bikeRides == 1) {
        cout << "You earned 3 points this semester\n";
    }
    else if (bikeRides == 2) {
        cout << "You earned 10 points this semester\n";
    }
    else if (bikeRides == 3) {
        cout << "You earned 15 points this semester\n";
    }
    else if (bikeRides == 4) {
        cout << "You earned 30 points this semester\n";
    }
    else if (bikeRides >= 5) {
        cout << "You earned 50 points this semester\n";
    }

    return 0; //End of program.
}
