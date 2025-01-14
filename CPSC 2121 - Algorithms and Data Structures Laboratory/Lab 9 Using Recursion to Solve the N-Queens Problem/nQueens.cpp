/*
 * Name: Sean Farrell
 * Date Submitted: 11/20/2023
 * Lab Section: 006
 * Assignment Name: Lab 9: Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board


//  helper function that determines if the queen can be placed
bool isValid(int** queen, int n, int col, int row) {
    // checks if queen can be placed int the same row.
    for (int i = 0; i < n; i++) {
        if (queen[row][i] == 1)
            return false;
    }

    // checks if queen can be placed on diagonal bottom left to top right
    for (int x = row, y = col; x>= 0 && y >= 0; x--, y--) {
        if(queen[x][y] == 1)
            return  false;
    }
    // checks if queen can be placed on diagonal top left to bottom right
    for (int x = row, y = col; x < n&& y >= 0; x++, y--) {
        if(queen[x][y] == 1)
            return  false;
    }
    return  true;
}

// helper function that calculates the solution of total queens.
int solution(int** queenArray, int n, int col) {
    int total = 0;
    int row;
    if (col == n)
        return 1;
    for (int i = 0; i < n; i++) {
        row = i;
        if(isValid(queenArray, n, col, row) == true) {
            queenArray[row][col] = 1; // places queen
            total = total + solution(queenArray, n, col +1); // recursively calls
            queenArray[row][col] = 0; // resets queens
        }
    }
    return total;
}


int nQueens(int n)
{
    //Implement int nQueens(int n)
    //Feel free to implement any recursive helper functions
    int** queen = new int* [n];
    for (int i = 0; i < n; i++) {
        queen[i] = new int[n];
        for ( int j = 0; j < n; j++)
            queen[i][j] = 0;
    }
    return solution(queen, n, 0); // returns number of solutions of queens.
}
//
//int main()
//{
//    cout << "1: " << nQueens(1) << endl;
//    cout << "2: " << nQueens(2) << endl;
//    cout << "3: " << nQueens(3) << endl;
//    cout << "4: " << nQueens(4) << endl;
//    cout << "5: " << nQueens(5) << endl;
//    cout << "6: " << nQueens(6) << endl;
//    cout << "7: " << nQueens(7) << endl;
//    cout << "8: " << nQueens(8) << endl;
//    cout << "9: " << nQueens(9) << endl;
//    cout << "10: " << nQueens(10) << endl;
//    cout << "11: " << nQueens(11) << endl;
//    cout << "12: " << nQueens(12) << endl;
//    return 0;
//}