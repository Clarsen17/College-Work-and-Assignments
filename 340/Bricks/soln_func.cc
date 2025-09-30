//Collen Larsen z1930118 CSCI 340-3
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

bool isFeasible(int maxTime, int b, const vector<int>& heights) 
{
    int currentSum = 0, workersUsed = 1;
    for (int height : heights) 
	{
        if (currentSum + height > maxTime) 
		{
            workersUsed++;
            currentSum = height;
            if (workersUsed > b)
			 {
                return false;
            }
        } else
		 {
            currentSum += height;
        }
    }
    return true;
}

int bricklayers(int b, int a[], int len) 
{
    // Edge cases
    if (b <= 0 || len <= 0) return -1;
    for (int i = 0; i < len; ++i) 
	{
        if (a[i] <= 0) return -1;
    }
    
    vector<int> heights(a, a + len);
    
    // Binary search range
    int low = *max_element(heights.begin(), heights.end()); // Minimum time is the height of the tallest wall
    int high = accumulate(heights.begin(), heights.end(), 0); // Maximum time is building all walls by one bricklayer
    
    int result = high;
    
    while (low <= high) 
	{
        int mid = low + (high - low) / 2;
        
        if (isFeasible(mid, b, heights)) 
		{
            result = mid;
            high = mid - 1;
        } else 
		{
            low = mid + 1;
        }
    }
    
    return result;
}
