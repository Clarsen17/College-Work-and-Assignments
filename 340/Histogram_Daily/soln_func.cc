//Collen Larsen z1930118
// CSCI 340-3
//Redone again what I read online was a lie
#include <iostream>

using namespace std;

int histogram(int a[], int len) 
{
    if (a == nullptr || len <= 0) 
	{
        return 0;
    }

    int* uniqueValues = new int[len];   // Dynamically allocate memory for unique values
    int* frequency = new int[len];      // Dynamically allocate memory for frequency of each unique value
    int uniqueCount = 0;                // Counter for the number of unique values

    for (int i = 0; i < len; i++) 
	{
        bool found = false;

        // Check if the value already exists in uniqueValues
        for (int j = 0; j < uniqueCount; j++) 
		{
        	
            if (uniqueValues[j] == a[i]) 
			{
                frequency[j]++;  // If found, increment its frequency
                found = true;
                break;
            }
        }

        // If the value is not found, add it to uniqueValues
        if (!found) 
		{
            uniqueValues[uniqueCount] = a[i];
            frequency[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // Print the unique values and their frequencies in the order of first occurrence
    for (int i = 0; i < uniqueCount; i++) 
	{
        cout << uniqueValues[i] << " occurs " << frequency[i] << " time(s)." << std::endl;
    }

    // Free the dynamically allocated memory
    delete[] uniqueValues;
    delete[] frequency;

    return 1;
}
