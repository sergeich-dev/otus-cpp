#ifndef IP_FILTER_TOOLS_H
#define IP_FILTER_TOOLS_H

#include <vector>
#include <string>
#include <algorithm>

/**
 * @brief Split string array of ip parts
 *  ("",  '.') -> [""]
 *  ("11", '.') -> ["11"]
 *  ("..", '.') -> ["", "", ""]
 *  ("11.", '.') -> ["11", ""]
 *  (".11", '.') -> ["", "11"]
 *  ("11.22", '.') -> ["11", "22"]
 * @retval array of ip parts
 */
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

/**
 * @brief Print ip adresses
 */
void printIpPool(const std::vector<std::vector<std::string> > & ipPool)
{
    for(const auto & ipAddr : ipPool)
    {
        for(auto ipAddrPart = ipAddr.cbegin(); ipAddrPart != ipAddr.cend(); ++ipAddrPart)
        {
            if (ipAddrPart != ipAddr.cbegin())
            {
                std::cout << ".";

            }
            std::cout << *ipAddrPart;
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Filter ip addresses by throwing away ones with first byte = 1
 * @retval list of ip filtered addresses
 */
std::vector<std::vector<std::string> > filterIpPool(const std::vector<std::vector<std::string> > & ipSrcPool)
{
    std::vector<std::vector<std::string> > filteredPool;

    std::copy_if(ipSrcPool.begin(), ipSrcPool.end(),
                 std::back_inserter(filteredPool),
                 [](const auto & ipAddr) { return ipAddr[0] == "1"; });

    return filteredPool;
}

/**
 * @brief  Filter ip addresses by throwing away ones with first byte = firstVal, second byte = secondVal
 * @retval list of ip filtered addresses
 */
std::vector<std::vector<std::string> > filterIpPoolByValues(const std::vector<std::vector<std::string> > & ipSrcPool, int firstVal, int secondVal)
{
    std::vector<std::vector<std::string> > filteredPool;

    std::copy_if(ipSrcPool.begin(), ipSrcPool.end(),
                 std::back_inserter(filteredPool),
                 [=](const auto & ipAddr)
                 {
                     return std::stoi(ipAddr[0]) == firstVal && std::stoi(ipAddr[1]) == secondVal;
                 });

    return filteredPool;
}

/**
 * @brief  Filter ip addresses by throwing away ones which have any byte = value
 * @retval list of ip filtered addresses
 */
std::vector<std::vector<std::string> > filterIpPoolByAny(const std::vector<std::vector<std::string> > & ipSrcPool, int value)
{
    std::vector<std::vector<std::string> > filteredPool;

    std::copy_if(ipSrcPool.begin(), ipSrcPool.end(),
                 std::back_inserter(filteredPool),
                 [=](const auto & ipAddr)
                 {
                     return std::find_if(ipAddr.begin(), ipAddr.end(), [=](const auto & el){ return std::stoi(el) == value; }) != ipAddr.end();
                 });

    return filteredPool;
}

#endif //IP_FILTER_TOOLS_H
