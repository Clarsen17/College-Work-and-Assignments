#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

/******************************************************************************
 * File: grids.h
 * Author: Collen Larsen
 * zID: z1930118
 * Course: CSCI 340-3
 * Date: 2/19/25
 * Assignment: Assignment 4
 *
 * Description:
 * This file implements the grid_row_major class
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "grids.decl.h"

////////////////////////////////////////////////////////////////////////////////
// grid_row_major method implementations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the given (x, y) coordinates are within grid bounds.
 * @tparam T The type of elements stored in the grid.
 * @tparam RA_CONTAINER The container type used for storing data.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return True if (x, y) is within bounds, false otherwise.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckxy(int x, int y) const 
{
    return x >= 0 && x < _width && y >= 0 && y < _height;
}

/**
 * @brief Checks if the given (row, col) coordinates are within grid bounds.
 * @tparam T The type of elements stored in the grid.
 * @tparam RA_CONTAINER The container type used for storing data.
 * @param row The row index.
 * @param col The column index.
 * @return True if (row, col) is within bounds, false otherwise.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::boundscheckrc(int row, int col) const 
{
    return row >= 0 && row < _height && col >= 0 && col < _width;
}

// Grid Status Methods

/**
 * @brief Checks if the grid is empty.
 * @return True if the grid has no elements, false otherwise.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::empty() const 
{
    return data.empty();
}

/**
 * @brief Clears all elements in the grid and resets its dimensions.
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::clear()
{
    data.clear();
    _width = 0;
    _height = 0;
}


// Accessor Methods
/**
 * @brief Accesses the element at the given (x, y) coordinates with bounds checking.
 * @return A reference to the element at (x, y).
 * @throws std::out_of_range if (x, y) is out of bounds.
 */
template <typename T, typename RA_CONTAINER>
T& grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) {
    if (!boundscheckxy(x, y)) {
        throw std::out_of_range("Invalid (x, y) coordinate");
    }
    return data[y * _width + x];
}

template <typename T, typename RA_CONTAINER>
const T& grid_row_major<T, RA_CONTAINER>::atxy(int x, int y) const {
    if (!boundscheckxy(x, y)) {
        throw std::out_of_range("Invalid (x, y) coordinate");
    }
    return data[y * _width + x];
}

template <typename T, typename RA_CONTAINER>
T& grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) {
    if (!boundscheckrc(row, col)) {
        throw std::out_of_range("Invalid (row, col) coordinate");
    }
    return data[row * _width + col];
}

template <typename T, typename RA_CONTAINER>
const T& grid_row_major<T, RA_CONTAINER>::atrc(int row, int col) const {
    if (!boundscheckrc(row, col)) {
        throw std::out_of_range("Invalid (row, col) coordinate");
    }
    return data[row * _width + col];
}

// Grid Size Methods

/**
 * @brief Returns the width of the grid.
 * @return The width of the grid.
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::width() const 
{
    return _width;
}

/**
 * @brief Returns the height of the grid.
 * @return The height of the grid.
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T, RA_CONTAINER>::height() const 
{
    return _height;
}

// Assignment Operator

/**
 * @brief Assigns the contents of another grid to this grid.
 * @tparam OTHER_CONTAINER The container type of the source grid.
 * @param source The grid to copy from.
 * @return A reference to the modified grid.
 */
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major<T, RA_CONTAINER>& grid_row_major<T, RA_CONTAINER>::operator=(
    const grid_row_major<T, OTHER_CONTAINER>& source) 
	{
    _width = source.width();
    _height = source.height();
    data.assign(source.begin(), source.end());
    return *this;
}

// Row Iterators
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) {
    return data.begin() + (row * _width);
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) {
    return data.begin() + ((row + 1) * _width);
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowbegin(int row) const {
    return data.cbegin() + (row * _width);
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::rowend(int row) const {
    return data.cbegin() + ((row + 1) * _width);
}

// Column Iterators
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colbegin(int col) {
    return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col, _width);
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T, RA_CONTAINER>::colend(int col) {
    return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + (_height * _width) + col, _width);
}

// Grid Resizing

/**
 * @brief Resizes the grid to new dimensions, discarding previous data.
 * @param new_width The new width of the grid.
 * @param new_height The new height of the grid.
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) 
{
    data.resize(new_width * new_height);
    _width = new_width;
    _height = new_height;
}

// Load Grid from File

/**
 * @brief Loads grid data from a file, replacing current contents.
 * @param filename The file to read from.
 * @return True if the file was successfully read, false otherwise.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T, RA_CONTAINER>::load_from_file(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filename << '\n';
        return false;
    }

    int new_width, new_height;
    file >> new_width >> new_height;
    if (!file) {
        std::cerr << "Error: Invalid file format\n";
        return false;
    }

    resize(new_width, new_height);
    for (int i = 0; i < new_width * new_height; ++i) {
        if (!(file >> data[i])) {
            std::cerr << "Error: Not enough data in file\n";
            return false;
        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
// Matrix Multiplication Implementation
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Performs matrix multiplication on two grids and stores the result.
 *
 * This function multiplies two matrices using the standard matrix multiplication
 * algorithm. The left-hand side (lhs) matrix must have the same number of columns
 * as the number of rows in the right-hand side (rhs) matrix. If the dimensions
 * do not match, the function returns false.
 *
 * @tparam GRID1 Type of the left-hand side matrix.
 * @tparam GRID2 Type of the right-hand side matrix.
 * @tparam GRID3 Type of the result matrix.
 * @param lhs The left-hand side matrix.
 * @param rhs The right-hand side matrix.
 * @param result The matrix where the multiplication result will be stored.
 * @return True if multiplication was successful, false otherwise.
 */
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3& result) {
    if (lhs.width() != rhs.height()) {
        return false;
    }

    // Resize result matrix to appropriate dimensions
    result.resize(rhs.width(), lhs.height());

    // Perform standard matrix multiplication
    for (int i = 0; i < lhs.height(); ++i) {
        for (int j = 0; j < rhs.width(); ++j) {
            double sum = 0.0;
            for (int k = 0; k < lhs.width(); ++k) {
                sum += lhs.atrc(i, k) * rhs.atrc(k, j);
            }
            result.atrc(i, j) = sum;
        }
    }
    return true;
}


////////////////////////////////////////////////////////////////////////////////
// Column Iterator Implementation
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pre-increment operator.
 * Moves the iterator to the next element in the column by incrementing
 * the position by the width of the grid.
 * @return Reference to the updated iterator.
 */
template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator++() { 
    pos += width;
    return *this;
}

/**
 * @brief Post-increment operator.
 * Moves the iterator to the next element in the column but returns
 * a copy of the iterator before the increment.
 * @return A copy of the iterator before incrementing.
 */
template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator++(int) { 
    col_iterator temp = *this;
    ++(*this);
    return temp;
}

/**
 * @brief Addition operator.
 * Returns a new iterator advanced by `n` positions in the column.
 * @param n The number of steps to advance.
 * @return A new iterator at the new position.
 */
template <typename ITERATOR>
col_iterator<ITERATOR> col_iterator<ITERATOR>::operator+(int n) const {
    return col_iterator(pos + (n * width), width);
}

/**
 * @brief Subscript operator.
 * Provides access to elements `n` positions ahead in the column.
 * @param n The offset in the column.
 * @return Reference to the element at position `n` steps ahead.
 */
template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator[](int n) {
    return *(pos + (n * width));
}

/**
 * @brief Const version of the subscript operator.
 * Provides read-only access to elements `n` positions ahead in the column.
 * @param n The offset in the column.
 * @return Const reference to the element at position `n` steps ahead.
 */
template <typename ITERATOR>
const auto& col_iterator<ITERATOR>::operator[](int n) const {
    return *(pos + (n * width));
}

/**
 * @brief Dereference operator.
 * Returns the value at the iterator's current position in the column.
 * @return Reference to the element at the iterator's position.
 */
template <typename ITERATOR>
auto& col_iterator<ITERATOR>::operator*() {
    return *pos;
}

/**
 * @brief Const version of the dereference operator.
 * Returns the value at the iterator's current position as a read-only reference.
 * @return Const reference to the element at the iterator's position.
 */
template <typename ITERATOR>
const auto& col_iterator<ITERATOR>::operator*() const {
    return *pos;
}

/**
 * @brief Equality comparison operator.
 * Checks if two column iterators point to the same position.
 * @param other The iterator to compare against.
 * @return True if both iterators point to the same position, false otherwise.
 */
template <typename ITERATOR>
bool col_iterator<ITERATOR>::operator==(const col_iterator<ITERATOR>& other) {
    return pos == other.pos;
}

#endif // NIU_CSCI_340_GRIDS_IMPL_H


