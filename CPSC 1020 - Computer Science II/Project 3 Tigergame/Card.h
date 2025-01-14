// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#ifndef CARD_H_
#define CARD_H_

#include <string> // Needed for string variables.

using namespace std;

class Card
{
    public:
        enum Color{purple, orange, tiger}; // Creates the three types colord of cards.

        Card() = default;
        Card(int rank, Color color);
        string printCard(); // Displays cards color and rank.

        int getRank(); // Returns card objects rank.
        Color getColor();  //Returns card objects color
        int getValue(); // Returns card objects value
    private:
        //default values for private variables for the object card.
        int rank {0}; 
        Color color {purple};
        int value {0};

};
  

#endif // CARD_H_
