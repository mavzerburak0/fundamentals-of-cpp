//
// Created by burak on 1/3/19.
//

#ifndef MATRIX_CLASS_CW_2_MATRIX_H
#define MATRIX_CLASS_CW_2_MATRIX_H


#include <cstdlib>
#include <iostream>


class Matrix {
private:
    int m, n;
    double **firstMatrix;
    void Create();
    void Fill();
public:
    Matrix();
    Matrix(int _m, int _n);
    Matrix( const Matrix& copyMatrix );
    ~Matrix();
    int getRows();
    int getCols();
    int getValue(int x, int y);
    int setValue(double value, int x, int y);
    Matrix operator+(const Matrix& matrix);
    Matrix operator-(const Matrix& matrix);
    Matrix operator*(const Matrix& matrix);
    Matrix& operator=(const Matrix& matrix);
    Matrix operator+=(const Matrix& matrix)const;
    Matrix operator-=(const Matrix& matrix)const;
    Matrix operator*=(const Matrix& matrix)const;
    bool operator==(const Matrix& matrix);
    Matrix operator^(const double num);
    Matrix operator!();
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& os, const Matrix& matrix);

};


#endif //MATRIX_CLASS_CW_2_MATRIX_H
