#include "../../include/string_parser/string_parser.h"
#include <iostream>

CStringParser::CStringParser(int nBulkProcessingSize)
: m_pBulkManager(std::make_unique<CBulkManager>())
{
    m_pBulkManager->SetBulkProcessingSize(nBulkProcessingSize);

    m_pBulkManager->AddOutputMethod(std::make_unique<CConsolePrinter>());
    m_pBulkManager->AddOutputMethod(std::make_unique<CFileSaver>());
}

CStringParser::~CStringParser()
{
    m_pBulkManager->ExecuteBulk(true);
}

void CStringParser::ProcessString(const std::string & str)
{
    if (str.empty())
        return;

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
        if (m_brackets.empty())
        {
            // nothing to do, stack empty
            return;
        }

        if (m_brackets.top() != "{")
        {
            // nothing to do, no corresponding opening bracket
            return;
        }

        if (!m_brackets.empty())
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