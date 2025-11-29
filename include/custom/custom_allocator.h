#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <cstddef>
#include <iostream>

using namespace std;

template<class T, std::size_t Size>
class CustomAllocator
{
public:
    template<class Other>
    struct rebind { using other =  CustomAllocator<Other, Size>; };

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

template<class T, std::size_t Size>
CustomAllocator<T, Size>::CustomAllocator()
    : m_pReservedMemory (nullptr),
      m_nAllocatedElementsCount (0)
{}

template<class T, std::size_t Size>
CustomAllocator<T, Size>::~CustomAllocator()
{}

template<typename T, std::size_t TSize, typename U, std::size_t USize>
bool operator==(const CustomAllocator<T, TSize>& lhs, const CustomAllocator<U, USize>& rhs) {
    return lhs.m_pReservedMemory == rhs.m_pReservedMemory;
}

template<typename T, std::size_t TSize, typename U, std::size_t USize>
bool operator!=(const CustomAllocator<T, TSize>& lhs, const CustomAllocator<U, USize>& rhs) {
    return !(lhs == rhs);
}

template<class T, std::size_t Size>
void CustomAllocator<T, Size>::reserve()
{
    // if memory block is not reserved yet
    if (!m_pReservedMemory)
    {
        m_pReservedMemory = static_cast<pointer>(std::malloc(Size * sizeof(T)));

        if (m_pReservedMemory)
        {
            //report(m_pReservedMemory, Size, "Reserved");
        }
        else
            std::cerr << "Failed to reserve memory block \n";
    }
}

template<class T, std::size_t Size>
T* CustomAllocator<T, Size>::allocate(std::size_t nElementsCount)
{
    if (!m_pReservedMemory)
        reserve();

    if (nElementsCount > (Size - m_nAllocatedElementsCount))
    {
        std::cerr << "All memory is occupied!\n";
        throw std::bad_alloc();
    }

    auto allocatedBuffer = m_pReservedMemory + m_nAllocatedElementsCount;
    m_nAllocatedElementsCount += nElementsCount;

    //report(allocatedBuffer, nElementsCount, "Allocated");

    return allocatedBuffer;
}

template<class T, std::size_t Size>
void CustomAllocator<T, Size>::deallocate(T* pBuffer, std::size_t __attribute__((unused)) nElementsCount)
{
    // pBuffer != m_pReservedMemory, deallocation would be skipped
    if (pBuffer != m_pReservedMemory)
        return;

    //report(pBuffer, Size, "Deallocated");

    std::free(pBuffer);
    m_nAllocatedElementsCount = 0;
}

template<class T, std::size_t Size>
void CustomAllocator<T, Size>::report(T* p, std::size_t nElementsCount, const std::string & operation) const
{
    std::cout << operation << ": " << sizeof(T) * nElementsCount
              << " bytes at " << std::hex << std::showbase
              << reinterpret_cast<void*>(p) << std::dec << '\n';
}

#endif //_ALLOCATOR_H_
