#include "../../include/command/base_command.h"

CBaseCommand::CBaseCommand(std::string cmd)
: m_Command(std::move(cmd))
{
    m_CommandReceivedTime = std::chrono::system_clock::now();
}

std::string CBaseCommand::GetCommand() const
{
    return m_Command;
}

size_t CBaseCommand::GetCmdReceiveTime()
{
    return std::chrono::duration_cast<std::chrono::seconds>(m_CommandReceivedTime.time_since_epoch()).count();
}