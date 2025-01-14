 /*
 * Name: Sean Farrell
 * Date Submitted: 9/26/2023
 * Lab Section: 6
 * Assignment Name: Stack-based Postfix Expression Calculator
 */
 
#include <string>
#include <stack>

using namespace std;

//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string
int calculatePostfixExpression(string expression[], int length) {
    	
	stack<int> myStack; // Stack datatype that stores awnsers.
	int operate = 0;    // Counts how many operaters are in the string array expression.
	int operand = 0;	// Counts how many operands are in the string array expression.
	int check ;			// variable needed to check to make shure if the string array has a valid math expression.
	int awnser; 		// varible that stores the awnser of the math expression
	
	// If the int length parameter of  the function equals zero then returns 0.
	
	if (length == 0)
		return 0;
	
	// Counts how many operands and operaters are in the string array expression.
	
	for (int i = 0; i < length; i++) {
		string validate;
		validate = expression[i];
		if ( validate >= "0" && validate <= "9")
			operand++;
		else
			operate++;
	}
	// Makes shure there are are always 2 operands and one operators.
	// If not the function returns 0.
	
	check = operand - operate;
	if (check != 1)
		return 0;
	
	// Populates the stack with the numbers in the string array if input is valid.
	
	for(int j = 0; j < length; j++) {
		string temp;
		temp = expression[j];
		if ( temp >= "0" && temp <= "9")
			myStack.push(stoi(temp));
		
		// If the string element value is a operater  executes following code below.
		
		else {

			int num1 = myStack.top(); //Vairble that is set to the  value of the elemebent that's at the top of the stack
			myStack.pop(); 		  // Removes the top element from the stack.
			int num2 = myStack.top(); // Variable that is set to the second most top element of the stack.
			myStack.pop(); 		  // Removes the top element from the stack.
			
			// If the operater is addion adds the num1 and num2.
			
			if (temp == "+")
				myStack.push(num1 + num2);
			
			// If the operator is subtraction subtracts num2 from num1.
			else if (temp == "-")
				myStack.push(num2 - num1);
			
			// If the operator is mulitpcation it multiplies num1 by num2.
			
			else if (temp == "*")
				myStack.push(num2 * num1);
			
			// If the operator is division it divides num1 by num2.
			
			else if (temp == "/")
				myStack.push(num2 / num1);
			
			// If the operator is modulo finds the remander of num2 divided by num1.
			
			else if (temp == "%")
				myStack.push(num2 % num1);
			
		}
	}

	awnser = myStack.top(); // Sets the integer awnser  to the value of the top element of the stack.
	myStack.pop(); 			// Deletes the top element of the stack.
	
	// Returns awnser if the stack is empy. If not returns 0.
	 
	if (myStack.empty())
		return awnser;
	else
		return 0;
}