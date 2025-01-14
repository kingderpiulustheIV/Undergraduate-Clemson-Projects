/*
 * Name: Sean Farrell
 * Date Submitted: 12/5/2023
 * Lab Section: 006
 * Assignment Name: Lab 11: Iterative Refinement and the Traveling Salesman Problem
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

const int N = 14; //Number of cities in cities.txt
typedef pair<double,double> Point; //<latitude,longitude> of a city
vector<Point> P(N), best; //P - current solution, best - best solution
map<Point, int> cities; //Point (latitude,longitude) -> index of city in cities.txt order
string cityNames[] = {"New York City",
                      "Chicago",
                      "Los Angeles",
                      "Toronto",
                      "Houston",
                      "Montreal",
                      "Mexico City",
                      "Vancouver",
                      "Atlanta",
                      "Denver",
                      "San Juan",
                      "New Orleans",
                      "Miami",
                      "Kansas City"}; //Index of a city -> city name

//Calculates "distance"
//Units are lat./long. "degrees" on an x-y plane
//to simplify calculations (not mi/km on globe)
double dist(int i, int j)
{
  double dx = P[(i+N)%N].first - P[(j+N)%N].first;
  double dy = P[(i+N)%N].second - P[(j+N)%N].second;
  return sqrt(dx*dx + dy*dy);
}

bool refine(double &len)
{
  //Implement this function
  //Should iterate through each pair of edges in the tour
  //checking if there is a decrease in tour length by
  //replacing these edges with their diagonals (see lab description)

  //If the decrease is more than a minimum threshold (such as 0.0001)
  //swap these edges for their diagonals (see description) and return true

  //Otherwise return false after iterating through all possible edge pairs
  //if swapping a pair of edges for their diagonals fails to decrease
  //tour length beyond a minimum threshold
  int size = P.size();
  int edge1_start, edge1_end, edge2_start, edge2_end;
  bool swapPossible = false;
  map<double, int> possible_swap;
  double currentSize; double possibleSize;
  Point hold;

  // Loops through to find solutions
  for (int i = 0; i < size; i++) {
      edge1_start = i;
      edge1_end = (i+1) % size;
      for (int j = 2; j < size; j++) {
        edge2_start = (i + j) % size;
        edge2_end = (i + j + 1) % size;
        currentSize = dist(edge1_start, edge1_end) + dist(edge2_start, edge2_end);
        possibleSize = dist(edge1_start, edge2_start) + dist(edge1_end, edge2_end);
        if ((currentSize - possibleSize > 0.001)) {
          possible_swap[currentSize-possibleSize] = edge2_start;
          swapPossible = true;
        }
      }
      // Stores shortest path
      if(swapPossible == true) {
         hold = P[possible_swap.rbegin()->second];
         P[possible_swap.rbegin()->second] = P[edge1_end];
         P[edge1_end] = hold;
         break;
      }
    }
    // Stores new length
    if (swapPossible == true) {
      len = 0;
      for(int i = 0; i < size; i++)
        len = len + dist(i, (i+1) % size);
    }
    // Returns best length for test case.
    return swapPossible;
}

//Returns best length for test case
double tspRefine()
{
  double best_len = 999999999;
  ifstream fin("cities.txt");
  for (int i=0; i<N; i++)
  {
    fin >> P[i].first >> P[i].second;
    cities[P[i]] = i;
  }

  // Initalizes variables
  int size = P.size();
  double length = 0;

  // Find length
  for (int i = 0; i < size; i++)
      length = length +dist(i, (i+1) % size);
  if ( length < best_len) {
      best_len = length;
      best = P;
  }
    while (refine(length)) {
        if (length < best_len) {
            // Stores the best path length
            best = P;
            best_len = length;
        }
    }
  //Use a loop that will repeat a certain number of times starting with
  //a randomly generated tour (P)
  //First calculate the length of this randomly generated tour
  //Then run refine() to rearrange the ordering of the cities in the
  //tour until refine() returns false
  //Finally, if final tour length < best_len replace best with the
  //current tour (P) and update best_len

  for (auto p : best) cout << cityNames[cities[p]] << endl;
  cout << "\nTotal length: " << best_len << "\n";
  return best_len;
}

//int main(void)
//{
//  double best_len = 999999999;
//  best_len=tspRefine();
//  return 0;
//}
