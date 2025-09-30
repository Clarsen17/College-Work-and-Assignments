//Collen Larsne z1930118 
//CSCI 340-1 340-assign-map - sudoku.cc
#include "settings.h"
#include "sudoku.h"
#include <fstream>
#include <iostream>
#include <set>

/**
 * @brief Initializes the Sudoku grid to be 9x9 with all possibilities (1-9) in each cell.
 * 
 * @param grid The SUDOKUGRID to initialize.
 */
void initialize_grid(SUDOKUGRID &grid)
{
    grid.resize(9, 9);
    for (int row = 0; row < 9; ++row) 
	{
        for (int col = 0; col < 9; ++col) 
		{
            set_sudoku_cell_unknown(grid, row, col);
        }
    }
}

/**
 * @brief Marks a cell as known by setting its value and clearing all other possibilities.
 * 
 * @param grid The SUDOKUGRID to use.
 * @param row The row of the cell.
 * @param col The column of the cell.
 * @param solution The value to set as the known solution.
 */
void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) 
{
    grid.atrc(row, col).clear();
    grid.atrc(row, col).insert(solution);
}

/**
 * @brief Marks a cell as unknown by filling the set with all possible values (1-9).
 * 
 * @param grid The SUDOKUGRID to use.
 * @param row The row of the cell.
 * @param col The column of the cell.
 */
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col)
 {
    grid.atrc(row, col) = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

/**
 * @brief Removes a specific possibility from a cell.
 * 
 * @param grid The SUDOKUGRID to use.
 * @param row The row of the cell.
 * @param col The column of the cell.
 * @param value The value to remove from the cell's possibilities.
 */
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) 
{
    grid.atrc(row, col).erase(value);
}

/**
 * @brief Handles all logic for a specific cell, applying Sudoku rules to rows, columns, and subgrids.
 * 
 * @param grid The SUDOKUGRID to use.
 * @param row The row of the cell.
 * @param col The column of the cell.
 * @return int The number of possibilities removed across rows, columns, and subgrids.
 */
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
    int count = 0;
    count += handle_row_for_cell(grid, row, col);
    count += handle_col_for_cell(grid, row, col);
    count += handle_subgrid_for_cell(grid, row, col);
    return count;
}

/**
 * @brief Removes the known value of a cell from all other cells in the same row.
 * 
 * @param grid The SUDOKUGRID to use.
 * @param row The row of the cell.
 * @param col The column of the cell.
 * @return int The number of possibilities removed.
 */
int handle_row_for_cell(SUDOKUGRID &grid, int row, int col) {
    const auto &cell = grid.atrc(row, col);
    if (cell.size() == 1) {
        int value = *cell.begin();
        int removed_count = 0;
        for (int c = 0; c < 9; ++c) 
		{
            if (c != col && grid.atrc(row, c).erase(value)) 
			{
                ++removed_count;
            }
        }
        return removed_count;
    }
    return 0;
}

/**
 * @brief Removes the known value of a cell from all other cells in the same column.
 * 
 * @param grid The SUDOKUGRID to use.
 * @param row The row of the cell.
 * @param col The column of the cell.
 * @return int The number of possibilities removed.
 */
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col) {
    const auto &cell = grid.atrc(row, col);
    if (cell.size() == 1) {
        int value = *cell.begin();
        int removed_count = 0;
        for (int r = 0; r < 9; ++r) 
		{
            if (r != row && grid.atrc(r, col).erase(value)) 
			{
                ++removed_count;
            }
        }
        return removed_count;
    }
    return 0;
}

/**
 * @brief Removes the known value of a cell from all other cells in the same 3x3 subgrid.
 * 
 * @param grid The SUDOKUGRID to use.
 * @param row The row of the cell.
 * @param col The column of the cell.
 * @return int The number of possibilities removed.
 */
int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col) {
    const auto &cell = grid.atrc(row, col);
    if (cell.size() == 1) {
        int value = *cell.begin();
        int removed_count = 0;

        // Determine the boundaries of the 3x3 subgrid
        int subgrid_row_start = (row / 3) * 3;
        int subgrid_col_start = (col / 3) * 3;

        for (int r = subgrid_row_start; r < subgrid_row_start + 3; ++r)
		 {
            for (int c = subgrid_col_start; c < subgrid_col_start + 3; c++) 
			{
                if (r != row || c != col) 
				{
                    if (grid.atrc(r, c).erase(value)) 
					{
                        ++removed_count;
                    }
                }
            }
        }
        return removed_count;
    }
    return 0;
}

/**
 * @brief Loads a Sudoku grid from a file.
 * 
 * @param filename The name of the file to load.
 * @param grid The SUDOKUGRID to populate.
 * @return true If the grid was successfully loaded, false otherwise.
 */
bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    int width, height;
    file >> width >> height;
    if (width != 9 || height != 9) 
	{
        std::cerr << "Error: Invalid grid dimensions. Expected 9x9." << std::endl;
        return false;
    }

    initialize_grid(grid);
    for (int row = 0; row < 9; ++row) 
	{
        for (int col = 0; col < 9; ++col) 
		{
            int value;
            file >> value;
            if (value >= 1 && value <= 9) 
			{
                set_sudoku_cell_known(grid, row, col, value);
            } else {
                set_sudoku_cell_unknown(grid, row, col);
            }
        }
    }

    return true;
}

/**
 * @brief Prints the Sudoku grid in a neatly formatted manner.
 * 
 * @param ost The output stream to print to.
 * @param grid The SUDOKUGRID to print.
 * @param unknown The character to print for unknown cells (default is space).
 * @param impossible The character to print for cells with no possibilities (default is 'x').
 */
void print_sudoku_grid(std::ostream &ost, const SUDOKUGRID &grid, char unknown, char impossible) {
    for (int row = 0; row < 9; ++row) 
	{
        if (row % 3 == 0 && row != 0) 
		{
            ost << "---------|---------|---------\n";
        }
        for (int col = 0; col < 9; ++col) 
		{
            if (col % 3 == 0 && col != 0) 
			{
                ost << "| ";
            }
            const auto &cell = grid.atrc(row, col);
            if (cell.empty()) {
                ost << impossible << " ";
            } else if (cell.size() == 1) 
			{
                ost << *cell.begin() << " ";
            } else {
                ost << unknown << " ";
            }
        }
        ost << "\n";
    }
}

