#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "print_ip.h"

int main()
{
    try
    {
        printIp( int8_t{-1} ); // 255
        printIp( int16_t{0} ); // 0.0
        printIp( int32_t{2130706433} ); // 127.0.0.1
        printIp( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
        printIp( std::string{"Hello, World!"} ); // Hello, World!
        printIp( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
        printIp( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
        printIp(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
