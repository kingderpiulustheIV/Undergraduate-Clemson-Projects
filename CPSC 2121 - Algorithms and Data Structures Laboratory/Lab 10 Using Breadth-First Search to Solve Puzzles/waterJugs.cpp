/*
 * Name: Sean Farrell
 * Date Submitted: 12/4/2024
 * Lab Section: 006
 * Assignment Name: Lab 10: Using Breadth-First Search to Solve Puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void)
{
  //Implement this function

  // Creates Jug A and B and makes them a pair
  state  currentState = make_pair(0,0);
  int jugA = 3;
  int jugB = 4;
  state end = make_pair(jugA, jugB);

  // Repeats the following until the current state equals the end state
  while(currentState != end) {

      state next;

      // Fills jug A

      next = make_pair(jugA, currentState.second);
      if (next != currentState) {
          pair<state, state> edge = make_pair(currentState, next);
          nbrs[currentState].push_back(next);
          edge_label[edge] = actions[0];
      }

      //Fills jug B

      next  = make_pair(currentState.first, jugB);
      if (next != currentState) {
          pair<state, state> edge = make_pair(currentState, next);
          nbrs[currentState].push_back(next);
          edge_label[edge] = actions[1];
      }

      // Empties jug A

      next = make_pair(0, currentState.second);
      if (next != currentState) {
          pair<state, state> edge = make_pair(currentState, next);
          nbrs[currentState].push_back(next);
          edge_label[edge] = actions[2];
      }

      // Empties jug B

      next = make_pair(currentState.first, 0);
      if (next != currentState) {
          pair<state, state> edge = make_pair(currentState, next);
          nbrs[currentState].push_back(next);
          edge_label[edge] = actions[3];
      }

      // Pours jug A into jug B

      int newJugA = currentState.first;
      int newJugB = currentState.second;
      if (currentState.second < jugB) {
          while (newJugA > 0 && newJugB < jugB) {
              newJugB++;
              newJugA--;
          }
          next = make_pair(newJugA, newJugB);
          if (next != currentState) {
              pair<state, state> edge = make_pair(currentState, next);
              nbrs[currentState].push_back(next);
              edge_label[edge] = actions[4];
          }
      }

      // Pours jug B into jug A;

      newJugA = currentState.first;
      newJugB = currentState.second;
      if (currentState.first < jugA) {
          while (newJugA < jugA && newJugB > 0) {
              newJugA++;
              newJugB--;
          }
          next = make_pair(newJugA, newJugB);
          if (next != currentState) {
              pair<state, state> edge = make_pair(currentState, next);
              nbrs[currentState].push_back(next);
              edge_label[edge] = actions[5];
          }
      }

      // updates the current state of the jugs

      if (currentState.second == jugB)
          currentState = make_pair(currentState.first + 1, 0);
      else
          currentState = make_pair(currentState.first, currentState.second + 1);
  }
}

//int main(void)
//{
//  build_graph();
//
//  state start = make_pair(0,0);
//
//  for (int i=0; i<5; i++)
//    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
//  search (start);
//  if (visited[make_pair(-1,-1)])
//    print_path (start, pred[make_pair(-1,-1)]);
//  else
//    cout << "No path!\n";
//
//  return 0;
//}
