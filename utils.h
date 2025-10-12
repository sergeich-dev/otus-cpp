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
 * @brief Prints the every byte of a integral value.
 */
void printIntegralBytes(const void* number, size_t size)
{
    auto bytes = static_cast<const uint8_t*>(number);

    for (size_t i = 0; i < size; ++i)
    {
        std::cout << static_cast<int>(bytes[size - 1 - i]);
        if (i < size - 1)
        {
            std::cout << '.';
        }
    }
    std::cout << std::endl;
}

#endif //_TOOLS_H_
