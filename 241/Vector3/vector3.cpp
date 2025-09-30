//Collen Larsen z1930118

#include "vector3.h"
#include <iostream>

using namespace std;

// Constructor
vector3::vector3(double x_val, double y_val, double z_val) : x(x_val), y(y_val), z(z_val) {}

// Overloaded output operator
ostream& operator<<(std::ostream& os, const vector3& obj) {
    os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
    return os;
}

// Overloaded addition operator
vector3 vector3::operator+(const vector3& other) const {
    return vector3(x + other.x, y + other.y, z + other.z);
}

// Overloaded subtraction operator
vector3 vector3::operator-(const vector3& other) const {
    return vector3(x - other.x, y - other.y, z - other.z);
}

// Overloaded scalar product operator
double vector3::operator*(const vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Overloaded scalar multiplication operator (vector * scalar)
vector3 vector3::operator*(double scalar) const {
    return vector3(x * scalar, y * scalar, z * scalar);
}

// Overloaded subscript operator for const objects
double vector3::operator[](size_t pos) const {
    if (pos == 0) return x;
    else if (pos == 1) return y;
    else if (pos == 2) return z;
    // Undefined behavior for other positions
    return 0.0;
}

// Overloaded subscript operator for non-const objects
double& vector3::operator[](size_t pos) {
    if (pos == 0) return x;
    else if (pos == 1) return y;
    else if (pos == 2) return z;
    // Undefined behavior for other positions
    static double dummy; // Return a dummy variable to avoid compiler warnings
    return dummy;
}

// Overloaded equality operator
bool vector3::operator==(const vector3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

// Overloaded scalar multiplication operator (scalar * vector)
vector3 operator*(double scalar, const vector3& vec) {
    return vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

