//Collen Larsen z1930118
//CSCI 340-3 
//Time Travel
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int mintimesteps(int a[], int len, int n) 
{
    if (n <= 0) return 0;
    
    int steps = 0;
    int maxReach = 0;
    int lastJump = 0;
    
    for (int i = 0; i < len; ++i) 
	{
        if (i > maxReach) return -1; // If we reach an unreachable position, return -1
        
        maxReach = max(maxReach, i + a[i]);
        
        if (maxReach >= n) return steps + 1; // If we can reach or exceed n, return the count
        
        if (i == lastJump) 
		{ // We used up the current jump, increase step count
            lastJump = maxReach;
            steps++;
        }
    }
    
    return -1;
}
