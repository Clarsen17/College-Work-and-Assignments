/***************************************************************
CSCI 240         Program 0     Fall 2023

Programmer: Collen Larsen

Section:0001

Date Due: 9/15/23

Purpose: Calculate a powerlifter's total
***************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;

//Creats constants
const double WILKS = 0.5976;
const double LEFT_COLUMN = 20;
const double RIGHT_COLUMN = 8;

int main ()
{
	//Creat variables
	int squat_value, press_value, deadlift_value;
	float powerlift_value, wilks_value; 
	
	//Get values from the user
	cout << "What is your max squat? ";
	cin >> squat_value;
	cout << "What is you max bench press? ";
	cin >> press_value;
	cout << "What is your max deadlift? ";
	cin >> deadlift_value;
	
	//Calculates the users total and wilks score
	powerlift_value = squat_value + press_value + deadlift_value;
	wilks_value = powerlift_value * 0.5976;
	
	//Display table of results
	cout << endl << endl
		<< left << setw(LEFT_COLUMN)	<< "Max Squat: "<< right << setw(RIGHT_COLUMN) << squat_value << endl
		<< left << setw(LEFT_COLUMN)	<< "Max Bench Press: "<< right << setw(RIGHT_COLUMN) << press_value << endl
		<< left << setw(LEFT_COLUMN)	<< "Max Deadlift: "<< right << setw(RIGHT_COLUMN) << deadlift_value << endl << endl
		<< left << setw(LEFT_COLUMN)	<< "Powerlifting Total: "<< right << setw(RIGHT_COLUMN) << powerlift_value << endl
		<< setprecision(3) <<fixed
		<< left << setw(LEFT_COLUMN)	<< "Wilks Score: "<< right << setw(RIGHT_COLUMN) << wilks_value << endl
		<< endl;
	
	return 0;
}

