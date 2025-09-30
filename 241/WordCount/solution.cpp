#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

bool wc(const string& file_name, int& lines, int& words, int& characters) 
{
    ifstream file(file_name);
    if (!file.is_open()) return false;

    lines = words = characters = 0;
    bool in_word = false;
    char ch;
    bool has_chars = false;  // To detect if there are any characters in the file at all

    while (file.get(ch)) 
	{
        characters++;
        has_chars = true;

        // Check if the character is a newline
        if (ch == '\n') 
		{
            lines++;
            if (in_word) 
			{  // End the current word
                words++;
                in_word = false;
            }
        } else if (isspace(ch)) 
		{
            if (in_word) {  // End the current word
                words++;
                in_word = false;
            }
        } else {
            in_word = true;
        }
    }

    // If the file does not end in a newline but has ended a word, count the last word
    if (in_word) words++;

    // Correct the lines count if the file has any characters but no newline at the end
    if (has_chars && ch != '\n') lines++;

    return true;
}

