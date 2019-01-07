//
// Created by burak on 1/3/19.
//

#include "Matrix.h"
#include <iostream>

// Empty constructor
Matrix::Matrix()
{
    m = 0;
    n = 0;
    Create();
    Fill();
}

// Constructor with parameters
Matrix::Matrix(int _m, int _n)
{
    m = _m;
    n = _n;
    Create();
    Fill();
}

// Copying constructor
Matrix::Matrix( const Matrix& copyMatrix )
{
    m = copyMatrix.m;
    n = copyMatrix.n;
    Create();
    Fill();
}

// Destructor
Matrix::~Matrix()
{
    delete(firstMatrix);
}

// Accessor functions
int Matrix::getCols()
{
    return n;
}

int Matrix::getRows()
{
    return m;
}

int Matrix::getValue(int x, int y)
{
    return firstMatrix[x][y];
}

int Matrix::setValue(double value, int x, int y)
{
    firstMatrix[x][y] = value;
}

// Operator functions

Matrix Matrix::operator+(const Matrix& matrix)
{
    Matrix secondMatrix(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            secondMatrix.firstMatrix[i][j] = firstMatrix[i][j] + matrix.firstMatrix[i][j];
        }
    }
    return secondMatrix;
}

Matrix Matrix::operator-(const Matrix& matrix)
{
    Matrix secondMatrix(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            secondMatrix.firstMatrix[i][j] = firstMatrix[i][j] - matrix.firstMatrix[i][j];
        }
    }
    return secondMatrix;
}

Matrix Matrix::operator*(const Matrix& matrix)
{
    Matrix secondMatrix(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            secondMatrix.firstMatrix[i][j] = firstMatrix[i][j] * matrix.firstMatrix[i][j];
        }
    }
    return secondMatrix;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
    Matrix secondMatrix(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            secondMatrix.firstMatrix[i][j] = matrix.firstMatrix[i][j];
        }
    }
    return secondMatrix;
}

Matrix Matrix::operator+=(const Matrix& matrix)const
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->firstMatrix[i][j] += matrix.firstMatrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator-=(const Matrix& matrix)const
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->firstMatrix[i][j] -= matrix.firstMatrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*=(const Matrix& matrix)const
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->firstMatrix[i][j] *= matrix.firstMatrix[i][j];
        }
    }
    return *this;
}



bool Matrix::operator==(const Matrix& matrix)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (this->firstMatrix[i][j] != matrix.firstMatrix[i][j])
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }

}

Matrix Matrix::operator^(const double num)
{
    Matrix secondMatrix(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->firstMatrix[i][j] = firstMatrix[i][j] * num;
        }
    }
    return *this;
}

Matrix Matrix::operator!()
{
    Matrix secondMatrix(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->firstMatrix[j][i] = firstMatrix[i][j];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (int i = 0; i < matrix.m; i++)
    {
        for (int j = 0; j < matrix.n; j++)
        {
            os << matrix.firstMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return os;
}

std::istream& operator>>(std::istream& ist, const Matrix& matrix)
{
    for (int i = 0; i < matrix.m; i++)
    {
        for (int j = 0; j < matrix.n; j++)
        {
            ist >> matrix.firstMatrix[i][j];
        }
    }
    return ist;
}

void Matrix::Create()
{
    firstMatrix = new double * [m];
    for (int i = 0; i < m; i++)
    {
        firstMatrix[i] = new double[n];
    }
}

void Matrix::Fill()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            firstMatrix[i][j] = (double)(rand() % 100);
        }
    }
}