//***************************************************************************
//
//  Collen Larsen
//  Z1930118
//  CSCI 340-1
//  Assignment 4: Defines the grid_row_major class and its methods
//
//***************************************************************************
#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iterator>

////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major class definition and method implementations
//
////////////////////////////////////////////////////////////////////////////////


// Class to manage a grid in row-major order
template <typename T, typename RA_CONTAINER = std::vector<T>>
class grid_row_major {
public:
    using value_type = T;

    // Constructors
    grid_row_major() : _width(0), _height(0), data() {}
    grid_row_major(int width, int height) : _width(width), _height(height), data(width * height) {}

    template<typename InputIt>
    grid_row_major(int width, int height, InputIt begin, InputIt end)
        : _width(width), _height(height), data(width * height) {
        auto it = begin;
        for (int i = 0; i < _width * _height && it != end; ++i, ++it) {
            data[i] = *it;
        }
    }

    // Copy constructor
    grid_row_major(const grid_row_major &other)
        : _width(other._width), _height(other._height), data(other.data) {}

    // Move constructor
    grid_row_major(grid_row_major &&other) noexcept
        : _width(other._width), _height(other._height), data(std::move(other.data)) {
        other._width = 0;
        other._height = 0;
    }

    // Assignment operator
    grid_row_major &operator=(const grid_row_major &other) {
        if (this != &other) {
            _width = other._width;
            _height = other._height;
            data = other.data;
        }
        return *this;
    }

    // Move assignment operator
    grid_row_major &operator=(grid_row_major &&other) noexcept {
        if (this != &other) {
            _width = other._width;
            _height = other._height;
            data = std::move(other.data);
            other._width = 0;
            other._height = 0;
        }
        return *this;
    }

    // Bounds checking
    bool boundscheckxy(int x, int y) const;
    bool boundscheckrc(int row, int col) const;

    // Element access
    T & atxy(int x, int y);
    const T & atxy(int x, int y) const;
    T & atrc(int row, int col);
    const T & atrc(int row, int col) const;

    // Utility methods
    int width() const;
    int height() const;
    bool empty() const;
    void clear();
    void resize(int new_width, int new_height);
    bool load_from_file(const std::string & filename);

    // Row iterators
    auto rowbegin(int row) { return data.begin() + row * _width; }
    auto rowend(int row) { return data.begin() + (row + 1) * _width; }
    auto rowbegin(int row) const { return data.cbegin() + row * _width; }
    auto rowend(int row) const { return data.cbegin() + (row + 1) * _width; }

    // Column iterators
    auto colbegin(int col);
    auto colend(int col);
    auto colbegin(int col) const;
    auto colend(int col) const;

private:
    int _width;
    int _height;
    RA_CONTAINER data;
};

// Bounds checking for (x, y) coordinates
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckxy(int x, int y) const 
{
    return (x >= 0 && x < _width && y >= 0 && y < _height);
}

// Bounds checking for (row, column) coordinates
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckrc(int row, int col) const
 {
    return (row >= 0 && row < _height && col >= 0 && col < _width);
}

// Checks if the grid is empty
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::empty() const 
{
    return data.empty();
}

// Clear the grid data
template <typename T, typename RA_CONTAINER>
void grid_row_major<T,RA_CONTAINER>::clear() 
{
    data.clear();
    _width = 0;
    _height = 0;
}

// Access element at (x, y) coordinates with bounds check
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y)
 {
    if (!boundscheckxy(x, y)) 
	{
        throw std::out_of_range("Coordinates out of bounds");
    }
    return data[y * _width + x];
}

// Const access to element at (x, y) coordinates with bounds check
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) const 
{
    if (!boundscheckxy(x, y)) 
	{
        throw std::out_of_range("Coordinates out of bounds");
    }
    return data[y * _width + x];
}

// Access element at (row, column) coordinates with bounds check
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) 
{
    if (!boundscheckrc(row, col)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    return data[row * _width + col];
}

// Const access to element at (row, column) coordinates with bounds check
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) const 
{
    if (!boundscheckrc(row, col)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    return data[row * _width + col];
}

// Return the width of the grid
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::width() const 
{
    return _width;
}

// Return the height of the grid
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::height() const 
{
    return _height;
}

template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) 
{
    data.resize(new_width * new_height);
    _width = new_width;
    _height = new_height;
}

// Resize the grid to a new width and height
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::load_from_file(const std::string & filename)
 {
    std::ifstream infile(filename);
    if (!infile.is_open()) 
	{
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    int width, height;
    infile >> width >> height;
    if (!infile) 
	{
        std::cerr << "Error reading dimensions from file." << std::endl;
        return false;
    }

    resize(width, height);
    for (int i = 0; i < width * height; ++i) 
	{
        if (!(infile >> data[i])) {
            std::cerr << "Error reading grid data from file." << std::endl;
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////


/**
 * @brief Multiplies two grids (matrices) and stores the result in the third grid.
 * @param lhs The left-hand side matrix.
 * @param rhs The right-hand side matrix.
 * @param result The grid to store the result of the multiplication.
 * @return True if multiplication is possible, otherwise false.
 */
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) 
{
    if (lhs.width() != rhs.height()) 
	{
        return false;
    }

    result.resize(rhs.width(), lhs.height());

    for (int i = 0; i < lhs.height(); ++i)
	 {
        for (int j = 0; j < rhs.width(); ++j) 
		{
            typename GRID3::value_type sum = 0;
            for (int k = 0; k < lhs.width(); ++k) 
			{
                sum += lhs.atrc(i, k) * rhs.atrc(k, j);
            }
            result.atrc(i, j) = sum;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pre-increments the column iterator (moves to the next element in the column).
 */
template <typename ITERATOR>
class col_iterator {
public:
    col_iterator(ITERATOR iter, int grid_width) : it(iter), width(grid_width) {}

    // Pre-increment
    col_iterator & operator ++ () 
	{
        it += width;
        return *this;
    }

    // Post-increment
    col_iterator operator ++ (int) 
	{
        col_iterator temp = *this;
        it += width;
        return temp;
    }
    
    // Addition operator
    col_iterator operator + (int n) const 
	{
        return col_iterator(it + n * width, width);
    }

    // Subscript operator
    auto & operator [] (int n) 
	{
        return *(it + n * width);
    }

    const auto & operator [] (int n) const 
	{
        return *(it + n * width);
    }
    
    // Dereference operator
    auto & operator * () {
        return *it;
    }

    const auto & operator * () const 
	{
        return *it;
    }

    // Equality operator
    bool operator == (const col_iterator &other) const
	 {
        return it == other.it;
    }

    bool operator != (const col_iterator &other) const 
	{
        return it != other.it;
    }

private:
    ITERATOR it;
    int width;
};

////////////////////////////////////////////////////////////////////////////////
//
// Implement column begin and end for grid_row_major
//
////////////////////////////////////////////////////////////////////////////////

// Return the column iterator for the beginning of a column
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) 
{
    return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col, _width);
}

// Return the column iterator for the end of a column
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col)
 {
    return col_iterator<typename RA_CONTAINER::iterator>(data.begin() + col + _width * _height, _width);
}

// Const column iterators
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) const
 {
    return col_iterator<typename RA_CONTAINER::const_iterator>(data.cbegin() + col, _width);
}

template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col) const 
{
    return col_iterator<typename RA_CONTAINER::const_iterator>(data.cbegin() + col + _width * _height, _width);
}

#endif // NIU_CSCI_340_GRIDS_IMPL_H

