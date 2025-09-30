#include <iostream>
#include <string>

using namespace std;

int count_hex_a(int n) 
{
    if (n < 0) {
        return -1;
    }
    
    int count = 0;
    string hex_representation = "";
    
    // Convert the number to hexadecimal rep
    while (n > 0) 
	{
        int remainder = n % 16;
        if (remainder == 10) 
		{ 
            count++;
        }
        n /= 16;
    }
    
    return count;
}
