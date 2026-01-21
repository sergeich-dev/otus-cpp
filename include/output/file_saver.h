#ifndef _FILE_SAVER_H_
#define _FILE_SAVER_H_

#include "../output/ibulkoutput.h"

class CFileSaver : public IBulkOutput
{
public:
    virtual void OutputBulk(const ComandsList& commands, const std::string & postfix) const override;
};


#endif //_FILE_SAVER_H_
