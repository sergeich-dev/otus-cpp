#include <iostream>
#include <map>
#include "custom_allocator.h"
#include "custom_container.h"
#include "utils.h"

int main()
{
    try
    {
        std::map<int, int> mapValues;

        FillContainer(mapValues);

        std::cout << "Map with standard allocator: ";
        PrintMap(mapValues);

        std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> mapValuesCA;

        FillContainer(mapValuesCA);

        std::cout << "Map with custom allocator: ";
        PrintMap(mapValuesCA);

        CustomContainer<int> custom;

        FillCustomContainer(custom);

        std::cout << "Custom container with standard allocator: ";

        PrintCustomContainer(custom);

        CustomContainer<int, CustomAllocator<int>> custom2;

        FillCustomContainer(custom2);

        std::cout << "Custom container with custom allocator: ";

        PrintCustomContainer(custom2);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
