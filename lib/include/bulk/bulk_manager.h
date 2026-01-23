#ifndef _BULK_MANAGER_H_
#define _BULK_MANAGER_H_

#include <iostream>
#include "bulk.h"
#include "../output/ibulkoutput.h"
#include "../output/file_saver.h"
#include "../output/console_printer.h"
#include <chrono>
#include <queue>
#include <array>
#include <thread>
#include <atomic>
#include <sstream>
#include <algorithm>
#include <condition_variable>

constexpr int FILE_LOG_THREADS_COUNT = 2;

class CBulkManager
{
    using BulkOutputMethods = std::vector<std::unique_ptr<IBulkOutput>>;

public:
                    CBulkManager         ();
                   ~CBulkManager         ();

    void            AddOutputMethod      (std::unique_ptr<IBulkOutput> outputMethod);

    void            ExecuteBulk          (bool bForce = false);

    void            SetBulkProcessingSize(int nBulkProcessingSize);
    void            AddCommand           (const std::shared_ptr<CBaseCommand> & cmd);

    const ComandsList &
                    GetCommands         ();

    bool            IsTimeToExecuteBulk  ();

    void            ConsoleThreadWork     ();
    void            FileThreadWork        ();

    void            ProcessQueueElement   (CBulk::eProcessingFlag eProcessingFlag,
                                           const CBulk & elem);

private:
    void            stop                  ();

private:

    int                                  m_nBulkProcessingSize;
    CBulk                                m_Storage;
    uint64_t                             m_CmdCurrentID = 0;

    BulkOutputMethods                    m_BulkOutputMethods;
    std::unique_ptr<IBulkOutput>         m_ConsolePrinter;
    std::unique_ptr<IBulkOutput>         m_FileSaver;

    std::condition_variable              m_CondVar;
    std::mutex                           m_mutex;
    std::queue<CBulk>                    m_BulkQueue;

    std::thread                          m_ConsoleLogThread;

    std::array<std::thread, FILE_LOG_THREADS_COUNT>
                                         m_FileLogThreads;

    std::atomic<bool>                    m_bDoneFlag{false};
};

#endif //_BULK_MANAGER_H_
