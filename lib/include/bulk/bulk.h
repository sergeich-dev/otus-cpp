#ifndef _BULK_H_
#define _BULK_H_

#include <vector>
#include <memory>
#include "../command/base_command.h"

using ComandsList = std::vector<std::shared_ptr<CBaseCommand>>;

class CBulk
{
public:

    enum eProcessingFlag : uint8_t
    {
        E_PF_CONSOLE_PROCESSING = 1,
        E_PF_FILE_PROCESSING    = 2
    };

    void                AddCommand  (const std::shared_ptr<CBaseCommand> & cmd);
    const ComandsList & GetCommands () const;
    void                Clear       ();
    int                 GetSize     ();

    bool                IsCompletelyProcessed();
    bool                IsPrintedToConsole   ();
    bool                IsSavedToFile        ();

    void                SetProcessingFlag(eProcessingFlag flag, bool bValue);

private:

    ComandsList         m_commands;

    bool                m_IsPrintedToConsole = false;
    bool                m_IsSavedToFile      = false;
};

inline bool CBulk::IsCompletelyProcessed()
{
    return m_IsPrintedToConsole && m_IsSavedToFile;
}

inline bool CBulk::IsPrintedToConsole()
{
    return m_IsPrintedToConsole;
}

inline bool CBulk::IsSavedToFile()
{
    return m_IsSavedToFile;
}

#endif //_BULK_H_
