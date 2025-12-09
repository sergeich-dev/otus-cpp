#include "../../include/output/console_printer.h"

void CConsolePrinter::OutputBulk(const ComandsList &commands)
{
    std::cout << "bulk: ";

    for (auto it = commands.cbegin(); it != commands.cend(); ++it) {
        std::cout << (*it)->GetCommand();

        if (it != commands.cend() - 1)
            std::cout << ", ";
    }

    std::cout << "\n";
}
