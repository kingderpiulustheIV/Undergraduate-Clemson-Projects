// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include <iostream>

using namespace std;

string Hand::printHand(){ // Prints the user each individual cards: color and rank in their hand.

    string handString;
    int handSize = hand.size();
    for(int i = 0; i < handSize; ++i){
	    cout << "[" << i + 1 << "]" << hand[i].printCard() << " ";
    }
    return handString;
}

Card Hand::dealCard(int num){ // Returns the card the player plays then removes it from the hand. 
    Card card = hand[num];
    hand.erase(hand.begin() + (num));
    return card;
}

int Hand::getHandSize(){ // Returns hand size.
    int handSize = hand.size();
    return handSize;
}

Hand::Hand(Deck &deck, int N){ // Gives players their hand from the deck.
    for(int i = 0; i < N; i++){
    	hand.push_back(deck.drawCard());
    }
}
