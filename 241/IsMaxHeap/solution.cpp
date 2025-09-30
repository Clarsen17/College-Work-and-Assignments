#include <iostream>

using namespace std;

// Function to check if the given array represents a max heap
bool is_max_heap(int a[], int n) 
{
    // Start from the first element and check to the last parent node
    for (int i = 0; i <= (n - 2) / 2; i++) 
	{
        // Get left child index
        int left = 2 * i + 1;
        // Get right child index
        int right = 2 * i + 2;

        // Checks if the current node is greater than its left child
        if (left < n && a[i] < a[left]) 
		{
            return false;
        }

        // Check sif the current node is greater than its right child
        if (right < n && a[i] < a[right])
		 {
            return false;
        }
    }

    // If all nodes satisfy the heap property, it's a max heap
    return true;
}
