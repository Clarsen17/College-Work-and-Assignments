//Collen Larsen z1930118
#include <iostream>
#include <string>

using namespace std;

//Function to check if a number is a step number
bool isStepNumber(int num) 
{
    string numStr = to_string(num);
    for (size_t i = 0; i < numStr.size() - 1; ++i) 
	{
        if (numStr[i] - '0' != numStr[i + 1] - '0' + 1 && numStr[i] - '0' != numStr[i + 1] - '0' - 1) 
		{
            return false;
        }
    }
    return true;
}

int max_stepnum(int n) 
{
    //Handle negative input
    bool isNegative = n < 0;
    if (isNegative) 
	{
        n = -n;
    }

    //Find the largest step number less than or equal to n
    for (int i = n; i >= 0; --i) 
	{
        if (isStepNumber(i)) 
		{
            return isNegative ? -i : i;
        }
    }

    return -1;
}
