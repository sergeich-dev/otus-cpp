#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <stack>
#include "../command/base_command.h"
#include "../bulk/bulk_manager.h"

class CStringParser
{
public:
           explicit CStringParser(CBulkManager          * manager);
                   ~CStringParser() = default;

    void            DoWork       ();

private:
    void            processString(const std::string & str);

private:

    CBulkManager                * m_pBulkManager;
    std::stack<std::string>       m_brackets;
};

#endif //_STRING_PARSER_H_
