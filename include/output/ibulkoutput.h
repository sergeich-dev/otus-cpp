#ifndef _IBULKOUTPUT_H_
#define _IBULKOUTPUT_H_

#include "../bulk/bulk.h"

class IBulkOutput
{
public:
    virtual ~IBulkOutput() = default;
    virtual void OutputBulk(const ComandsList& commands) = 0;
};

#endif //_IBULKOUTPUT_H_
