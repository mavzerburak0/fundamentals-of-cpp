#pragma once
#include <iostream>

class Cell
{
private:
    int nrRow,
            nrColumn,
            value;
    Cell *pNextInRow,
            *pNextInColumn;
public:
    Cell() { }
    Cell(int row, int column, int value)
    {
        nrRow = row;
        nrColumn = column;
        this->value = value;
        pNextInRow = pNextInColumn = nullptr;
    }
    friend class SparseMatrix;
};

class SparseMatrix
{
private:
    int nRow,
            nColumn;
    Cell *pStartPoint;
public:
    SparseMatrix();
    SparseMatrix(int, int);
    int GetnRow() { return nRow; }
    int GetnColumn() { return nColumn; }
    Cell *GetStartPoint() { return pStartPoint; }
    void PrintSparseMatrix() const;
    void SetElement(int, int, int);
    //void RemoveElement(int, int);
    int GetElement(int nRow, int nColumn) const;
    SparseMatrix operator+(const SparseMatrix &sparse);
    SparseMatrix operator-(const SparseMatrix &sparse);
    SparseMatrix operator*(const SparseMatrix &sparse);
    SparseMatrix operator^(int value);
    SparseMatrix operator!();
    void operator+=(const SparseMatrix &sparse);
    void operator-=(const SparseMatrix &sparse);
    void operator*=(const SparseMatrix &sparse);
    bool operator==(const SparseMatrix &obj);
    friend std::ostream& operator<<(std::ostream& os, const SparseMatrix &sparse);
    friend std::istream& operator>>(std::istream& os, SparseMatrix &sparse);

private:
    void PrintControlRow() const;
    void PrintControlColumn() const;
};
