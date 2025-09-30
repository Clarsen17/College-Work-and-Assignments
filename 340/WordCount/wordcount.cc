// Name: Collen Larsen 
// ZID: z1930118 
// Class: 340-1 Lab
// File Name: WordCount.cc
// Description: Implements a hash table with separate chaining to store unique words and the number of occurrences of each word.
#include "wordcount.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>

// Constructor
WordCount::WordCount(int sz) : tableSize(sz), hashTable(sz) {}

// Hash Function
int WordCount::hash(string s) 
{
    return hashFunction(s) % tableSize;
}

// Count (Search)
int WordCount::count(string word) 
{
    int index = hash(word);
    auto& chain = hashTable[index];
    auto it = std::find_if(chain.begin(), chain.end(), [&](const std::pair<string, int>& pair) 
	{
        return pair.first == word;
    });
    if (it != chain.end()) 
	{
        return it->second;
    }
    return 0;
}

// Add (Insert)
void WordCount::add(string word)
 {
    int index = hash(word);
    auto& chain = hashTable[index];
    auto it = std::find_if(chain.begin(), chain.end(), [&](const std::pair<string, int>& pair) 
	{
        return pair.first == word;
    });
    if (it != chain.end()) 
	{
        it->second++; // Increment count if word exists
    } else {
        chain.emplace_back(word, 1); // Add new word with count 1
    }
}

// Print
void WordCount::print() 
{
    std::vector<std::pair<string, int>> words;
    for (auto& entry : hashTable)
	 {
        for (auto& pair : entry) 
		{
            words.push_back(pair);
        }
    }
    std::sort(words.begin(), words.end());
    for (auto& pair : words) 
	{
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// File Word Count
void printFileWordCount(string filename, int tableSize) 
{
    WordCount wc(tableSize);
    std::ifstream file(filename);
    if (!file) 
	{
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    string word;
    while (file >> word) 
	{
        // Convert to lowercase
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) 
		{
            return std::tolower(c);
        });
        // Remove punctuation
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) 
		{
            return std::ispunct(c);
        }), word.end());
        wc.add(word);
    }
    file.close();
    wc.print();
}

