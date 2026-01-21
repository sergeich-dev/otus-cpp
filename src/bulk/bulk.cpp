#include "../../include/bulk/bulk.h"

void CBulk::AddCommand(const std::shared_ptr<CBaseCommand> & cmd)
{
    m_commands.push_back(cmd);
}

const ComandsList & CBulk::GetCommands() const
{
    return m_commands;
}

void CBulk::Clear()
{
    m_commands.clear();
}

int CBulk::GetSize()
{
    return m_commands.size();
}

void CBulk::SetProcessingFlag(eProcessingFlag flag, bool bValue)
{
    switch (flag)
    {
        case E_PF_CONSOLE_PROCESSING:
            m_IsPrintedToConsole = bValue;
            break;

        case E_PF_FILE_PROCESSING:
            m_IsSavedToFile = bValue;
            break;
    }
}
