#include <fstream>
#include "../../include/output/file_saver.h"

void CFileSaver::OutputBulk(const ComandsList &commands, const std::string & postfix) const
{
    if (commands.empty())
        return;

    std::string filename = "bulk_";

    const auto & firstCmd = commands[0];

    auto strFirstCmdID   = std::to_string(firstCmd->GetCommandID());
    auto strFirstCmdTime = std::to_string(firstCmd->GetCmdReceiveTime());

    filename += (strFirstCmdID + "_");
    filename += (strFirstCmdTime + "_");

    filename += postfix;
    filename += ".log";

    std::ofstream out(filename);

    FormatOutput(out, commands);
}
