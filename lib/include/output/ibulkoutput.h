#ifndef _IBULKOUTPUT_H_
#define _IBULKOUTPUT_H_

#include "../bulk/bulk.h"
#include "common.h"

class IBulkOutput
{
public:
    virtual ~IBulkOutput() = default;

    virtual void OutputBulk(const ComandsList& commands, const std::string & postfix) const = 0;
};

#endif //_IBULKOUTPUT_H_
