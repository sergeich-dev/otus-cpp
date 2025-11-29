#ifndef _TOOLS_H_
#define _TOOLS_H_

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
