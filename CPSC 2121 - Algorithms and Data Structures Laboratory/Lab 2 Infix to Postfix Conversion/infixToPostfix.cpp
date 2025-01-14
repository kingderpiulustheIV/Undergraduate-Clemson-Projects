/*
 * Name: Sean Farrell
 * Date Submitted: 9/11/2023
 * Lab Section: 1
 * Assignment Name: Lab 2 Infix to postfix Conversion.
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

//Converts an infix arithmetic expression into postfix
//The function takes 3 parameters
//First parameter: array of strings for infix expression
//    each string is either an integer number or operator symbol
//Second parameter: number of strings in infix expression
//Third parameter: array of strings for postfix expression
//    generated by function, same format as first parameter
//    assumes that postfix is at least the size of postfix
//Return value: int, number of strings in postfix expression
//    Returns 0 if an error is encountered when converting expression
//    An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
//Operator symbols:
// ( : left parenthesis, all operations between this and ")" take place first
// ) : right parenthesis, all op.s back to previous "(" take place first
// * : multiplication, higher precedence - takes place before "+" and "-"
// / : division, higher precedence - takes place before "+" and "-"
// % : remainder, higher precedence - takes place before "+" and "-"
// + : addition, lower precedence - takes place after "*" , "/" , "%"
// - : subtraction, lower precedence - takes place after "*" , "/" , "%"
//The function is not specified to work with any other operator symbols
//Any string in infix may be assumed to be an integer operand if none
// of the above symbols


// Checks precendent basicly order of operations from math.
int checkPrecedent(char value) {

    // returns 2 for modulo division and multipication/division

    if (value  == '*' || value == '/' || value == '%')
        return 2;
        // returns 1  for addition and subtraction

    else if (value == '+' || value == '-')
        return 1;
        // returns 1 for everything else

    else
        return -1;
}

int infixToPostfix(string infix[], int length, string postfix[])
{
    // Integers for start end and number of elements index number and value of elements for the stack
    int start = 0;
    int end = 0;
    int count = 0;
    int index = 0;
    int value = length;

    // creates a stack

    stack<string> fixStack;
    fixStack.push("|");

    // if infix equals parentheses sets the values to 0.

    for (int i = 0; i < length -1; i++) {
        if(infix[i][0] != '(' && infix[i][0] == infix[ i + 1] [0] && infix[i][0] != ')')
            value = 0;
    }
    // repeats until i is equal to length

    for( int i = 0; i < length; i++) {

        // if first data in the row is a digit postfix  is equal to it.

        if(isdigit(infix[i][0]))
            postfix[index++] = infix[i];

            // If infix[i] is a "(" pushes it to the stack and increase count and start by 1.
        else if (infix[i][0] == '(') {
            fixStack.push(infix[i]);
            count +=  1;
            start += 1;
        }
            //
            // If infix[i] is a ")" pushes it to the stack and increase count and start by 1.
        else if (infix[i][0] == ')') {

            // if first element of stack does not equal "|" "(" sets the string to the value of the top of the stack then pops it.

            while(fixStack.top()[0] != '|' && fixStack.top()[0] != '(') {
                string hold = fixStack.top();
                fixStack.pop();

                // Sets the next postfix element to hold.

                postfix[index++] = hold;
            }
            count +=  1;
            end +=  1;

            // deletes the top element if the first element in stack is "("

            if(fixStack.top()[0] == '(')
                fixStack.pop();
        }
            // if infix[i][0] does not equal ")" or "("
        else {

            // if top element of stack does not equal "|"
            // and if check precedent function of infix[i][o] is less than the stacks top element value
            // then it sets the string hold to the top element of the stack and pops it
            // then it sets the next element of postfix to the string hold

            while(fixStack.top()[0] != '|' && checkPrecedent(infix[i][0]) <= checkPrecedent(fixStack.top()[0])) {
                string hold = fixStack.top();
                fixStack.pop();
                postfix[index++] = hold;
            }

            // adds infix[i] value to a new element on the top of the stack

            fixStack.push(infix[i]);
        }
    }
    //subtracts count from value

    value -= count;

    // value equals 0 if end does not equal start

    if (end != start)
        value = 0;
    else {

        // sets the top elements of the stack to an element of post fix then deletes the top stack element.

        for(index = index; index < value; index++)
        {
            postfix[index] = fixStack.top();
            fixStack.pop();
        }
    }
    // returns value of infix to postfix function.

    return value;
}

//Main function to test infixToPostfix()
//Should convert 2 + 3 * 4 + ( 5 - 6 + 7 ) * 8
//            to 2 3 4 * + 5 6 - 7 + 8 * +
/* int main()
{
    string infixExp[] = {"2", "+", "3", "*", "4", "+", "(",
                         "5", "-", "6", "+", "7", ")", "*",
                         "8"};
    string postfixExp[15];
    int postfixLength;

    cout << "Infix expression: ";
    for (int i=0; i<15; i++)
    {
        cout << infixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: 15" << endl << endl;

    postfixLength = infixToPostfix(infixExp, 15, postfixExp);

    cout << "Postfix expression: ";
    for (int i=0; i<postfixLength; i++)
    {
        cout << postfixExp[i] << " ";
    }
    cout << endl;
    cout << "Length: " << postfixLength << endl;
    
    return 0;
}
*/