#include "../../include/bulk/bulk_manager.h"

CBulkManager::CBulkManager()
{
    m_ConsoleLogThread  = std::thread(&CBulkManager::ConsoleThreadWork, this);

    for (int i = 0; i < FILE_LOG_THREADS_COUNT; ++i)
    {
        m_FileLogThreads[i] = std::thread(&CBulkManager::FileThreadWork, this);
    }
}

CBulkManager::~CBulkManager()
{
   stop();
};

void CBulkManager::stop() {
    m_bDoneFlag = true;
    m_CondVar.notify_all();

    m_ConsoleLogThread.join();

    std::for_each(m_FileLogThreads.begin(), m_FileLogThreads.end(), [](auto & thread){
        thread.join();
    });
}

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
    cmd->SetCommandID(++m_CmdCurrentID);
    m_Storage.AddCommand(cmd);
}

void CBulkManager::ExecuteBulk(bool bForce)
{
    if (!bForce && m_Storage.GetSize() != m_nBulkProcessingSize)
    {
        // too early to execute bulk!
        return;
    }

    if (m_Storage.GetSize())
    {
        {
            std::lock_guard<std::mutex> lck(m_mutex);

            m_BulkQueue.push(m_Storage);
        }

        m_CondVar.notify_all();

        m_Storage.Clear();
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


void CBulkManager::ConsoleThreadWork()
{
    while (1) {
        std::unique_lock<std::mutex> lck{m_mutex};

        m_CondVar.wait(lck, [this]{
            return !m_BulkQueue.empty() || m_bDoneFlag;
        });

        if (m_bDoneFlag && m_BulkQueue.empty())
            break;

        if (m_BulkQueue.front().IsPrintedToConsole())
            continue;

        CBulk elemCopy;
        auto & elem = m_BulkQueue.front();

        elem.SetProcessingFlag(CBulk::E_PF_CONSOLE_PROCESSING, true);
        elemCopy = elem;

        if (elem.IsCompletelyProcessed()) {
            m_BulkQueue.pop();
        }

        lck.unlock();

        ProcessQueueElement(CBulk::E_PF_CONSOLE_PROCESSING, elemCopy);
    }
}

void CBulkManager::FileThreadWork()
{
    while (1) {
        std::unique_lock<std::mutex> lck{m_mutex};

        m_CondVar.wait(lck, [this]{
            return !m_BulkQueue.empty() || m_bDoneFlag;
        });

        if (m_bDoneFlag && m_BulkQueue.empty())
            break;

        if (m_BulkQueue.front().IsSavedToFile())
            continue;

        CBulk elemCopy;

        auto & elem = m_BulkQueue.front();

        elem.SetProcessingFlag(CBulk::E_PF_FILE_PROCESSING, true);
        elemCopy = elem;

        if (elem.IsCompletelyProcessed()) {
            m_BulkQueue.pop();
        }

        lck.unlock();

        ProcessQueueElement(CBulk::E_PF_FILE_PROCESSING, elemCopy);
    }
}

void CBulkManager::ProcessQueueElement(CBulk::eProcessingFlag eProcessingFlag, const CBulk & elem)
{
    auto methodIt = std::find_if(m_BulkOutputMethods.begin(), m_BulkOutputMethods.end(), [eProcessingFlag](const auto & method)
    {
        if (eProcessingFlag == CBulk::E_PF_CONSOLE_PROCESSING)
            return dynamic_cast<CConsolePrinter* >(method.get()) != nullptr;
        else
            return dynamic_cast<CFileSaver* >(method.get()) != nullptr;
    });

    auto threadId = std::this_thread::get_id();

    std::stringstream ss;
    ss << threadId;
    std::string postfix = ss.str();

    (*methodIt)->OutputBulk(elem.GetCommands(), postfix);
}
