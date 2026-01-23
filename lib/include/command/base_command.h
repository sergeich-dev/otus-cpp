#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <chrono>
#include <string>
#include <iostream>

using TTimePoint = std::chrono::time_point<std::chrono::system_clock>;

class CBaseCommand
{
public:
                                explicit CBaseCommand    (std::string cmd);
                                        ~CBaseCommand    () = default;

        std::string                      GetCommand       () const;
        uint64_t                         GetCommandID     () const;
        void                             SetCommandID     (uint64_t cmdID);

        size_t                           GetCmdReceiveTime();

private:

    TTimePoint                          m_CommandReceivedTime;
    std::string                         m_Command;
    uint64_t                            m_CommandID;
};

inline uint64_t CBaseCommand::GetCommandID() const
{
    return m_CommandID;
}

inline void CBaseCommand::SetCommandID(uint64_t cmdID)
{
    m_CommandID = cmdID;
}

#endif //_COMMAND_H_
