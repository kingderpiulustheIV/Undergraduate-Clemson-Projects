/*
 * Name: Sean Farrell
 * Date Submitted: 10/12/2023
 * Lab Section: Section 6
 * Assignment Name: Spell Checker Using a Hash Table
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

// Inserts a word into the hash table vector

void Stringset::insert(string word)
{
    
	// Exectues the following code if the word is a string stream.
	
	if (!find(word))		
    {
		// Createas a hash for strings.

        hash<string> hashString;
        
        string input;
        int point;
        
		
		// Determines wether the size of the table needs to be expaneded or not.
		
        if (num_elems >= size) 
        {
            size *= 2;
            
			// Creates a temporary table that inserts the new word.
			
            vector<list<string>> tempTable(size); 
            
			
			
			// Loops through the temp table and lists and establishes the hash values.
			
            for (int i = 0; i < size / 2; i++) 
            {
                for (list<string>::const_iterator iter = table[i].begin(); iter != table[i].end(); iter++)
                {
                    input = *iter;
                    point = hashString(input) % size;
                    
                    tempTable[point].push_back(input);
                    table[i].remove(word);
                }
            }
			// sets the table to the temp table with the inserted word.
            
			table = tempTable; 
        }
        point = hashString(word) % size;
        table[point].push_back(word);
        
		// Increments the number of elements of the table by 1
        
		num_elems++;
    }
}

// Returns true if the word in a table is equal to the word in this functions parameters.

bool Stringset::find(string word) const
{
    hash<string> hashString;
    int location;
    
    location = hashString(word) % size;
    
	//loops through all of the hash and list values.
	
    for (list<string>::const_iterator iteration = table[location].begin(); 
         iteration != table[location].end(); iteration++) 
    {
		// Returns true if the word of the parameter equals a word in the table or list.
		
        if (*iteration == word) 
            return true;
    }
    return false;
}


// Removes a word from the hashtable of strings.

void Stringset::remove(string word)
{
	// Exectues the following if the word in the parameter of the function is a string stream
	
    if (find(word)) 
    {
        hash<string> hashString;
        int location;
		
		// sets the hash value of the word needed to be removed.
		
        location = hashString(word) % size;
        
		// Removes the elemnt of the by the hash value of the word that is set to be removed.
		
        table[location].remove(word);
		
		// decrements the number of elements by 1.
        
		num_elems--;
    }
}