#ifndef _FILE_SAVER_H_
#define _FILE_SAVER_H_

#include "../output/ibulkoutput.h"

class CFileSaver : public IBulkOutput
{
public:
    virtual void OutputBulk(const ComandsList& commands) override;
};


#endif //_FILE_SAVER_H_
