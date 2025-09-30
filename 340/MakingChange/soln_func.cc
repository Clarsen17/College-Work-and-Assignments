//Collen Larsen Z1930118
// CSCI 340-3
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int mintokens(int c, int a[], int len) 
{
    if (c < 1 || len < 1) return -1;
    
    std::vector<int> dp(c + 1, INT_MAX);
    dp[0] = 0;
    
    for (int i = 1; i <= c; ++i) 
	{
        for (int j = 0; j < len; ++j) 
		{
            if (a[j] <= i && dp[i - a[j]] != INT_MAX) 
			{
                dp[i] = std::min(dp[i], dp[i - a[j]] + 1);
            }
        }
    }
    
    return dp[c] == INT_MAX ? -1 : dp[c];
}
