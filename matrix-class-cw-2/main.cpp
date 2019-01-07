#include <iostream>
#include <exception>
#include "Matrix.h"


int main() {
    // Random seed
    srand((unsigned)time(NULL));
    try
    {
        // Empty constructor
        std::cout << "This will show an empty line since empty constructor initializes"
        << " with zero rows and columns." << std::endl;
        Matrix* emptyMatrix = new Matrix();
        std::cout << *emptyMatrix;

        // Constructor with parameters
        std::cout << "Constructed with parameters: " << std::endl;
        Matrix* testMatrix = new Matrix(5, 5);
        Matrix* secondTestMatrix = new Matrix(5, 5);
        std::cout << *testMatrix;
        std::cout << *secondTestMatrix;

        // Copy constructor

        std::cout << "Copy constructor demonstration: " << std::endl;
        Matrix* copiedMatrix = testMatrix;
        std::cout << *copiedMatrix;

        // Accessor functions

        std::cout << "Accessor functions demonstration: " << std::endl;
        std::cout << "Rows: " << testMatrix->getRows() << std::endl;
        std::cout << "Columns: " << testMatrix->getCols() << std::endl;
        std::cout << "Value at row 4, column 5: " << testMatrix->getValue(3, 4) << std::endl;
        std::cout << "Value at row 4, column 5 changed to 51." << std::endl;
        testMatrix->setValue(51, 3, 4);
        std::cout << "Value at row 4, column 5: " << testMatrix->getValue(3, 4) << std::endl;
        std::cout << std::endl;

        // Operators overloaded

        std::cout << "Sum of two matrices: " << std::endl;
        std::cout << *testMatrix + *secondTestMatrix;
        std::cout << "Difference of two matrices: " << std::endl;
        std::cout << *testMatrix - *secondTestMatrix;
        std::cout << "Product of two matrices: " << std::endl;
        std::cout << *testMatrix * *secondTestMatrix;
        std::cout << "Set one matrix equal to another: (need to uncomment line 47)" << std::endl;
        // secondTestMatrix = testMatrix;
        /*
        std::cout << *testMatrix << *secondTestMatrix << std::endl;
        std::cout << "Compound operator overloading: " << std::endl;
        *testMatrix += *secondTestMatrix;
        std::cout << *testMatrix;
        *testMatrix -= *secondTestMatrix;
        std::cout << *testMatrix;
        *testMatrix *= *secondTestMatrix;
        std::cout << *testMatrix;
        */
        // Comparison
        std::cout << (*testMatrix == *secondTestMatrix) << std::endl;
        std::cout << "Scalar multiplication: " << std::endl;
        *testMatrix = *testMatrix ^ 2;
        std::cout << *testMatrix;

        // Not sure if this is what's asked for with transposing
        std::cout << "Transposing: " << std::endl;
        *testMatrix = !*testMatrix;
        std::cout << *testMatrix;


    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}