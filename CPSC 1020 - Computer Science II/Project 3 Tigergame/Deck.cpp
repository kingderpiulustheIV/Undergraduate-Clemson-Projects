// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#include "Deck.h"
#include "Card.h"
#include <iostream>

using namespace std;

void Deck::shuffle() { // Shuffles deck randomly basied on a seed from current time.
    srand(time(NULL));
    random_shuffle(deck.begin(), deck.end());
}

Card Deck::drawCard(){ // Draws a card to the player then discards the card.
    Card card = deck.back();
    deck.pop_back();
    return card;
}

int Deck::getDeckSize(){ // Displays the deck size.
    int deckSize = deck.size();
    return deckSize;
}

Deck::Deck(){ // Defult constructor populates the deck vector with 10 orange cards, 10 purple card,  with ranks 1-10 and 1 tiger card.
    vector<Card> deckOfCards = deck;

    //Adds 10 purple cards to the deck
    for(int i = 1; i <= 10; i++){
        deck.push_back(Card(i, Card::purple));
    }

    //Adds 10 orange cards to the deck
    for(int i = 1; i <= 10; i++){
        deck.push_back(Card(i, Card::orange));    
    }
    
    //Adds a single tiger card with rank 10, this card ends the game
    deck.push_back(Card(10, Card::tiger));
}



