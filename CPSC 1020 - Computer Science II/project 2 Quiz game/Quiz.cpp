// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 10/28/2022
// Desc: Creates a quiz for the user to complete from a textfile..
// Time: Approx. 10 hours
#include "Quiz.h"

int Quiz::score = 0; // constructs the score to 0.

Quiz::Quiz(){ // constructs private strings to "".
	question = "";
	answer = "";
}

Quiz::Quiz(std::string q, std::string a){ // sets private to public variables.
    question = q;
    answer = a;
}

int Quiz::getScore(){ // returns private int score
    return score;
}

void Quiz::updateScore(int val){   //function in class to update score
	score += val;                  //increases score by 1 if correct
	if (score < 0) score = 0;      // keeps the lowest possible score 0.
}
std::string Quiz::getQuestion(){ // returns private string question.
    return question;
}

std::string Quiz::getAnswer(){  // return private string anwser.
    return answer;
}