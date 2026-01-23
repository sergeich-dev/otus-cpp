#ifndef _CONSOLE_PRINTER_H_
#define _CONSOLE_PRINTER_H_

#include "ibulkoutput.h"

class CConsolePrinter : public IBulkOutput
{
public:

    virtual void OutputBulk(const ComandsList& commands, const std::string & postfix) const override;
};

#endif //_CONSOLE_PRINTER_H_
