#ifndef _BULK_MANAGER_H_
#define _BULK_MANAGER_H_

#include <iostream>
#include "bulk.h"
#include "../output/ibulkoutput.h"
#include <chrono>
#include <thread>

class CBulkManager
{
public:
    explicit        CBulkManager         (std::unique_ptr<IBulkOutput> consolePrinter,
                                          std::unique_ptr<IBulkOutput> fileSaver);

    void            ExecuteBulk          (bool bForce = false);

    void            SetBulkProcessingSize(int nBulkProcessingSize);
    void            AddCommand           (const std::shared_ptr<CBaseCommand> & cmd);

    bool            IsTimeToExecuteBulk  ();

private:

    int                                  m_nBulkProcessingSize;
    CBulk                                m_Storage;
    std::unique_ptr<IBulkOutput>         m_ConsolePrinter;
    std::unique_ptr<IBulkOutput>         m_FileSaver;
};

#endif //_BULK_MANAGER_H_
