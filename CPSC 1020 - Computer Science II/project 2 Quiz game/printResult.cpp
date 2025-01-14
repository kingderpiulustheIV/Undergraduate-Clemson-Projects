// My Name: Sean Farrell
// My Class: CPSC 1021
// Date: 10/28/2022
// Desc: Creates a quiz for the user to complete from a textfile..
// Time: Approx. 10 hours
#include "printResult.h" //Inludes header

std::string printResult(int questions, int correct, int wrong){ // Creates a function that outputs number of correct awnsers wrong anwsers and final score with streamstring.
	std::stringstream out;
	out << "Number of questions: " << questions << std::endl << "Number correct answers: " << correct << std::endl << "Number wrong answers: " << wrong << std::endl << "Final score: " << Quiz::score << std::endl;
	return out.str();
}