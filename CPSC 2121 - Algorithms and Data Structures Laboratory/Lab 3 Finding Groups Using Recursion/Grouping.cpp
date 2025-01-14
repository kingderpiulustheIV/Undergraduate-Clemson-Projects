/*
 * Name: Sean Farrell
 * Date Submitted: 9/18/2023
 * Lab Section: 006
 * Assignment Name: Lab 3: Finding Groups Using Recursion
 */

#include "Grouping.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below
//class Grouping{

Grouping::Grouping(string file) {
	string inputFile;
	ifstream input(file);
	vector<GridSquare> square;
	for(int i = 0; i < 10; i++) {
		getline(input, inputFile);
		for(int j = 0; j < 10; j++) {
			if (inputFile[j] == 'X')
				grid[i][j] = 1;
			else if (inputFile[j] == '.')
				grid[i][j] = 0;
		}
	}
	for (int k = 0; k < 10; k++) {
		for (int l = 0; l < 10; l++) {
			if (grid[k][l] == 1) {
				groups.push_back(square);
				findGroup(k, l);
			}
		}	
	}
}

void Grouping::findGroup (int row, int colum) {
	if (grid[row][colum] == 0)
		return;
	int max = 10;
	int min = 0;
	grid[row][colum] = 0;
	groups.back().push_back(GridSquare(row, colum));
	if ((row + 1) < max) 
		findGroup(row +1, colum);
	if ((row - 1) >= min)
		findGroup((row - 1), colum);
	if ((colum + 1) < max)
		findGroup(row, (colum + 1));
	if ((colum -1) >= min)
		findGroup(row, colum - 1);
}




//Simple main function to test Grouping
//Be sure to comment out main() before submitting
/*int main(int argc, char *argv[])
{
	//FILE input1 = argv[1];
    Grouping input1("argv[1]");
    input1.printGroups();
    
    return 0;
}
*/
//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}