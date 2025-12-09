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

        size_t                           GetCmdReceiveTime();

private:

    TTimePoint                          m_CommandReceivedTime;
    std::string                         m_Command;
};

#endif //_COMMAND_H_
