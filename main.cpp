#include <iostream>
#include <chrono>

#include "lib/include/string_parser/string_parser.h"
#include "async.h"

using namespace std::literals::chrono_literals;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Invalid arguments count! Stop working.\n";
            return -1;
        }

        auto nBulkSize = std::stoi(argv[1]);

        std::cout << "Start processing commands\n\n";

        std::string line;

        auto ctx  = connect(nBulkSize);
        while ( getline(std::cin, line) )
        {
            if (line.empty())
                break;

            receive(line.c_str(), line.size(), ctx);
        }

        disconnect(ctx);

        std::cout << "\nComplete\n";
    }
    catch (const std::invalid_argument & e)
    {
        std::cerr << "invalid_argument exception" << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

