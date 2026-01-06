#include <iostream>
#include "../include/args_parser.h"
#include "../include/files_collector.h"

int main(int argc, char *argv[])
{
    try
    {
        CArgsParser parser;

        parser.Parse(argc, argv);

        auto parsedArguments = parser.GetParsedValues();

        CFilesCollector filesCollector;

        if (!parsedArguments.m_Dirs.empty())
        {
            filesCollector.CollectFiles(parsedArguments.m_Dirs, parsedArguments.m_ExcludedDirs, parsedArguments.m_RecursionLevel,
                                        parsedArguments.m_FileMinimalSize, parsedArguments.m_FileMasks);

            filesCollector.SetReadingBlockSize(parsedArguments.m_FileReadBlockSize);
            filesCollector.SetHashAlgorythm(parsedArguments.m_HashAlgorythm);

            std::cout << "Start scanning for duplicate files... \n\n";
            filesCollector.PrepareDuplicates();

            filesCollector.PrintDuplicates();

            std::cout << "Finish \n";
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

