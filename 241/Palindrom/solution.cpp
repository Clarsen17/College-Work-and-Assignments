#include <iostream>
#include <string>

using namespace std;

bool ispalindrome(const string& s) 
{
    string clean_string;
    for (char c : s) 
	{
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) 
		{
            if (c >= 'A' && c <= 'Z') 
			{
                clean_string += c + ('a' - 'A'); 
            } 
			else 
			{
                clean_string += c;
            }
        }
    }
    
    int left = 0;
    int right = clean_string.size() - 1;
    
    while (left < right) 
	{
        if (clean_string[left] != clean_string[right]) 
		{
            return false;
        }
        ++left;
        --right;
    }
    return true;
}
