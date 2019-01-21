#include <iostream>
#include "SparseMatrix.h"

int main()
{
    // First sparse matrix creation

    SparseMatrix sp(3, 3);
    sp.SetElement(1, 1, 2);
    sp.SetElement(1, 2, 3);
    sp.SetElement(1, 3, 4);
    sp.SetElement(2, 3, 5);
    sp.SetElement(2, 2, 2);
    sp.SetElement(2, 1, 3);
    sp.SetElement(3, 1, 4);
    sp.SetElement(3, 3, 5);
    sp.SetElement(3, 2, 2);
    sp.SetElement(1, 1, 3);
    sp.SetElement(2, 2, 4);
    sp.SetElement(3, 3, 5);
    std::cout << "*-*-* FIRST SPARSE *-*-*:" << std::endl;
    sp.PrintSparseMatrix();
    std::cout << std::endl;

    /*
     * sp.RemoveElement(1,1);
     * std::cout << "Element removal: " << std::endl;
     * sp.PrintSparseMatrix();
     * std::cout << std::endl;
    */

    // Second sparse matrix creation

    SparseMatrix spTwo(3,3);
    spTwo.SetElement(1, 1, 6);
    spTwo.SetElement(1, 2, 1);
    spTwo.SetElement(1, 3, 2);
    spTwo.SetElement(2, 3, 4);
    spTwo.SetElement(2, 2, 3);
    spTwo.SetElement(2, 1, 3);
    spTwo.SetElement(3, 1, 2);
    spTwo.SetElement(3, 3, 4);
    spTwo.SetElement(3, 2, 6);
    spTwo.SetElement(1, 1, 5);
    spTwo.SetElement(2, 2, 3);
    spTwo.SetElement(3, 3, 1);
    std::cout << "*-*-* SECOND SPARSE *-*-*: " << std::endl;
    spTwo.PrintSparseMatrix();
    std::cout << std::endl;

    // Addition
    std::cout << "ADDITION: " << std::endl;
    SparseMatrix spThree = sp + spTwo;
    spThree.PrintSparseMatrix();
    std::cout << std::endl;

    // Subtraction
    std::cout << "SUBTRACTION: " << std::endl;
    SparseMatrix spFour = sp - spTwo;
    spFour.PrintSparseMatrix();
    std::cout << std::endl;

    // Multiplication
    std::cout << "MULTIPLICATION: " << std::endl;
    SparseMatrix spFive = sp * spTwo;
    spFive.PrintSparseMatrix();
    std::cout << std::endl;

    // Scalar multiplication
    std::cout << "SCALAR MULTIPLICATION: " << std::endl;
    SparseMatrix spSix = sp ^ 2;
    spSix.PrintSparseMatrix();
    std::cout << std::endl;

    // Transposing
    std::cout << "TRANSPOSING: " << std::endl;
    SparseMatrix spSeven = !sp;
    spSeven.PrintSparseMatrix();
    std::cout << std::endl;

    // Compound addition
    std::cout << "COMPOUND ADDITION: " << std::endl;
    spSeven += sp;
    spSeven.PrintSparseMatrix();
    std::cout << std::endl;

    // Compound subtraction
    std::cout << "COMPOUND SUBTRACTION: " << std::endl;
    spSix -= sp;
    spSix.PrintSparseMatrix();
    std::cout << std::endl;

    // Compound multiplication
    std::cout << "COMPOUND MULTIPLICATION: " << std::endl;
    spFive *= sp;
    spFive.PrintSparseMatrix();
    std::cout << std::endl;

    // Comparison
    std::cout << "COMPARISON: " << std::endl;
    if (sp == spTwo)
    {
        std::cout << "Sparse matrices are identical." << std::endl;
    }
    else
    {
        std::cout << "Sparse matrices are not identical." << std::endl;
    }
    std::cout << std::endl;


    return 0;
}

SparseMatrix::SparseMatrix()
{

}

SparseMatrix::SparseMatrix(int nRow, int nColumn)
{
    this->nRow = nRow;
    this->nColumn = nColumn;
    pStartPoint = new Cell(0, 0, 0);
    Cell *pPrior = nullptr;
    for (int i = 0; i < nRow; i++)
    { // build control row
        Cell *pNew = new Cell(0, nColumn - i, 0);
        pNew->pNextInRow = i ? pPrior : pStartPoint;
        pStartPoint->pNextInRow = pPrior = pNew;
    }
    for (int i = 0; i < nColumn; i++)
    { // build control column
        Cell *pNew = new Cell(nRow - i, 0, 0);
        pNew->pNextInColumn = i ? pPrior : pStartPoint;
        pStartPoint->pNextInColumn = pPrior = pNew;
    }
}


void SparseMatrix::PrintSparseMatrix() const
{
    PrintControlRow();
    PrintControlColumn();
    for (Cell *p = pStartPoint->pNextInColumn;  p != pStartPoint;  p = p->pNextInColumn)
    {
        std::cout << "Row: " << p->nrRow << std::endl;
        Cell *pFirst = p->pNextInRow; // auxiliary variable: pointer to the first element in this row
        if (!pFirst)
        { // not yet elements in this row
            continue;
        }
        Cell *q = pFirst; // auxiliary variable: in the loop points to the cells one after another
        do
        {
            std::cout << "Element " << q << ", (" << q->nrRow << ", " << q->nrColumn << ") value " << q->value <<
                 " pointers (" << q->pNextInRow << ", " << q->pNextInColumn <<")" << std::endl;
            q = q->pNextInRow;
        }
        while (q != pFirst);
    }
}

void SparseMatrix::PrintControlRow() const
{
    std::cout << "Control row:" << std::endl;
    for (Cell *p = pStartPoint->pNextInRow;  p != pStartPoint;  p = p->pNextInRow)
    {
        std::cout << "Element (" << p->nrRow << ", " << p->nrColumn << ") with value " << p->value << std::endl;
    }
}

void SparseMatrix::PrintControlColumn() const
{
    std::cout << "Control column:" << std::endl;
    for (Cell *p = pStartPoint->pNextInColumn; p != pStartPoint; p = p->pNextInColumn)
    {
        std::cout << "Element (" << p->nrRow << ", " << p->nrColumn << ") with value " << p->value << std::endl;
    }
}

void SparseMatrix::SetElement(int nRow, int nColumn, int value)
{
    if (nRow < 1 || nRow > this->nRow)
    {
        throw "Illegal row index";
    }
    if (nColumn < 1 || nColumn > this->nColumn)
    {
        throw "Illegal column index";
    }
    if (!value)
    {
        return; // zero values are not stored
    }
    //
    // Insert into row
    //
    Cell *pRow; // pointer to the control element of this row
    for (pRow = pStartPoint->pNextInColumn; pRow->nrRow != nRow; pRow = pRow->pNextInColumn);
    Cell *pFirst = pRow->pNextInRow; // auxiliary variable: pointer to the first element in this row
    if (pFirst)
    { // there are elements in this row, maybe the element to insert already exists
        Cell *q = pFirst; // auxiliary variable: in the loop points to the cells one after another
        do
        {
            if (q->nrColumn == nColumn)
            {
                q->value = value; // found it, change the value and return
                return;
            }
            q = q->pNextInRow;
        }
        while (q != pFirst);
    }
    Cell *pNew = new Cell(nRow, nColumn, value); // have to create the new element
    if (!pFirst)
    { // no elements in this row
        pRow->pNextInRow = pNew;
        pNew->pNextInRow = pNew;
    }
    else
    { // there are some elements
        Cell *q = pFirst, *pPrior = nullptr; // pPrior points to the cell after which the new cell should be inserted
        do
        {
            if (q->nrColumn < nColumn)
            {
                pPrior = q;
                q = q->pNextInRow;
            }
            else
            {
                break;
            }
        }
        while (q != pFirst);
        if (pPrior)
        {
            pPrior->pNextInRow = pNew; // insert resetting pointers
            pNew->pNextInRow = q;
        }
        else
        { // pPrior == nullptr means the new cell will be first in the chain
            Cell *r;
            for (r = pFirst; r->pNextInRow != pFirst; r = r->pNextInRow); // find the last in the chain
            r->pNextInRow = pNew; // reset pointers
            pRow->pNextInRow = pNew;
            pNew->pNextInRow = q;
        }
    }
    //
    // Insert into column
    //
    Cell * pColumn; // pointer to the control element of this column
    for (pColumn = pStartPoint->pNextInRow; pColumn->nrColumn != nColumn; pColumn = pColumn->pNextInRow);
    pFirst = pColumn->pNextInColumn; // auxiliary variable: pointer to the first element in this column
    if (!pFirst)
    { // no elements in this column
        pColumn->pNextInColumn = pNew;
        pNew->pNextInColumn = pNew;
    }
    else
    { // there are some elements
        Cell *q = pFirst, *pPrior = nullptr; // pPrior points to the cell after which the new cell should be inserted
        do
        {
            if (q->nrRow < nRow)
            {
                pPrior = q;
                q = q->pNextInColumn;
            }
            else
            {
                break;
            }
        }
        while (q != pFirst);
        if (pPrior)
        {
            pPrior->pNextInColumn = pNew; // insert resetting pointers
            pNew->pNextInColumn = q;
        }
        else
        { // pPrior == nullptr means the new cell will be first in the chain
            Cell *r;
            for (r = pFirst; r->pNextInColumn != pFirst; r = r->pNextInColumn); // find the last in the chain
            r->pNextInColumn = pNew; // reset pointers
            pRow->pNextInColumn = pNew;
            pNew->pNextInColumn = q;
        }
    }
}

int SparseMatrix::GetElement(int nRow, int nColumn) const
{
    for (Cell * p = pStartPoint->pNextInColumn;  p != pStartPoint;  p = p->pNextInColumn)
    {
        Cell * pFirst = p->pNextInRow;
        Cell * q = pFirst;
        do
        {
            if (q->nrColumn == nColumn && q->nrRow == nRow)
            {
                return q->value;
            }
            q = q->pNextInRow;
        }
        while (q != pFirst);
    }

    return -1;
}


SparseMatrix SparseMatrix::operator+(const SparseMatrix & sparse)
{
    SparseMatrix newSparse = SparseMatrix(this->nRow, this->nColumn);

    for (int i = 1; i <= this->nColumn; i++)
    {
        for (int j = 1; j <= this->nRow; j++)
        {
            int firstVal = this->GetElement(i,j);
            int secondVal = sparse.GetElement(i,j);
            newSparse.SetElement(i,j, (firstVal + secondVal));
        }
    }

    return newSparse;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix & sparse)
{
    SparseMatrix newSparse = SparseMatrix(this->nRow, this->nColumn);

    for (int i = 1; i <= this->nColumn; i++)
    {
        for (int j = 1; j <= this->nRow; j++)
        {
            int firstVal = this->GetElement(i,j);
            int secondVal = sparse.GetElement(i,j);
            newSparse.SetElement(i,j, (firstVal - secondVal));
        }
    }
    return newSparse;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix & sparse)
{
    SparseMatrix newSparse = SparseMatrix(this->nRow, this->nColumn);

    for (int i = 1; i <= nRow; i++) {
        for (int j = 1; j <= nColumn; j++) {
            int val = 0;
            for (int k = 0; k < nRow; k++) {
                val = this->GetElement(i, k) * sparse.GetElement(k, j);
            }
            newSparse.SetElement(i, j, val);
        }
    }
    return newSparse;
}

SparseMatrix SparseMatrix::operator^(int scalar)
{
    SparseMatrix newSparse = SparseMatrix(this->nRow, this->nColumn);

    for (int i = 1; i <= this->nColumn; i++) {
        for (int j = 1; j <= this->nRow; j++) {
            int val = this->GetElement(i,j);
            newSparse.SetElement(i,j, (val * scalar));
        }
    }

    return newSparse;
}

SparseMatrix SparseMatrix::operator!()
{
    SparseMatrix newSparse = SparseMatrix(this->nColumn, this->nRow);
    for (int i = 1; i <= nRow; i++)
        for (int j = 1; j <= nColumn; j++)
            newSparse.SetElement(j, i, this->GetElement(i, j));
    return newSparse;
}

void SparseMatrix::operator+=(const SparseMatrix & sparse)
{
    for (int i = 1; i <= nRow; i++)
        for (int j = 1; j <= nColumn; j++)
            SetElement(i, j, this->GetElement(i, j) + sparse.GetElement(i, j));
}

void SparseMatrix::operator-=(const SparseMatrix & sparse)
{
    for (int i = 1; i <= nRow; i++)
        for (int j = 1; j <= nColumn; j++)
            SetElement(i, j, this->GetElement(i, j) - sparse.GetElement(i, j));
}

void SparseMatrix::operator*=(const SparseMatrix & sparse)
{
    SparseMatrix result = (*this) * sparse;
    (*this) = result;
}

bool SparseMatrix::operator==(const SparseMatrix & sparse)
{

    for (int i = 0; i < this->nRow; i++)
    {
        for (int j = 0; j< this->nColumn; j++)
        {
            if (this->GetElement(i,j) != sparse.GetElement(i,j))
            {
                return false;
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const SparseMatrix & sparse)
{
    sparse.PrintSparseMatrix();
    return os;
}

std::istream& operator>>(std::istream& ist, SparseMatrix & sparse)
{
    int val;
    ist >> val;
    for (int i = 0; i < sparse.nRow; i++)
    {
        for (int j = 0; j < sparse.nColumn; j++)
        {
            sparse.SetElement(i, j, val);
        }
    }
        return ist;
}

/*
void SparseMatrix::RemoveElement(int nRow, int nColumn)
{
    for (Cell * p = pStartPoint->pNextInColumn;  p != pStartPoint;  p = p->pNextInColumn)
    {
        Cell * pFirst = p->pNextInRow;
        Cell * q = pFirst;
        do
        {
            if (q->nrColumn == nColumn && q->nrRow == nRow)
            {
                delete(q);
            }
            q = q->pNextInRow;
        }
        while (q != pFirst);
    }
}
*/