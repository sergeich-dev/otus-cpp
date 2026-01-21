#ifndef _BULK__QUEUE_H_
#define _BULK__QUEUE_H_

#include <vector>
#include <queue>
#include <shared_mutex>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "../command/base_command.h"
#include "../bulk/bulk.h"

using ComandsList = std::vector<std::shared_ptr<CBaseCommand>>;

class CThreadSafeBulkQueue
{
public:

        bool    Empty   () const;
        CBulk   Front   () const;

        void    Push    (const CBulk & bulk);
        CBulk   Pop     ();

        void wait_and_pop(CBulk& item);

private:
    mutable std::shared_mutex   m_BulkQueueMtx;
    std::queue<CBulk>           m_BulkQueue;

    std::mutex                           m_mtx;
    std::condition_variable_any          m_cond_var;
};

#endif //_BULK__QUEUE_H_