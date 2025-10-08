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

#endif //_TOOLS_H_
