//Collen Larsen

#include <iostream>
#include <string>

using namespace std;

int roman_to_decimal(const string& roman_value)
{
    int decimal_value = 0;
    for (size_t i = 0; i < roman_value.length(); ++i)
    {
        if (roman_value[i] == 'I')
        {
            if (i + 1 < roman_value.length() && (roman_value[i + 1] == 'V' || roman_value[i + 1] == 'X'))
            {
                decimal_value -= 1;
            }
            else
            {
                decimal_value += 1;
            }
        }
        else if (roman_value[i] == 'V')
        {
            decimal_value += 5;
        }
        else if (roman_value[i] == 'X')
        {
            if (i + 1 < roman_value.length() && (roman_value[i + 1] == 'L' || roman_value[i + 1] == 'C'))
            {
                decimal_value -= 10;
            }
            else
            {
                decimal_value += 10;
            }
        }
        else if (roman_value[i] == 'L')
        {
            decimal_value += 50;
        }
        else if (roman_value[i] == 'C')
        {
            if (i + 1 < roman_value.length() && (roman_value[i + 1] == 'D' || roman_value[i + 1] == 'M'))
            {
                decimal_value -= 100;
            }
            else
            {
                decimal_value += 100;
            }
        }
        else if (roman_value[i] == 'D')
        {
            decimal_value += 500;
        }
        else if (roman_value[i] == 'M')
        {
            decimal_value += 1000;
        }
    }
    return decimal_value;
}
