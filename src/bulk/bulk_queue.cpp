#include "../../include/bulk/bulk_queue.h"

bool CThreadSafeBulkQueue::Empty() const
{
    std::shared_lock lock(m_BulkQueueMtx);

    return m_BulkQueue.empty();
}

/**
 * @brief Get first element
 * @return Copy of first bulk in queue
 */
CBulk CThreadSafeBulkQueue::Front() const
{
    std::shared_lock lock(m_BulkQueueMtx);

    return m_BulkQueue.front();
}

void CThreadSafeBulkQueue::Push(const CBulk & bulk)
{
    std::cout << "CThreadSafeBulkQueue::Push add element\n";
    std::unique_lock lock(m_BulkQueueMtx);

    m_BulkQueue.push(bulk); // std::move ?

    m_cond_var.notify_all();
}

CBulk CThreadSafeBulkQueue::Pop()
{
    std::unique_lock lock(m_BulkQueueMtx);

    // проверить не пуста ли очередь? либо проверять в внешнем коде
    auto item = m_BulkQueue.front();

    m_BulkQueue.pop();

    return item;
}

void CThreadSafeBulkQueue::wait_and_pop(CBulk& item) {
    std::cout << "CThreadSafeBulkQueue::wait_and_pop wait and pop\n";

    std::unique_lock<std::shared_mutex> lock(m_BulkQueueMtx); // скорее всего shared_mutex это неправильно?
    m_cond_var.wait(lock, [this]{ return !m_BulkQueue.empty(); });
    item = std::move(m_BulkQueue.front());
    m_BulkQueue.pop();
}
