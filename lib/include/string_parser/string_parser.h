#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <stack>
#include "../command/base_command.h"
#include "../bulk/bulk_manager.h"

class CStringParser
{
public:
           explicit CStringParser(int nBulkProcessingSize);
                   ~CStringParser();

    void            ProcessString(const std::string & str);

private:

    std::unique_ptr<CBulkManager> m_pBulkManager;
    std::stack<std::string>       m_brackets;
};

#endif //_STRING_PARSER_H_
