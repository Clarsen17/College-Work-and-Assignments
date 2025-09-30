//Collen Larsen Z1930118
#include <iostream>
#include <vector>

using namespace std;

// Returns the value of the last integer remaining out of the set of integers
int last_int_standing(size_t n, size_t step) 
{
    if (n == 0 || step == 0) return -1;

    vector<int> nums(n);
    for (size_t i = 0; i < n; i++) 
	{
        nums[i] = i + 1;
    }

    int idx = 0;
    while (nums.size() > 1) 
	{
        idx = (idx + step - 1) % nums.size();
        nums.erase(nums.begin() + idx);
    }

    return nums[0];
}

