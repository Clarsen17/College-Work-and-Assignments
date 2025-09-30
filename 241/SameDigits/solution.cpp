//Collen Larsen z1930118

#include <iostream>
#include <string>

using namespace std;

bool same_digits(int a, int b) 
{
    // Convert integers to strings for easier comparison
    std::string str_a = std::to_string(a);
    std::string str_b = std::to_string(b);

    // Check if both strings have the same length
    if (str_a.length() != str_b.length()) 
	{
        return false;
    }

    // Count occurrences of each digit for both numbers
    int count_a[10] = {0};
    int count_b[10] = {0};

    for (char digit : str_a) 
	{
        count_a[digit - '0']++;
    }

    for (char digit : str_b) 
	{
        count_b[digit - '0']++;
    }

    // Compare the count of each digit
    for (int i = 0; i < 10; ++i) 
	{
        if (count_a[i] != count_b[i]) 
		{
            return false;
        }
    }

    return true;
}
