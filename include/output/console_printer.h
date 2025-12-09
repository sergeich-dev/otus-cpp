#ifndef _CONSOLE_PRINTER_H_
#define _CONSOLE_PRINTER_H_

#include "../output/ibulkoutput.h"

class CConsolePrinter : public IBulkOutput
{
public:
    virtual void OutputBulk(const ComandsList& commands) override;
};

#endif //_CONSOLE_PRINTER_H_
