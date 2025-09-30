#include <iostream>

using namespace std;

void heapify(int array[], int n);
void sift_down(int array[], int start, int end);

void heap_sort(int array[], int n) 
{
    // Build the heap
    heapify(array, n);

    // Sorting the heap
    int end = n - 1;
    while (end > 0) 
	{
        // Swap the root (maximum value) with the last element
        swap(array[end], array[0]);
        // Reduce the heap size
        end--;
        // Restore heap property
        sift_down(array, 0, end);
    }
}

void heapify(int array[], int n) 
{
    int start = (n - 2) / 2; // Find parent of last element of array
    while (start >= 0) 
	{
        sift_down(array, start, n + 1);
        start--;
    }
}

void sift_down(int array[], int start, int end) 
{
    int root = start;
    while (2 * root + 1 <= end) 
	{
        int child = 2 * root + 1; // Left child of root
        int largest = root;       // Assume root is largest

        // If left child is larger than root, left child is largest
        if (array[largest] < array[child])
            largest = child;

    
        if (child + 1 <= end && array[largest] < array[child + 1])
            largest = child + 1;

    
        if (largest == root)
            return;
        else {
            swap(array[root], array[largest]);
            root = largest;
        }
    }
}
