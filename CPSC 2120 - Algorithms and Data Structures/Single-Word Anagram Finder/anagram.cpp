/*
 * Name: Sean Farrell
 * Date Submitted: 10/27/2023
 * Assignment Name: Single Word Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

// int main()
// {
//     vector<string> words;
//     vector<string> anagrams;
//     string inputWord;
//     words=loadWordlist("wordlist.txt");
//     cout << "Find single-word anagrams for the following word: ";
//     cin >> inputWord;
//     anagrams = anagram(inputWord, words);
//     for (int i=0; i<anagrams.size(); i++)
//     {
//         cout << anagrams[i] << endl;
//     }
//     return 0;
// }

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Implement this function
vector<string> anagram(string word, vector<string> wordlist) {

    string myWord;                // String variable that holds a word form the list to be detected if it is an anagram.
    vector<string> anagramVector; // vector for all strings that are anagrams,
        
    // runs until it finishes the list
    for (int i = 0; i < wordlist.size(); i ++) {
        myWord = wordlist[i];               // word selected from the list
        unordered_map<char, int> myMap;     // Creates a map 

        // variables that retrieve the words lengths that are being compared to see if there anagrams
        int myLength = myWord.length();
        int wordLength = word.length();


        // continues to read a different string if the current word being evaluated is not an anagram
        if (wordLength != myLength) 
            continue;

        // Increments keys of myMap
        for(int j = 0; j < wordLength; j++) 
            myMap[word[j]]++;

        // loops the following code below on how many characters are on the current word being checked from the list
        for(int k = 0; k < myLength; k++) {

            //breaks if the word is not an anagram by missing or non matching characters
            if(myMap.find(myWord[k]) == myMap.end())
                break;

            //Otherwise 
            else  {
                // decrements the value for amount of chars
                myMap[myWord[k]]--;

                // empties myMap if chars == 0
                if (myMap[myWord[k]] == 0)
                    myMap.erase(myWord[k]);
            }
        }
        if(myMap.size() == 0)
            anagramVector.push_back(myWord);
    }
    // Returns a vector of all anagrams from the list
    return anagramVector;           
}