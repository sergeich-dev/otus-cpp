#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <memory>
#include <list>
#include "../primitive/primitive.h"

using TPrimitive = std::shared_ptr<CPrimitiveBase>;
using TPrimitivesList = std::list<TPrimitive>;

class CDocument
{
public:

    CDocument() = default;
   ~CDocument() = default;

    void AddPrimitive(std::shared_ptr<CPrimitiveBase> pObj) {}
    void RemovePrimitive(uint32_t nObjId) {}

    const TPrimitivesList& GetObjectsList()
    { return m_ObjectsList; }

private:

    TPrimitivesList m_ObjectsList;
};

#endif //_DOCUMENT_H_
