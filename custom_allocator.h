#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <cstddef>
#include <iostream>

using namespace std;

constexpr static size_t MAX_RESERVED_ELEMENTS = 10;

template<class T>
class CustomAllocator
{
public:
    using value_type = T;

    using pointer = T*;

                    CustomAllocator   ();
                   ~CustomAllocator   ();

        void        reserve     ();
        pointer     allocate    (std::size_t            nElementsCount);
        void        deallocate  (pointer                pBuffer,
                                 std::size_t            nElementsCount);

private:
            void    report      (pointer                pBuffer,
                                 std::size_t            nElementsCount,
                                 const std::string    & operation) const;

    pointer m_pReservedMemory;
    int     m_nAllocatedElementsCount;
};

template<class T>
CustomAllocator<T>::CustomAllocator()
    : m_pReservedMemory (nullptr),
      m_nAllocatedElementsCount (0)
{}

template<class T>
CustomAllocator<T>::~CustomAllocator()
{}

template<typename T, typename U>
bool operator==(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) {
    return lhs.m_pReservedMemory == rhs.m_pReservedMemory;
}

template<typename T, typename U>
bool operator!=(const CustomAllocator<T>& lhs, const CustomAllocator<U>& rhs) {
    return !(lhs == rhs);
}

template<class T>
void CustomAllocator<T>::reserve()
{
    // if memory block is not reserved yet
    if (!m_pReservedMemory)
    {
        m_pReservedMemory = static_cast<pointer>(std::malloc(MAX_RESERVED_ELEMENTS * sizeof(T)));

        if (m_pReservedMemory)
        {
            //report(m_pReservedMemory, MAX_RESERVED_ELEMENTS, "Reserved");
        }
        else
            std::cerr << "Failed to reserve memory block \n";
    }
}

template<class T>
T* CustomAllocator<T>::allocate(std::size_t nElementsCount)
{
    if (!m_pReservedMemory)
        reserve();

    if (nElementsCount > (MAX_RESERVED_ELEMENTS - m_nAllocatedElementsCount))
    {
        std::cerr << "All memory is occupied!\n";
        throw std::bad_alloc();
    }

    auto allocatedBuffer = m_pReservedMemory + m_nAllocatedElementsCount;
    m_nAllocatedElementsCount += nElementsCount;

    //report(allocatedBuffer, nElementsCount, "Allocated");

    return allocatedBuffer;
}

template<class T>
void CustomAllocator<T>::deallocate(T* pBuffer, std::size_t __attribute__((unused)) nElementsCount)
{
    // pBuffer != m_pReservedMemory, deallocation would be skipped
    if (pBuffer != m_pReservedMemory)
        return;

    //report(pBuffer, MAX_RESERVED_ELEMENTS, "Deallocated");

    std::free(pBuffer);
    m_nAllocatedElementsCount = 0;
}

template<class T>
void CustomAllocator<T>::report(T* p, std::size_t nElementsCount, const std::string & operation) const
{
    std::cout << operation << ": " << sizeof(T) * nElementsCount
              << " bytes at " << std::hex << std::showbase
              << reinterpret_cast<void*>(p) << std::dec << '\n';
}

#endif //_ALLOCATOR_H_
