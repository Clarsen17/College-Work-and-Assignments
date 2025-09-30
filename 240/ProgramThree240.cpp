/**************************************************************
CSCI 240         Program 3     Fall 2023

Programmer: Collen Larsen

Section:0001

Date Due: 9/22/23

Purpose: Calculate income tax
***************************************************************/
//if the current gross income is MORE than the diffrence (min-max) add the diffrence times tax rate to the income tax ammount
// deduct the diffrence from the current gross income if the current gross income is LESS than the diffrence
//add the current gross income times the tax rate, set the current gross income to 0

#include <iostream>
#include <iomanip>

using namespace std;

//Create constants that will be used for the tax rates
const double TAX_RATE1 = .10;
const double TAX_RATE2 = .12;
const double TAX_RATE3 = .22;
const double TAX_RATE4 = .24;

int main ()
{
//creates variables that will be used in the program
	double gross_income,income_tax;
	int tax_rate;
	
	
//asks user for the gross income
	cout << "What is your gross income? $";
	cin >> gross_income;
	
//decides what tax rate to use, then calculates
if (gross_income <= 11000)
    {
        income_tax = gross_income * TAX_RATE1;
    }
    else if (gross_income <= 44725)
    {
        income_tax = 11000 * TAX_RATE1 + (gross_income - 11000) * TAX_RATE2;
    }
    else if (gross_income <= 95375)
    {
        income_tax = 11000 * TAX_RATE1 + (44725 - 11000) * TAX_RATE2 + (gross_income - 44725) * TAX_RATE3;
    }
    else
    {
        income_tax = 11000 * TAX_RATE1 + (44725 - 11000) * TAX_RATE2 + (95375 - 44725) * TAX_RATE3 + (gross_income - 95375) * TAX_RATE4;
        cout << "Congrats, you're in the highest tax bracket!" << endl;
    }
	
	//displays the results, shows the user the gross income they input and the income tax calculated
	cout <<endl << fixed << setprecision(2) << "Your gross income: $" << gross_income << endl << "Your income tax: $" << income_tax << endl;
	
	return 0;
}
