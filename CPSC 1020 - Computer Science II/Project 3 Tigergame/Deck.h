// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#ifndef DECK_H_
#define DECK_H_

#include <vector> // Needed for vector vairabels.
#include <algorithm> // Needed for random_shuffle
#include <cstdlib> // Needed for random numbers. 
#include <ctime> // Needed for time();
#include "Card.h" // Needed to inherit card.h

using namespace std;

class Deck
{
    private:
        vector<Card> deck; // Creates private vector of card objects.
    public:
        Deck();  
        void shuffle(); // Shuffles deck randomly basied on a seed from current time.
        Card drawCard(); // Draws a card to the player then discards the card.
        int getDeckSize(); // Displays the deck size.
};
  

#endif // DECK_H_
