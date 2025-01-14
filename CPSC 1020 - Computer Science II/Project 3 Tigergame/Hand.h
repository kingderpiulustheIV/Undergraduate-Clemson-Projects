// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#ifndef HAND_H_
#define HAND_H_

#include "Card.h" // Needed to inherit card class.
#include "Deck.h" // Needed to inherit deck class.
#include <vector> // Neeeed for a vector of cards that are the player's hand.
#include <string> // needed for string variables
#include <sstream>

using namespace std;

class Hand
{
    private:
        vector<Card> hand; //  A vector of cards that are the player's hand.
    public:
        Hand() = default;
        Hand(Deck &deck, int N); 
        string printHand(); // Prints the users hand of cards.
        Card dealCard(int num); // Player plays a card.
        int getHandSize(); // Returns hand size.
  
};

#endif // HAND_H_
