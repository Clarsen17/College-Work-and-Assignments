//Collen Larsen Z1930118

#include <iostream>

using namespace std;

int count_hex_a(int n) 
{
    // If n is negative, return -1
    if (n < 0)
        return -1;

    int count = 0;
    // Convert decimal number to hexadecimal string
    string hex = "";
    while (n > 0) 
	{
        int rem = n % 16;
        if (rem < 10)
            hex = char(rem + '0') + hex;
        else
            hex = char(rem - 10 + 'A') + hex;
        n /= 16;
    }

    // Count the occurrences of 'A'
    for (char c : hex) 
	{
        if (c == 'A')
            ++count;
    }

    return count;
}
