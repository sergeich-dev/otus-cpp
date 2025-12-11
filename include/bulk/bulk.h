#ifndef _BULK_H_
#define _BULK_H_

#include <vector>
#include <memory>
#include "../command/base_command.h"

using ComandsList = std::vector<std::shared_ptr<CBaseCommand>>;

class CBulk
{
public:

    void                AddCommand  (const std::shared_ptr<CBaseCommand> & cmd);
    const ComandsList & GetCommands ();
    void                Clear       ();
    int                 GetSize     ();

private:

    ComandsList         m_commands;
};

#endif //_BULK_H_
