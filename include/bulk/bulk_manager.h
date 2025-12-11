#ifndef _BULK_MANAGER_H_
#define _BULK_MANAGER_H_

#include <iostream>
#include "bulk.h"
#include "../output/ibulkoutput.h"
#include <chrono>
#include <thread>
#include <algorithm>

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

private:

    int                                  m_nBulkProcessingSize;
    CBulk                                m_Storage;
    BulkOutputMethods                    m_BulkOutputMethods;
    std::unique_ptr<IBulkOutput>         m_ConsolePrinter;
    std::unique_ptr<IBulkOutput>         m_FileSaver;
};

#endif //_BULK_MANAGER_H_
