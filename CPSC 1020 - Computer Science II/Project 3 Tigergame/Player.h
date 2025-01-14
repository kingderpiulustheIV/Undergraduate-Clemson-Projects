// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>

using namespace std;

class Player
{
    public:
	   Hand hand; // Needs a hand object when a player is created
	   int score {0}; // defult value of score is zero
       Player() = default;
       Player(Deck &deck, int N) : hand(deck, N) {} // Overloaded constructor that creates a player object with specidifed deck and how many cards the player has in their deck.
};
  

#endif // PLAYER_H_
