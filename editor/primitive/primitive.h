#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include <cstdint>

class CPrimitiveBase
{
public:
    virtual            ~CPrimitiveBase() = default;

    virtual void        Move() = 0;
    virtual void        Draw() const = 0;

    uint32_t            GetObjectId() {};

private:

    uint32_t nObjectId;
};

class CPrimitiveCircle : public CPrimitiveBase
{
public:

    void                Move() override {};
    void                Draw() const override {};


private:

    int m_nCenterX;
    int m_nCenterY;
    int m_nRadius;
};

class CPrimitiveRectangle : public CPrimitiveBase
{
public:
    void                Move() override {};
    void                Draw() const override {};

private:

    int m_X;
    int m_Y;
    int m_nWidth;
    int m_nHeight;
};

class CPrimitiveTriangle : public CPrimitiveBase
{
public:
    void                Move() override {};
    void                Draw() const override {};

private:
    int m_X1;
    int m_Y1;

    int m_X2;
    int m_Y2;

    int m_X3;
    int m_Y3;
};

#endif //_PRIMITIVE_H_
