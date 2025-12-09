#include <fstream>
#include "../../include/output/file_saver.h"

void CFileSaver::OutputBulk(const ComandsList &commands)
{
    if (commands.empty())
        return;

    std::string filename = "bulk";

    const auto & firstCmd = commands[0];

    auto strFirstCmdTime = std::to_string(firstCmd->GetCmdReceiveTime());

    filename += strFirstCmdTime;
    filename += ".log";

    std::ofstream out(filename);

    out << "bulk: ";

    for (auto it = commands.cbegin(); it != commands.cend(); ++it) {
        out << (*it)->GetCommand();

        if (it != commands.cend() - 1)
            out << ", ";
    }

    out << "\n";
}
