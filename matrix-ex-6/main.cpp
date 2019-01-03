
#include <iostream>
#include <ctime>
#include "matrix-functions.h"

int main()
{

    int mat_size;
    // random seed generator put in main function because we want different
    // values in each matrix created
    srand((unsigned)time(0));
    std::cout << "Enter the matrix size" << std::endl;
    std::cin >> mat_size;
    std::cout << std::endl;
    double **Matrix = Create(mat_size);
    double **SecMatrix = Create(mat_size);
    Fill(Matrix, mat_size);
    Fill(SecMatrix, mat_size);
    Print(Matrix, mat_size);
    Print(SecMatrix, mat_size);
    double **addition_example = AddMatrices(Matrix, SecMatrix, mat_size);
    Print(addition_example, mat_size);
    double **multiplication_example = MultiplyMatrices(Matrix, SecMatrix, mat_size);
    Print(multiplication_example, mat_size);
    Destroy(Matrix, mat_size);
    Destroy(SecMatrix, mat_size);

    return 0;
}