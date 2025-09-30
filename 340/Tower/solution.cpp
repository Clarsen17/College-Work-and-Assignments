// Collen Larsen z1930118 CSCI 340-3
// Lab Project 3 - Highest Hanoi Tower
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to build the tallest Hanoi Tower possible from a given set of disks
// Parameters:
// - v: A vector of pairs representing disks, where each pair consists of (radius, height)
// - height: Reference variable to store the maximum height of the tower
// - index: Reference variable to store the index of the top disk in the original input vector
void buildHanoiTower(const vector<pair<int, int>>& v, int& height, int& index) 
{
    int n = v.size();

    // Store original indices along with disk radius and height
    vector<pair<pair<int, int>, int>> sorted_v;
    for (int i = 0; i < n; i++) 
    {
        sorted_v.push_back({v[i], i}); // Pair of (radius, height) and its original index
    }

    // Sort disks in ascending order by radius, breaking ties by height
    sort(sorted_v.begin(), sorted_v.end(), [](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        return a.first.first < b.first.first || (a.first.first == b.first.first && a.first.second < b.first.second);
    });

    // dp[i] stores the maximum height attainable with the i-th disk as the topmost disk
    // top_index[i] stores the index of the disk that ends up on top of the tallest tower ending at i
    vector<int> dp(n), top_index(n);

    for (int i = 0; i < n; i++) 
    {
        dp[i] = sorted_v[i].first.second; // Base case: each disk can be a tower on its own
        top_index[i] = sorted_v[i].second;  // Store the original index of the disk
    }

    // Iterate through disks to find the optimal stacking order
    for (int i = 1; i < n; i++) 
    {
        for (int j = 0; j < i; j++) 
        {
            if (sorted_v[j].first.first < sorted_v[i].first.first && sorted_v[j].first.second < sorted_v[i].first.second) {
                if (dp[i] < dp[j] + sorted_v[i].first.second) 
                {
                    dp[i] = dp[j] + sorted_v[i].first.second;
                    top_index[i] = top_index[j];  // Keep track of the topmost disk index
                }
            }
        }
    }

    // Find the maximum possible height and the corresponding top disk index
    height = dp[0];
    index = top_index[0];

    for (int i = 1; i < n; i++) 
    {
        if (dp[i] > height) 
        {
            height = dp[i];
            index = top_index[i];  // Retrieve the original index
        }
    }
}
