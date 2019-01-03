//
// Created by burak on 1/3/19.
//

// Allocates memory space for a 2D array

#include <cstdlib>
#include <iostream>

double **Create(int n)
{
    double **NewMatrix = new double *[n];
    for (int i = 0; i < n; i++)
    {
        NewMatrix[i] = new double[n];
    }

    return NewMatrix;
}

void Fill(double **ppMatrix, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
            ppMatrix[i][j] = rand() % 1000;
    }
}

void Print(double **ppMatrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << ppMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Destroy(double **ppMatrix, int n)
{
    delete ppMatrix;
}

double **AddMatrices(double **ppMatrix1, double **ppMatrix2, int n)
{
    double **Addition = Create(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Addition[i][j] = ppMatrix1[i][j] + ppMatrix2[i][j];
        }
    }
    return Addition;
}

double **MultiplyMatrices(double **ppMatrix1, double **ppMatrix2, int n)
{
    double **Multiplication = Create(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Multiplication[i][j] = ppMatrix1[i][j] * ppMatrix2[i][j];
        }
    }
    return Multiplication;
}