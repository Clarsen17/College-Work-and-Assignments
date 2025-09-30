#include <iostream>

bool windback(int a[], int b[], int len, int num_steps) 
{
    // Check for invalid input
    if (len < 1 || num_steps < 0)
        return false;

    // No need to do anything if num_steps is 0 or a single element array
    if (num_steps == 0 || len == 1) 
	{
        for (int i = 0; i < len; i++)
            b[i] = a[i];
        return true;
    }

    // Adjust num_steps if it's greater than array length
    num_steps %= len;

    // Copy the elements starting from (len - num_steps) position
    for (int i = 0; i < num_steps; i++)
    {
        b[i] = a[len - num_steps + i];
	} 
	
    // Copy the elements before (len - num_steps) position
    for (int i = 0; i < len - num_steps; i++)
    {
        b[num_steps + i] = a[i];
	}
    return true;
}

