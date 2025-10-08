#ifndef _CUSTOM_CONTAINER_H_
#define _CUSTOM_CONTAINER_H_

#include <iostream>
#include <memory>

constexpr static size_t MAX_CONTAINER_ELEMENTS = 10;

template <class T, class Allocator = std::allocator<T>>
class CustomContainer
{
public:
                    CustomContainer();
                   ~CustomContainer();

        void        insert(T elem);
        T*          begin() const;
        T*          end() const;

private:

    Allocator allocator;

    size_t    nElementsCount = 0;
    T*        pBegin         = nullptr;
};

template<class T, class Allocator>
CustomContainer<T, Allocator>::CustomContainer()
{
}

template<class T, class Allocator>
CustomContainer<T, Allocator>::~CustomContainer()
{
    allocator.deallocate(pBegin, MAX_CONTAINER_ELEMENTS);
}

template<class T, class Allocator>
void CustomContainer<T, Allocator>::insert(T elem)
{
    if (!pBegin)
        pBegin = allocator.allocate(MAX_CONTAINER_ELEMENTS);

    pBegin[nElementsCount] = elem;

    nElementsCount++;
}

template<class T, class Allocator>
T* CustomContainer<T, Allocator>::begin() const
{
    return pBegin;
}

template<class T, class Allocator>
T* CustomContainer<T, Allocator>::end() const
{
    return pBegin + nElementsCount;
}

#endif //_CUSTOM_CONTAINER_H_
