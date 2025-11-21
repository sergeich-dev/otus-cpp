#include <iostream>
#include <cassert>
#include "utils.h"
#include "matrix.h"

int main()
{
    try
    {
        Matrix<int, -1> matrix;

        assert(matrix.size() == 0);

        auto a = matrix[0][0];

        assert(a == -1);
        assert(matrix.size() == 0);

        FillMatrixMainDiagonal(matrix, {0,0}, {9,9});

        FillMatrixSecondaryDiagonal(matrix, {0,9}, {9,0});

        std::cout << "Range from [0,0] to [8,8]: " << std::endl;

        PrintMatrix(matrix, {0,0}, {8,8});

        std::cout << std::endl;

        std::cout << "Range from [1,1] to [8,8]: " << std::endl;

        PrintMatrix(matrix, {1,1}, {8,8});

        std::cout << std::endl;

        // Prints total=17 because for main diagonal and secondary
        // one element is common
        std::cout << "Total filled cells in matrix: " << matrix.size() << " (for main diagonal and secondary one element is common)" << std::endl;

        PrintMatrixCellsWithValues(matrix);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

