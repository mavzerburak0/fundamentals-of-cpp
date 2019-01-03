#include <iostream>

// Simple swap function to do the swapping
// until the array is sorted
void swap(int & a, int & b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Bubble sort implementation
int * Bubble(int const arr_len, int * first_array)
{
    int i;
    int * sorted_array = new int[arr_len];
    // Boolean value to check if the values in the array are already swapped or not
    bool swapped = true;
    // For loop to fill in sorted_array with the random values in first_array
    for (i = 0; i < arr_len; i++)
    {
        sorted_array[i] = first_array[i];
    }
    while (swapped)
    {
        swapped = false;
        // For loop to do the swapping
        for (i = 1; i < arr_len; i++)
        {
            if (sorted_array[i] < sorted_array[i - 1])
            {
                swap(sorted_array[i], sorted_array[i - 1]);
                swapped = true;
            }
            else
            {
                continue;
            }
        }
    }
    // Printing the sorted_array
    for (i = 0; i < arr_len; i++)
    {
        std::cout << sorted_array[i] << std::endl;
    }
    // Function returns sorted_array
    return sorted_array;
}