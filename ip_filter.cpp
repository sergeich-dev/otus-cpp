#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "tools.h"

int main()
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        auto comp = [](const std::vector<std::string> & a, const std::vector<std::string> & b)
        {
            bool isGreater = false;

            for (size_t idx = 0; idx < std::min(a.size(), b.size()); ++idx)
            {
                int valA = std::stoi(a[idx]);
                int valB = std::stoi(b[idx]);

                if (valA == valB)
                    continue;
                else if (valA > valB)
                {
                    isGreater = true;
                    break;
                }
                else
                    break;
            }

            return isGreater;
        };

        std::sort(ip_pool.begin(), ip_pool.end(), comp);

        printIpPool(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        auto filteredIpPool = filterIpPool(ip_pool);
        printIpPool(filteredIpPool);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        filteredIpPool = filterIpPoolByValues(ip_pool, 46, 70);
        printIpPool(filteredIpPool);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        filteredIpPool = filterIpPoolByAny(ip_pool, 46);
        printIpPool(filteredIpPool);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
