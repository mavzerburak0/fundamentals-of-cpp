#include <iostream>
#include <time.h>
#include "bubble-func.h"


// Creates an array of a length given by the user
// Fills the array with pseudo-random integers up to 1000
// Sorts the array with a bubble sorting algorithm
// Prints both the first and the sorted array


int main()
{
    // Array length declaration (user-input)
    int leng_arr;
    int * int_array;
    std::cout << "Enter the array length: " << std::endl;
    std::cin >> leng_arr;
    // Seed for random int generation
    srand(time(NULL));
    // Array initialization
    int_array = new int[leng_arr];
    // For loop to fill the array with random integers between 0-1000
    for (int i = 0; i < leng_arr; i++)
    {
        int_array[i] = rand() % 1000;
        std::cout << int_array[i] << std::endl;
    }
    std::cout << "" << std::endl;
    // Function call to bubble
    Bubble(leng_arr, int_array);
    return 0;
}