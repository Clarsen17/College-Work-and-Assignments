/************************************************************************************
 * NIU CSCI 340 Section 1
 * Assignment # 1
 * Collen Larsen - Z1930118
 * 
 * I certify that everything I am submitting is either provided by the professor for use in
 * the assignment, or work done by me personally. I understand that if I am caught submitting
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic
 * Misconduct and will be punished as such.
 * 
 * This program generates random integers, stores them in a vector, then copies them into
 * another vector in reverse order, and prints both vectors with formatted output.
 ************************************************************************************/
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

// Generates random numbers and stores them in the vector v
void gen_rnd_nums(vector<int>& v, int seed, int range_limit, int vec_size) 
{
    // Clears the vector to remove any existing contents
    v.clear();

    // Seed the random number generator
    srand(seed);

    // Generates vec_size random numbers and push them to the vector
    for (int i = 0; i < vec_size; i++) 
	{
        // Generates a random number in the range 1, range_limit
        int random_num = (rand() % range_limit) + 1;
        v.push_back(random_num);
    }
}

//Copies the contents of v1 into v2 in reverse order.
int reverse_copy(vector<int>& v1, vector<int>& v2) 
{
    // Checks if the sizes match
    if (v1.size() != v2.size()) 
	{
        return -1;
    }

    // Copies elements from v1 to v2 in reverse order
    int size = v1.size();
    for (int i = 0; i < size; i++) 
	{
		//Changed, because I'm a idiot and put "+" istead of "-"
        v2[i] = v1[size - i - 1];
    }

    return 0;
}

//Prints the contents of a vector to stdout.
void print_vec(const vector<int>& v, int items_per_row, int item_width) 
{
    int count = 0;

	//prints new line for formating
	cout << endl;
	
    for (int num : v) 
	{
        // Prints each number with specified width
        cout << setw(item_width) << num;

        // Moves to a new line after items_per_row items
        count++;
        if (count % items_per_row == 0) 
		{
            cout << endl;
        }
    }

    // If the last row didn't fill up, will print newline
    if (count % items_per_row != 0) 
	{
        cout << endl;
    }
}

