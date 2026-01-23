#include "../../include/output/console_printer.h"

void CConsolePrinter::OutputBulk(const ComandsList &commands, [[maybe_unused]] const std::string & postfix) const
{
    FormatOutput(std::cout, commands);
}
