// Collen Larsen z1930118 
// CSCI 340-3
#include <iostream>

int howmuchwater(unsigned int a[], int n) 
{
    // Basic error check
    if (n <= 0 || a == nullptr) 
	{
        return -1; 
    }

    int left = 0, right = n - 1;
    int left_max = 0, right_max = 0;
    int water_trapped = 0;

    // Two-pointer approach
    while (left < right) 
	{
        if (a[left] < a[right]) 
		{
            if (static_cast<int>(a[left]) >= left_max) 
			{
                left_max = a[left];
            } else 
			{
                water_trapped += (left_max - a[left]);
            }
            ++left;
        } else 
		{
            if (static_cast<int>(a[right]) >= right_max) 
			{
                right_max = a[right];
            } else 
			{
                water_trapped += (right_max - a[right]);
            }
            --right;
        }
    }

    return water_trapped;
}
