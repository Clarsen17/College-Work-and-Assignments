#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int x_value, y_value;
	char letter, word;
	
	cout << "Enter a number (NO decimal point): ";
	cin >> x_value;
	cout << "Enter anouther number (NO decimal point): ";
	cin >> y_value;
	cout << "Enter a single character: ";
	cin >> letter;
	cout << "Enter a word: ";
	cin >> word;
	cout << endl;
	
	if (x_value > y_value)
	{
		cout << x_value << " is greater than " << y_value <<endl;
	}
	else if (x_value < y_value)
	{
		cout << x_value << " is less than " << y_value <<endl;
	}
	
	if (x_value >= y_value)
	{
		cout << x_value << " is greater than or equal to " << y_value <<endl;
	}
	else if (x_value <= y_value)
	{
		cout << x_value << " is less than or equal to " << y_value <<endl;
	}
	
	if (x_value = y_value)
	{
		cout << x_value << " is equal to " << y_value <<endl;
	}
	else if (x_value != y_value)
	{
		cout << x_value << " is not equal to " <<y_value <<endl;
	}
	
	return 0;
}
