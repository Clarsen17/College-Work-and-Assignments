//Collen Larsen z1930118
// CSCI 340-3
// Kight Attack
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Position
{
    int row, col, moves;
};

// Possible moves of a knight
const vector<pair<int, int>> moves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                                      {1, -2}, {1, 2}, {2, -1}, {2, 1}};

int captured(int knight_r, int knight_c, int pawn_r, int pawn_c) 
{
    if (knight_r == pawn_r && knight_c == pawn_c) return -1;
    
    vector<vector<bool>> visited(8, vector<bool>(8, false));
    queue<Position> q;
    
    q.push({knight_r, knight_c, 0});
    visited[knight_r][knight_c] = true;
    
    while (!q.empty()) {
        Position current = q.front();
        q.pop();
        
        if (current.row == pawn_r && current.col == pawn_c) 
		{
            return current.moves;
        }
        
        for (auto move : moves) {
            int newRow = current.row + move.first;
            int newCol = current.col + move.second;
            
            if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                q.push({newRow, newCol, current.moves + 1});
            }
        }
    }
    
    return -1;
}

