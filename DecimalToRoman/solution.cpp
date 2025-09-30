//Collen LArsen Z1930118
#include <iostream>
#include <string>

using namespace std;

string decimal_to_roman(int decimal_value) 
{
    // Arrays to store Roman numeral symbols and their values
    string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    string roman;
    
    // Iterate through the decimal value and convert to Roman numerals
    for (int i = 0; i < 13; i++) 
	{
        while (decimal_value >= values[i]) 
		{
            decimal_value -= values[i];
            roman += symbols[i];
        }
    }
    return roman;
}

