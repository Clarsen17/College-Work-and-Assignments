//Collen Larsne z1930118 
//CSCI 340-1 340-assign-map - grids.h
#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include <iostream>
#include <fstream>
#include "grids.decl.h"

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the given x and y coordinates are within the grid bounds.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @return true if within bounds, false otherwise
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckxy(int x, int y) const {
  return (x >= 0 && x < _width && y >= 0 && y < _height);
}

/**
 * @brief Checks if the given row and column are within the grid bounds.
 * 
 * @param row Row index
 * @param col Column index
 * @return true if within bounds, false otherwise
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckrc(int row, int col) const {
  return boundscheckxy(col, row);
}

/**
 * @brief Checks if the grid is empty.
 * 
 * @return true if the grid is empty, false otherwise
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::empty() const {
  return _width == 0 || _height == 0;
}

/**
 * @brief Clears the grid, resetting its dimensions and content.
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T,RA_CONTAINER>::clear() {
  data.clear();
  _width = 0;
  _height = 0;
}

/**
 * @brief Returns a reference to the element at the specified x and y coordinates.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @return T& Reference to the element
 * @throws std::out_of_range if the coordinates are out of bounds
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) {
  if (!boundscheckxy(x, y)) throw std::out_of_range("Invalid index");
  return data[y * _width + x];
}

/**
 * @brief Returns a constant reference to the element at the specified x and y coordinates.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @return const T& Constant reference to the element
 * @throws std::out_of_range if the coordinates are out of bounds
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) const {
  if (!boundscheckxy(x, y)) throw std::out_of_range("Invalid index");
  return data[y * _width + x];
}

/**
 * @brief Returns a reference to the element at the specified row and column.
 * 
 * @param row Row index
 * @param col Column index
 * @return T& Reference to the element
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) {
  return atxy(col, row);
}

/**
 * @brief Returns a constant reference to the element at the specified row and column.
 * 
 * @param row Row index
 * @param col Column index
 * @return const T& Constant reference to the element
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) const {
  return atxy(col, row);
}

/**
 * @brief Returns the width of the grid.
 * 
 * @return int Width of the grid
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::width() const {
  return _width;
}

/**
 * @brief Returns the height of the grid.
 * 
 * @return int Height of the grid
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::height() const {
  return _height;
}

/**
 * @brief Assigns the contents of another grid (regardless of backing container) to this grid.
 * 
 * @param source Source grid to copy from
 * @return grid_row_major<T, RA_CONTAINER>& Reference to the updated grid
 */
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major <T, RA_CONTAINER> & grid_row_major<T, RA_CONTAINER>::operator=(const grid_row_major<T, OTHER_CONTAINER> &source) {
  if (this != &source) {
    data = RA_CONTAINER(source.begin(), source.end());
    _width = source.width();
    _height = source.height();
  }
  return *this;
}

/**
 * @brief Returns an iterator to the beginning of the specified row.
 * 
 * @param row The row index
 * @return auto Iterator to the beginning of the row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) {
  return data.begin() + row * _width;
}

/**
 * @brief Returns an iterator to the end of the specified row.
 * 
 * @param row The row index
 * @return auto Iterator to the end of the row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) {
  return data.begin() + (row + 1) * _width;
}

/**
 * @brief Returns a constant iterator to the beginning of the specified row.
 * 
 * @param row The row index
 * @return auto Constant iterator to the beginning of the row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) const {
  return data.begin() + row * _width;
}

/**
 * @brief Returns a constant iterator to the end of the specified row.
 * 
 * @param row The row index
 * @return auto Constant iterator to the end of the row
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) const {
  return data.begin() + (row + 1) * _width;
}

/**
 * @brief Returns a column iterator to the beginning of the specified column.
 * 
 * @param col Column index
 * @return auto Column iterator to the beginning of the column
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) {
  return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col, _width);
}

/**
 * @brief Returns a column iterator to the end of the specified column.
 * 
 * @param col Column index
 * @return auto Column iterator to the end of the column
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col) {
  return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col + _width * _height, _width);
}

/**
 * @brief Resizes the grid to new dimensions and copies over existing data.
 * 
 * @param new_width New width of the grid
 * @param new_height New height of the grid
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {
  RA_CONTAINER new_data(new_width * new_height);
  int min_width = std::min(new_width, _width);
  int min_height = std::min(new_height, _height);
  for (int y = 0; y < min_height; ++y) {
    for (int x = 0; x < min_width; ++x) {
      new_data[y * new_width + x] = data[y * _width + x];
    }
  }
  data.swap(new_data);
  _width = new_width;
  _height = new_height;
}

/**
 * @brief Loads grid data from a file.
 * 
 * @param filename The name of the file containing grid data
 * @return true if the file was successfully loaded, false otherwise
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::load_from_file(const std::string & filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return false;
  }
  
  int width, height;
  file >> width >> height;
  if (width != 9 || height != 9) {
    std::cerr << "Error: Invalid grid dimensions. Expected 9x9." << std::endl;
    return false;
  }

  resize(width, height);
  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      int value;
      file >> value;
      if (value >= 1 && value <= 9) {
        set_sudoku_cell_known(*this, row, col, value);
      } else {
        set_sudoku_cell_unknown(*this, row, col);
      }
    }
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) {
  // XXX This function has not been implemented yet.
  return false; // report that it's not working, because it's not implemented yet
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//
////////////////////////////////////////////////////////////////////////////////

template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator ++ () { // preincrement
  // XXX This is not yet implemented
}

template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator ++ (int) { // postincrement
  // XXX This is not yet implemented
}
    
template <typename ITERATOR>
col_iterator <ITERATOR> col_iterator<ITERATOR>::operator + (int n) const {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
auto & col_iterator <ITERATOR>::operator [] (int n) {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
const auto & col_iterator <ITERATOR>::operator [] (int n) const {
  // XXX This is not yet implemented
}
    
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator * () {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
const auto & col_iterator<ITERATOR>::operator * () const {
  // XXX This is not yet implemented
}

template <typename ITERATOR>
bool col_iterator <ITERATOR>::operator == (const col_iterator <ITERATOR> &other) {
  // XXX This is not yet implemented
}

#endif

