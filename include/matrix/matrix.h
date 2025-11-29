#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <list>
#include <memory>
#include <algorithm>

template <typename T>
struct MatrixElement
{
    int x;
    int y;
    T   v;
};

template <typename T, T DefaultValue>
class ProxyMatrix
{
public:
     ProxyMatrix() = default;
    ~ProxyMatrix() = default;

    ProxyMatrix & operator=(const ProxyMatrix<T, DefaultValue>&) = delete;

    ProxyMatrix & operator[](int y_idx)
    {
        m_ElementInProcessing.y = y_idx;

        return *this;
    }

    ProxyMatrix & operator=(T value)
    {
        auto searchedX = m_ElementInProcessing.x;
        auto searchedY = m_ElementInProcessing.y;

        auto it = std::find_if(m_list.begin(), m_list.end(), [searchedX, searchedY](const auto & el)
        {
            return el.x == searchedX && el.y == searchedY;
        });

        if (it != m_list.end())
        {
            if (value == DefaultValue)
                m_list.erase(it);
            else
                it->v = value;
        }
        else
        {
            if (value == DefaultValue)
            {
                // nothing to do
            }
            else
            {
                m_list.push_back({ m_ElementInProcessing.x, m_ElementInProcessing.y, value});
            }
        }

        return *this;
    }

    operator T()
    {
        auto searchedX = m_ElementInProcessing.x;
        auto searchedY = m_ElementInProcessing.y;

        auto it = std::find_if(m_list.begin(), m_list.end(), [searchedX, searchedY](const auto & el)
        {
            return el.x == searchedX && el.y == searchedY;
        });

        if (it == m_list.end())
            return DefaultValue;
        else
        {
            return it->v;
        }
    }

    void setXIndex(int x)
    {
        m_ElementInProcessing.x = x;
    }

    size_t size()
    {
        return m_list.size();
    }

    typename std::list<MatrixElement<T>>::iterator begin() { return m_list.begin(); }
    typename std::list<MatrixElement<T>>::iterator end() { return m_list.end(); }

private:
    std::list<MatrixElement<T>> m_list;
    MatrixElement<T>            m_ElementInProcessing = {};
};

template <typename T, T DefaultValue>
class Matrix
{
public:

    Matrix()
    {
        ptrMatrix = std::make_unique<ProxyMatrix<T, DefaultValue>>();
    }

    ~Matrix() = default;

    ProxyMatrix<T, DefaultValue>& operator[](int x_idx)
    {
        ptrMatrix->setXIndex(x_idx);

        return *ptrMatrix;
    }

    ProxyMatrix<T, DefaultValue> & operator[](int x_idx) const
    {
        ptrMatrix->setXIndex(x_idx);

        return *ptrMatrix;
    }

    size_t size()
    {
        return ptrMatrix->size();
    }

    typename std::list<MatrixElement<T>>::iterator begin() const { return ptrMatrix->begin(); }
    typename std::list<MatrixElement<T>>::iterator end() const { return ptrMatrix->end(); }

private:

    std::unique_ptr<ProxyMatrix<T,DefaultValue>> ptrMatrix;
};

#endif //_MATRIX_H_
