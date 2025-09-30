/***************************************************************
CSCI 240         Program 7     Fall 2023

Programmer: Collen Larsen

Section:0001

Date Due: 9/29/23

Purpose: Display Stardew Crops
***************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>


using namespace std;

int main()
{
ifstream infile;

infile.open( "crops.txt" );

if ( infile.fail())
{
	cout << "something went wrong" <<endl;
	
	exit (-1);
}

//"   Season       Crop Name       Seed Cost      Sell Value    Harvest Time Gold Profit/Day"
cout << "Season " << setw(10) << "Crop Name " << setw(8) << "Seed Cost " << setw(8) <<"Harvest Time " << setw(8) << "Gold Profit/Day" <<endl;
cout <<"------------------------------------------------------------------------------------------------" <<endl;

string name; 
int season, crop, seed_cost, sell_value, harvest_time;

infile >> name; 
	
while ( infile )
{
	infile >> season;
	infile >> crop;
	infile >> seed_cost;
	infile >> sell_value;
	infile >> harvest_time;
	
	cout << name << setw(6) << season << setw(6) << crop << setw(6) 
	<< seed_cost << setw(6) << sell_value << setw(6) << harvest_time << endl; 
	
	infile >>name;
}

return 0;
}
