#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <vector>
#include <string>
#include <algorithm>
#include "custom_container.h"

/**
 * @brief  Calculate factorial of given value
 * @retval factorial value
 */
int CalculateFactorial(int nValue)
{
    if (nValue == 0)
        return 1;

    return nValue * CalculateFactorial(nValue - 1);
}

/**
 * @brief  Print all map elems
 */
template<class T>
void PrintMap(const T & map)
{
    for (auto el : map)
    {
        std::cout << "[" << el.first << " " << el.second << "]";
    }

    std::cout << std::endl;
}

/**
 * @brief  Print all custom container elems
 */
template<class T>
void PrintCustomContainer(const T & custom)
{
    for (auto it = custom.begin(); it != custom.end(); ++it)
    {
        std::cout << "|" << *it << "|";
    }

    std::cout << std::endl;
}

/**
 * @brief  Fill container with values
 */
template<class T>
void FillContainer(T & map)
{
    for (int i = 0; i < 10; ++i)
    {
        auto nValue = CalculateFactorial(i);

        map[i] = nValue;
    }
}

template<class T>
void FillCustomContainer(T & custom)
{
    for (int i = 0; i < 10; ++i)
    {
        custom.insert(i);
    }
}

/**
 * @brief  Fill matrix main diagonal with values [0,9]
 */
template<class T>
void FillMatrixMainDiagonal(T & matrix, std::pair<int,int> startRange, std::pair<int,int> endRange)
{
    for (int i = startRange.first; i < endRange.first; ++i)
    {
        for (int j = startRange.second; j < endRange.second; ++j)
            if (i == j)
                matrix[i][j] = i;
    }
}

/**
 * @brief  Fill matrix secondary diagonal with values [9,0]
 */
template<class T>
void FillMatrixSecondaryDiagonal(T & matrix, std::pair<int,int> startRange, std::pair<int,int> endRange)
{
    for (int i = startRange.first; i < endRange.first; ++i)
    {
        for (int j = startRange.second; j >= endRange.second; --j)
            if (j == startRange.second - 1 - i)
                matrix[i][j] = j;
    }
}

template<class T>
void PrintMatrix(const T & matrix, std::pair<int,int> startRange, std::pair<int,int> endRange)
{
    for (int i = startRange.first; i <= endRange.first; ++i)
    {
        for (int j = startRange.second; j <= endRange.second; ++j)
            std::cout << matrix[i][j] << " ";

        std::cout << std::endl;
    }
}


template<class T>
void PrintMatrixCellsWithValues(const T & matrix)
{
    for (const auto el : matrix)
    {
        std::cout << "[" << el.x << "][" << el.y << "]=" << el.v << ", ";
    }

    std::cout << std::endl;
}

#endif //_TOOLS_H_
