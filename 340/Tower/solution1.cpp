//Collen Larsen z1930118 CSCI 340-1 
//Lab Poject 3 - HighestHanoiTower
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Function to build the Tower
void buildHanoiTower(const vector<pair<int, int>>& v, int& height, int& index) 
{
    //Sorts disks by radius first, and then by their height
    vector<pair<int, int>> sorted_v = v;
    
    sort(sorted_v.begin(), sorted_v.end(), [](pair<int, int> a, pair<int, int> b) 
	{
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });

	//
    int n = sorted_v.size();
    vector<int> dp(n), top_index(n);
    
    for (int i = 0; i < n; i++) 
	{
        dp[i] = sorted_v[i].second;
        
        top_index[i] = i;
    }
    
    for (int i = 1; i < n; i++) // might work now?
	{
        for (int j = 0; j < i; j++) 
		{
            if (sorted_v[j].first < sorted_v[i].first && sorted_v[j].second < sorted_v[i].second) 
			{
                if (dp[i] < dp[j] + sorted_v[i].second) 
				{
                    dp[i] = dp[j] + sorted_v[i].second;
                    
                    top_index[i] = j;
                }
            }
        }
    }

    //Finds the maximum height
    height = dp[0];
    index = top_index[0];
    
    for (int i = 1; i < n; i++) 
	{
        if (dp[i] > height) 
		{
            height = dp[i];
            index = top_index[i];
        }
    }
}
//Sample main to test... 
int main() 
{
    int height = 0;
    int index = 0;
    vector<pair<int, int>> v = {{14, 13}, {11, 14}, {13, 12}};

    buildHanoiTower(v, height, index);

    cout << "Max height of the Hanoi Tower: " << height << endl;
    cout << "Top disk index: " << index << endl;

    return 0;
}

