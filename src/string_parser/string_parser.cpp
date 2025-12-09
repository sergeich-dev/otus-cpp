#include "../../include/string_parser/string_parser.h"
#include <iostream>

CStringParser::CStringParser(CBulkManager * manager)
: m_pBulkManager(manager)
{}

void CStringParser::DoWork()
{
    std::string line;
    while ( getline(std::cin, line) )
    {
        processString(line);
    }

    m_pBulkManager->ExecuteBulk(true);

    std::cout << "End parsing." <<std::endl;
}


void CStringParser::processString(const std::string & str)
{
    if (str == "{")
    {
        if (m_brackets.empty()) {
            // execute previous block prematurely
            m_pBulkManager->ExecuteBulk(true);
        }

        m_brackets.push(str);
    }
    else if (str == "}")
    {
        if (m_brackets.top() != "{")
        {
            // nothing to do, no corresponding opening bracket
            return;
        }

        m_brackets.pop();

        if (m_brackets.empty()) {
            // time to execute dynamic block
            m_pBulkManager->ExecuteBulk(true);
        }
    }
    else
    {
        auto cmd = std::make_shared<CBaseCommand>(str);

        m_pBulkManager->AddCommand(cmd);

        if (m_brackets.empty() && m_pBulkManager->IsTimeToExecuteBulk())
        {
            m_pBulkManager->ExecuteBulk();
        }
    }
}