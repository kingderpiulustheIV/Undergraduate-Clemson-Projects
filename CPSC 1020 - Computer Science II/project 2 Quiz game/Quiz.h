// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 10/28/2022
// Desc: Creates a quiz for the user to complete from a textfile..
// Time: Approx. 10 hours
#ifndef QUIZ_H_
#define QUIZ_H_
#include <string> //needed for getting user input and from input .tct.

class Quiz{  // Allows quiz class to be accesed by main.
private:
    std::string question; // Private string for question from .txt 
    std::string answer;   // Private variable user enters a string varaible for an awnser.
    static int score;     // private static int for current score of the quiz.
public:
    Quiz(); // Constructur to initalize private variables.
    Quiz(std::string q, std::string a);  // sets private to public variables.
    std::string getQuestion(); //returns private string question.
    std::string getAnswer();   //returns private string answer
    static int getScore();    // returns private int score
    void static updateScore(int val); //function in class to update score
friend std::string printResult(int questions, int correct, int wrong); // allows print result function to be a freind.
};
#endif