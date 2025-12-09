#include "../../include/bulk/bulk.h"

void CBulk::AddCommand(const std::shared_ptr<CBaseCommand> & cmd)
{
    m_commands.push_back(cmd);
}

const ComandsList & CBulk::GetCommands()
{
    return m_commands;
}

void CBulk::Flush()
{
    m_commands.clear();
}

int CBulk::GetSize()
{
    return m_commands.size();
}
