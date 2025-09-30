//Collen Larsen Z1930118
// CSCI 340-1
// Convert a decimal to a roman num
#include <string>
using namespace std;

string decimal_to_roman(int decimal_value) 
{
    // Define Roman numeral equivalents for thousands, hundreds, tens, and ones
    string thousands[] = {"", "M", "MM", "MMM"};
    string hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    // Construct the Roman numeral string by extracting each place value
    string roman = thousands[decimal_value / 1000] +
                   hundreds[(decimal_value % 1000) / 100] +
                   tens[(decimal_value % 100) / 10] +
                   ones[decimal_value % 10];

    return roman;
}
