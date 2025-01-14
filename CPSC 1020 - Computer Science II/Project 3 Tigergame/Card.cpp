// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#include "Card.h"
#include <iostream>

using namespace std;

string Card::printCard(){  // Prints the cards color and rank of card object.
    string cardString;

    if(color == 0){
        cardString = "purple:" + to_string(rank);
    }
    else if(color == 1){
        cardString = "orange:" + to_string(rank);
    }
    else{
        cardString = "tiger:" + to_string(rank);
    }

    return cardString;
}

int Card::getRank(){ // Returns rank of card object.
    return rank;
}

Card::Color Card::getColor(){ // Returns color of card object.
    return color;
}

int Card::getValue(){ // returns value of card object.
    return value;
}

Card::Card(int rank, Color color){ // sets the stats of the card based on the overload constructor's parameters.
    this->rank = rank;
    this->color = color;
    if(color == purple){
        value = rank;
    }
    else if(color == orange || color == tiger){
        value = rank * 2;
    }    
}

