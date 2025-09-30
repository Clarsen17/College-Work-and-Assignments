//Collen Larsen z1930118
// CSCI 340-3
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool valid_sudoku(vector<vector<int>> &s) {
    // Check rows and columns
    for (int i = 0; i < 9; ++i) {
        unordered_set<int> row_set, col_set;
        for (int j = 0; j < 9; ++j) {
            int row_val = s[i][j];
            int col_val = s[j][i];
            
            // Check if the numbers are within the valid range
            if (row_val < 1 || row_val > 9 || col_val < 1 || col_val > 9) {
                return false;
            }

            // Check for duplicate in row
            if (row_set.find(row_val) != row_set.end()) {
                return false;
            }
            row_set.insert(row_val);

            // Check for duplicate in column
            if (col_set.find(col_val) != col_set.end()) {
                return false;
            }
            col_set.insert(col_val);
        }
    }

    // Check 3x3 subgrids
    for (int block_row = 0; block_row < 9; block_row += 3) {
        for (int block_col = 0; block_col < 9; block_col += 3) {
            unordered_set<int> block_set;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int val = s[block_row + i][block_col + j];
                    
                    if (block_set.find(val) != block_set.end()) {
                        return false;
                    }
                    block_set.insert(val);
                }
            }
        }
    }

    return true;
}


