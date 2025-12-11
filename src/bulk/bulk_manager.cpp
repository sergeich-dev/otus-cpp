#include "../../include/bulk/bulk_manager.h"

CBulkManager::CBulkManager()  = default;
CBulkManager::~CBulkManager() = default;

void CBulkManager::AddOutputMethod(std::unique_ptr<IBulkOutput> outputMethod)
{
    m_BulkOutputMethods.push_back(std::move(outputMethod));
}

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
        std::for_each(m_BulkOutputMethods.begin(), m_BulkOutputMethods.end(), [this](const auto & method)
        {
            method->OutputBulk(m_Storage.GetCommands());
        });

        m_Storage.Clear();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

const ComandsList & CBulkManager::GetCommands()
{
    return m_Storage.GetCommands();
};

bool CBulkManager::IsTimeToExecuteBulk()
{
    return m_Storage.GetSize() == m_nBulkProcessingSize;
};