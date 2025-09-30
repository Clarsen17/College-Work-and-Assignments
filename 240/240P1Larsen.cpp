/***************************************************************
CSCI 240         Program 0     Fall 2023

Programmer: Collen Larsen

Section:0001

Date Due:

Purpose: Triangle Area Calculator
***************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;

int main ()
{
	//Step one: Creat variables
	float  base_value, height_value, triangle_area; 
	
	//Step two: Get values from the user (base, height of triangle)
	cout << "Please Enter the Base of the Triangle: ";
	cin >> base_value;
	cout << "Please Enter the Height if the Triangle: ";
	cin >> height_value;
	
	//Step three: Calculate area of triangle
	triangle_area = 0.5 * base_value * height_value;
	//Step four: Display table of results
	cout << endl << endl
		<< "*********************" << endl
		<< "Area Calculator" << endl << endl
		<< "Base:        " << base_value << endl
		<< "Height:      " << height_value << endl << endl
		<< "Area:        " << triangle_area << endl
		<< "*********************" << endl;
	
	
	return 0;
}

