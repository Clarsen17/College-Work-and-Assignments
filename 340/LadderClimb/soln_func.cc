// Collen Larsen Z1930118
// CSCI 340-3 2/14/25
#include <iostream>

int nclimbs(int n) 
{
    if (n < 1) return -1; // Invalid input check

    // Base cases
    constexpr int base_cases[] = {1, 2, 4}; // For n = 1, 2, 3 respectively
    if (n <= 3) return base_cases[n - 1];

    // Optimized iterative approach (O(1) space)
    int a = 1, b = 2, c = 4, result = 0;

    for (int i = 4; i <= n; ++i) 
	{
        result = a + b + c; // Recurrence relation
        a = b;
        b = c;
        c = result;
    }

    return result;
}
