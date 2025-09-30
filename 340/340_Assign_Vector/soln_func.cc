//Collen Larsen Z1930118
//CSCI 340-1
//Histogram Daily
#include <iostream>
#include <vector>

int histogram(int a[], int len) 
{
    // Check if the array is NULL or length is 0
    if (a == nullptr || len <= 0) 
	{
        return 0;
    }

    std::vector<int> uniqueValues; // To store unique values in the order of first occurrence
    std::vector<int> frequencies;  // To store corresponding frequencies

    // Iterate over the array
    for (int i = 0; i < len; i++) 
	{
        int value = a[i];
        bool found = false;

        // Check if the value already exists in uniqueValues
        for (int j = 0; j < uniqueValues.size(); j++) 
		{
            if (uniqueValues[j] == value) 
			{
                frequencies[j]++;  // Increment frequency if value is found
                found = true;
                break;
            }
        }

        // If value is not found in uniqueValues, add it and set its frequency to 1
        if (!found) 
		{
            uniqueValues.push_back(value);
            frequencies.push_back(1);
        }
    }

    // Print the results in the order of first occurrence
    for (int i = 0; i < uniqueValues.size(); i++) 
	{
        std::cout << uniqueValues[i] << " occurs " << frequencies[i] << " time(s)." << std::endl;
    }

    return 1;
}

int main() 
{
    // Test cases
    int a1[] = {7, -11, 7};
    int len1 = 3;
    histogram(a1, len1); // Output: 7 occurs 2 time(s), -11 occurs 1 time(s)

    int a2[] = {5};
    int len2 = 1;
    histogram(a2, len2); // Output: 5 occurs 1 time(s)

    int a3[] = {12, -4, 19, 5, 19, 6, 5, -4, -4, 7};
    int len3 = 10;
    histogram(a3, len3); // Output: 12 occurs 1 time(s), -4 occurs 3 time(s), ...

    return 0;
}

