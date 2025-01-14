// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 10/28/2022
// Desc: Creates a quiz for the user to complete from a textfile..
// Time: Approx. 10 hours
#include <iostream>      // Needed for cin c out
#include <string>        // Nedded for string variables.
#include <vector>        // Needed for vectors.
#include <cstdlib>       // Needed for random numbers.
#include <ctime>         // Needed for clock for random number seed.
#include <fstream>       // Needed for file input and output
#include <algorithm>     // Needed for random shuffle
#include "Quiz.h"        // Needed for Quiz objects.
#include "printResult.h" // Nedded for program output.

int main(int argc, char* argv[]) {
// Reads and opens  a .txt file the user enters with the execute command in the command line.
	std::ifstream myFile;
	std::string fileName = *(argv + 1);
	myFile.open(fileName, std::ios_base::in);
	//Create a string vector of quiz objects.
	std::vector<Quiz> quizVector;
	    // Variables used to set contects from .txt files to strings 
		std::string q; // For questions
		std::string a; // For awnsers
        while (getline(myFile, q )&& getline(myFile, a)) {  //sets the quiz object's questions and awnsers from the .txt file.
            		q = q.substr(3);
				    a = a.substr(3);
				    quizVector.push_back(Quiz{q,a});
            }
    int totalCorrect = 0;
    int totalWrong = 0;
    
    // Shuffles the vector based on a random number with a seed based on the current time of the clock.
    
    std::srand(time(NULL));
	std::random_shuffle(quizVector.begin(),quizVector.end());
	for (std::vector<Quiz>::iterator it = quizVector.begin(); it != quizVector.end(); ++it)  { // For loop that gets the users input for awnsers of the question and outputs if the user is correct or not.
		
		std::string answer;
		std::cout << (*it).getQuestion() << std::endl;
		std::cout << "Type in your answer: ";
		getline(std::cin, answer);
		if (answer == (*it).getAnswer()) {
			std::cout << "Correct!" << std::endl;
			Quiz::updateScore(1);
            totalCorrect += 1; // Accumulates total correct awnsers.
		}
        else {
            std::cout << "Wrong! Correct answer: " << (*it).getAnswer() << std::endl;
            Quiz::updateScore(-1);
            totalWrong += 1; // Accumulates total wrong awnsers.
        }
		std::cout << "Current Score: " << Quiz::getScore() << std::endl << std::endl; // shows current score
	}
	std::cout << printResult(quizVector.size(), totalCorrect, totalWrong); // prints number of questions completed total correct and total wronb.
	myFile.close(); // Close input .txt files.
}