#include "../../include/bulk/bulk_manager.h"

CBulkManager::CBulkManager(std::unique_ptr<IBulkOutput> consolePrinter,
                           std::unique_ptr<IBulkOutput> fileSaver)
: m_ConsolePrinter  (std::move(consolePrinter))
, m_FileSaver       (std::move(fileSaver))
{}

void CBulkManager::SetBulkProcessingSize(int nBulkProcessingSize)
{
    m_nBulkProcessingSize = nBulkProcessingSize;
}

void CBulkManager::AddCommand(const std::shared_ptr<CBaseCommand> & cmd)
{
    m_Storage.AddCommand(cmd);
}

void CBulkManager::ExecuteBulk(bool bForce)
{
    if (!bForce && m_Storage.GetSize() != m_nBulkProcessingSize)
    {
        std::cout << "Its too early to execute bulk! \n";
        return;
    }

    if (m_Storage.GetSize())
    {
        m_ConsolePrinter->OutputBulk(m_Storage.GetCommands());
        m_FileSaver->OutputBulk(m_Storage.GetCommands());

        m_Storage.Flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

bool CBulkManager::IsTimeToExecuteBulk()
{
    return m_Storage.GetSize() == m_nBulkProcessingSize;
};