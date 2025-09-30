// Collen Larsen Z1930118
// CSCI 340-3
#include <iostream>
#include <vector>

using namespace std;

vector<int> RotatingCornerSpiral(vector<vector<int>> &m) 
{
    int N = m.size();
    if (N == 0 || m[0].size() != N) return {}; // Return empty if not square

    vector<int> result;
    int layer = 0;
    while (layer < (N + 1) / 2)
	 {
        int size = N - 2 * layer;
        if (size <= 0) break;
        
        int r = layer, c = layer;
        for (int step = 0; step < size; ++step) 
		{
            result.push_back(m[r][c]);
            if (step < size - 1) c++; // Move right
        }
        for (int step = 0; step < size - 1; ++step) 
		{
            result.push_back(m[r][c]);
            if (step < size - 2) r++; // Move down
        }
        for (int step = 0; step < size - 1; ++step) 
		{
            result.push_back(m[r][c]);
            if (step < size - 2) c--; // Move left
        }
        for (int step = 0; step < size - 2; ++step) 
		{
            result.push_back(m[r][c]);
            r--; // Move up
        }
        layer++;
    }
    
    return result;
}
