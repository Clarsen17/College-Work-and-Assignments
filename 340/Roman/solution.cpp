//Collen Larsen Z1930118
// CSCI 340-3 Lab 2/6/25
// Convert a decimal number into its Roman numeral representation

#include <string>
using namespace std;

string decimal_to_roman(int decimal_value) 
{
    // Separate arrays for each place: thousands, hundreds, tens, and ones
    const string roman_thousands[] = {"", "M", "MM", "MMM"};
    const string roman_hundreds[]  = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const string roman_tens[]      = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const string roman_ones[]      = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    // Calculate the indices for each position
    int thousands_index = decimal_value / 1000;
    int hundreds_index  = (decimal_value % 1000) / 100;
    int tens_index      = (decimal_value % 100) / 10;
    int ones_index      = decimal_value % 10;

    // Build the Roman numeral
    string roman_result = roman_thousands[thousands_index] 
                        + roman_hundreds[hundreds_index] 
                        + roman_tens[tens_index] 
                        + roman_ones[ones_index];

    return roman_result;
}
