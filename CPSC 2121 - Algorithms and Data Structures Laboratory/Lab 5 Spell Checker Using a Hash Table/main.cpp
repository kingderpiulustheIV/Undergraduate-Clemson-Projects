/*
 * Name: Sean Farrell
 * Date Submitted: 10/12/2023
 * Lab Section: Section 1
 * Assignment Name: Spell Checker Using a Hash Table
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 // loads a string set from data from a textfile.
 
 void loadStringset(Stringset& words, string filename)
 {
     string current;
     ifstream infile(filename);
	
	// inserts all words of a text file to a stringset variable
	
     while(getline(infile, current))
         words.insert(current);
 }
 
 
 // Finds and lists all words that are spelled incorrectly and corrects the spelling erros
 
 vector<string> spellcheck(const Stringset& words, string word)
 {
	 // String vairable that is set to the word that will be used to spell check.
	 
     string tempWord; 
     tempWord = word;
	
	// Vector for all words that needed to be spell checked.
	
     vector<string> listTempWord; 
     
	// Loops through all character and words in the string set.
     
	 for (int i = 0; i < word.length(); i++) 
     {
         for (char j = 'a'; j < 'z' + 1; j++) 
         {
        
			 tempWord.replace(i, 1, 1, j); 
             
			 
			 // Adds a correct word to the vector if it detects a spelling error.
			 
             if (tempWord != word && words.find(tempWord)) 
             {
                 listTempWord.push_back(tempWord);
             }
             tempWord = word;
         }
     }
	 
	 // Returns vector of words that are corrected.
	 
     return listTempWord; 
 }