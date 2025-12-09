#include <iostream>

#include "../include/string_parser/string_parser.h"
#include "../include/output/console_printer.h"
#include "../include/output/file_saver.h"

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

        std::cout << "Bulk size=" << nBulkSize << ". Start parsing standard input... \n";

        CBulkManager manager(std::make_unique<CConsolePrinter>(), std::make_unique<CFileSaver>());
        manager.SetBulkProcessingSize(nBulkSize);

        CStringParser parser(&manager);

        parser.DoWork();
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

