#include "../include/args_parser.h"

CArgsParser::CArgsParser()
    : m_OptionsDescription("Options")
{
    m_OptionsDescription.add_options()
            ("help,h", "Show help")
            ("dir,d", po::value<std::vector<std::string>>(&m_ParsedArguments.m_Dirs)->multitoken()->composing(), "Scan directories")
            ("exclude,e", po::value<std::vector<std::string>>(&m_ParsedArguments.m_ExcludedDirs)->multitoken()->composing(), "Exclude directories")
            ("level,l", po::value<int>(&m_ParsedArguments.m_RecursionLevel)->default_value(0), "Recursion level (0=no recursion)")
            ("min-size,m", po::value<int>(&m_ParsedArguments.m_FileMinimalSize)->default_value(1), "Min file size")
            ("mask", po::value<std::vector<std::string>>(&m_ParsedArguments.m_FileMasks)->composing(), "File masks (case-insensitive)")
            ("block-size,s", po::value<int>(&m_ParsedArguments.m_FileReadBlockSize)->default_value(4096), "Block size S")
            ("hash,H", po::value<std::string>(&m_ParsedArguments.m_HashAlgorythm)->default_value("crc32"), "Hash: crc32, md5");
}

void CArgsParser::Parse(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Incorrect using of utility: no arguments given\n\n";
        std::cout << m_OptionsDescription << "\n";
        return;
    }

    po::store(po::parse_command_line(argc, argv, m_OptionsDescription), m_ParsedValues);
    po::notify(m_ParsedValues);

    if (m_ParsedValues.count("help")) {
        std::cout << m_OptionsDescription << "\n";
        return;
    }

    if (m_ParsedArguments.m_Dirs.empty()) {
        std::cout << "No directories for scan given\n\n";

        std::cout << m_OptionsDescription << "\n";
        return;
    }

}

CommandLineArguments CArgsParser::GetParsedValues() const
{
    return m_ParsedArguments;
}
