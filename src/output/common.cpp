#include "../../include/output/common.h"

void FormatOutput(std::ostream& os, const ComandsList& commands)
{
    os << "bulk: ";

    for (auto it = commands.cbegin(); it != commands.cend(); ++it) {
        os << (*it)->GetCommand();

        if (it != commands.cend() - 1)
            os << ", ";
    }

    os << "\n";
}