// My Name: Sean Farrell
// My Class: CPSC 102
// Date: 12/2/2022
// Desc: Program plays tiger card game against player and computer.
// Time: Approx. 3 hours
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include <vector>

int main() {

	//Variable declarations to implement to find statistics for multiple games.
	int roundsTotal = 0;
	int compTotalScore = 0;
	int playerTotalScore = 0;
	int compWins = 0;
	int playerWins = 0;
	vector<int> playerScores;
    vector<int> compScores;
	char anotherGame = 'y';
	
	//Start while loop to continue playing more games after the game ends.
	while(anotherGame == 'y'){
	  int numCards = 0;

      //Welcomes the user to tiger game.
	  cout << "Welcome to Tiger Game!" << endl;

	  //Allows the user to choose how many cards to have in a hand which determinds how many rounds to play, if there are enough cards in the deck
	  cout << "How many number of cards in your hand you would like to have: " << endl;
	  cin >> numCards;
	  while(numCards > 10 || numCards < 1){ // Max number of cards in a deck and rounds is 10 because their are 21 cards in the deck.
		  cout << "Please enter a different number, not enough cards in deck" << endl; // Reprompts the user for invalid input.
		  cin >> numCards;
	  }

	  //Create a deck of cards and shuffle it.
	  Deck deckOfCards;
	  deckOfCards.shuffle();
	  cout << "The deck has been shuffled and each player has drawn " << numCards << " cards" << endl;

	  //Create two players, one computer one human.
	  Player player(deckOfCards, numCards);
	  Player comp(deckOfCards, numCards);
	   

	  //Creates Varaibules and objects needed to caculated values of cards before they get used. 
      int cardSelect;
	  Card compCard;
	  Card playerCard;
	 

	  // plays how many rounds are played basied on the number of cards in a players hand.
	 for(int i = 0; i < numCards; ++i){
		cout << "\nRound " << i +1 << endl;
		cout << "------" << endl;

		// Computer card is played at random.
		int compSelection = rand() % comp.hand.getHandSize();
		compCard = comp.hand.dealCard(compSelection);
		cout << "The computer plays: " << compCard.printCard() << endl;
				

		// Displays the users hand then the user chooses what card to use. 
		cout << endl << player.hand.printHand() << endl;
		cout << "Which card do you want to play? " ;
		cin >> cardSelect;
		while(cardSelect > player.hand.getHandSize()){
		cout << "Please enter a valid number: " << endl; // reprompts the user if they enter invalid input.
		cin >> cardSelect;
				}
		playerCard = player.hand.dealCard(cardSelect - 1);
		cout << "You Played: " << playerCard.printCard() << endl; // displays the card you playyd.
				

		// If the computer has the higher value card the computer wins.
		if(compCard.getValue() > playerCard.getValue()) {
			cout << "\nThe computer wins this round!" << endl;
            if( compCard.getColor() == Card::tiger) { // If the computer has a tiger card the scores get updated accordingly and ends the game.
                comp.score += 20;
                cout << "Game Over!" << endl << endl;
                    break;
                        
                }
            comp.score += (compCard.getValue() + playerCard.getValue());
			}

        // If the player has the higher value card the computer wins.
		else if(compCard.getValue() < playerCard.getValue()){
			cout << "\nYou win this round!" << endl;
            if( playerCard.getColor() == Card::tiger) { // If the player has a tiger card the scores get updated accordingly and ends the game.
                player.score += 20;
                cout << "Game Over!" << endl << endl;
                break;
                }
            player.score += (compCard.getValue() + playerCard.getValue());
			}
            //displays tie if  a tie occours in the round.
		else{
			cout << "Tie!" << endl;
			}

		// Print Player and computer current scores after each round of the game.
		cout << "Current scores: " << endl;
		cout << "Human: " << player.score << endl;
		cout << "Computer: " << comp.score << endl << endl;

         } // End of for loop of each round. 

	  

		//Print final game results.  
		cout << "FINAL SCORE: " << endl;
		cout << "Player: " << player.score << endl;
		cout << "Compuer: " << comp.score << endl;
		if(comp.score > player.score){
			cout << "Computer has won!" << endl << endl;
			compWins++;
		}
		else{
			cout << "Human has won!" << endl;
			playerWins++;
		}

		//Collecting data for game summary
		
		compScores.push_back(comp.score);
		playerScores.push_back(player.score);
		compTotalScore += comp.score;
		playerTotalScore += player.score;
        roundsTotal++;

		//Ask the user if they want to play another game
		cout << "Would you like to play again? (y/n): ";
		cin >> anotherGame;
		cout << endl;
	} // End of while loop. 
	

	cout << endl << "Played " << roundsTotal; // Determinds and displays correct grammer of number of games played as well as how many games each player won.
	if(roundsTotal == 1){
		cout << " Game" << endl;
	}
	else{
		cout << " Games" << endl;
	}
	cout << "--------------------------" << endl;
	cout << "Computer won " << compWins;
  if(compWins == 1){
		cout << " Game" << endl;
	}
	else{
		cout << " Games" << endl;
	}
	cout << "Player won " << playerWins;
	if(playerWins == 1){
		cout << " Game" << endl << endl;
	}
	else{
		cout << " Games" << endl << endl;
	}
  
 
// Displays how much each player scored in each game.
  for(int i = 1; i <= roundsTotal; i++){
  	cout << "Game " << i << "" << endl;
  	cout << "Computer scored: " << compScores[i-1] << endl;
  	cout << "Player scored: " <<  playerScores[i-1] << endl << endl;

  }
  
	// Displays total scores of all points each player has won.
	cout << "Total Scores" << endl;
	cout << "------------" << endl;
	cout << "Computer scored " << compTotalScore << " total points" << endl;
	cout << "Player scored " << playerTotalScore << " total points" << endl;
	return 0;
}
