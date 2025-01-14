/*
 * Name: Sean Farrell
 * Date Submitted: 12/5/2023
 * Lab Section: 006
 * Assignment Name: Word Ladder
 */

// Libraries need 
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

//words from wordlist05.txt or other specified input.txt file
vector<string> inputText;

// Varabiles needed for the breadth-first search algorithm from lab 10
unordered_map<string, bool> visited;
unordered_map<string, string> predecessor;
unordered_map<string, int> searchDistance;
unordered_map<string, vector < string>> neigborNode;
int find(string, string, vector<string>&);
void build();

//Implemented breadth-first search algorithm.
void wordLadder(string source, string target, int& steps, vector<string>& path)
{
    // Creates a huge string vector that stores the infromation from the source .txt file
	build();

	// A string queue to check through every word of the source file.
    queue<string> check;
    check.push(source);
	
	// Sets the distance to 0 before searching.
    visited[source] = true;
    searchDistance[source] = 0;

    // Seriches through the check queue until its empty.
	while (!check.empty())
    {
		// Resetts the front of the queue per while loop iteration.
        string current = check.front();
		
		// Pops the untarget word in the queue.
        check.pop();
		
		// Accumulates search distance and mark nodes in the queue have been visited 
        for (string x : neigborNode[current]) {
            if (!visited[x]) {
                predecessor[x] = current;
                searchDistance[x] = 1 + searchDistance[current];
                visited[x] = true;

                check.push(x);        
			}
		}
    }
	// searches the path of the targeted word.
    steps = find(source, target, path);
}

// Function that Searches for the targeted word.
int find(string start, string end, vector<string>& path)
{
	// Returns nothing if the user seraches the ending string that isnt equal to 0.
    if (predecessor.find(end) == predecessor.end()) 
        return 0;
	
	// Returns how many steps until the target word is located recursively. 
    if (start.compare(end) != 0) {
        int part = 1 + find(start, predecessor[end], path);

        path.push_back(end);

        return part;
    }
	// Adds the end string to the end of the path string vector. 
    else {
        path.push_back(end);

        return 0;
    }
}
// Function that reads the source .txt file.
void build(void)
{
	// Opens text file.
    ifstream word_file("wordlist05.txt");
    string curr;
	
	//copies every textfile's data into a string vector.
    while (word_file >> curr)
    {
        inputText.push_back(curr);
    }
// Populates the neighborNode string map.
    for (auto word : inputText) {
	
	// Makes shure each node in  NeghborNode is a string of 5 characters before populating the node.
        for (int i = 0; i < word.length(); i++) {
	
	// Makes shure each node in NeghborNode is a string only containing the chacters in the english alphabet before populating the node.
            for (char letter = 'a'; letter <= 'z'; letter++){
                if (letter == word.at(i))
                    continue;
                string buildCurrent = word;
                buildCurrent.at(i) = letter;
                neigborNode[word].push_back(buildCurrent);
            }
        }
    }
}

// int main(void) {
//   int steps = 0;
//   string userSource, userTarget;
//   vector<string> path;
//   cout << "Source: ";
//   cin >> userSource;
//   cout << "Target: ";
//   cin >> userTarget;
//   wordLadder(userSource, userTarget, steps, path);
//   if (steps == 0)
//       cout << "No path!\n";
//   else {
//       cout << "Steps: " << steps << "\n\n";
//       for (int i=0; i<path.size(); i++)
//           cout << path[i] << endl;
//   }
//   return 0;
// }