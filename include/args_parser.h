#ifndef _ARGS_PARSER_H_
#define _ARGS_PARSER_H_

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

struct CommandLineArguments
{
    std::vector<std::string> m_Dirs;
    std::vector<std::string> m_ExcludedDirs;
    std::vector<std::string> m_FileMasks;
    int                      m_RecursionLevel;
    int                      m_FileMinimalSize;
    int                      m_FileReadBlockSize;
    std::string              m_HashAlgorythm;
};

class CArgsParser
{
public:
                            CArgsParser     ();
                            ~CArgsParser    () = default;

    void                    Parse           (int argc, char* argv[]);
    CommandLineArguments    GetParsedValues () const;

private:
    po::options_description m_OptionsDescription;
    po::variables_map       m_ParsedValues;

    CommandLineArguments    m_ParsedArguments;
};

#endif //_ARGS_PARSER_H_
