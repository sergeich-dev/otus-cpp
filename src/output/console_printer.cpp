#include "../../include/output/console_printer.h"

void CConsolePrinter::OutputBulk(const ComandsList &commands)
{
    FormatOutput(std::cout, commands);
}
