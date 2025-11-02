#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <memory>
#include "../primitive/primitive.h"
#include "../document/document.h"
#include "../renderer/renderer.h"

enum ePrimitiveObjectType : uint8_t
{
    E_POT_CIRCLE    = 1,
    E_POT_RECTANGLE = 2,
    E_POT_TRIANGLE  = 3,
};

class CController
{
public:
    CController()
    {
        m_pRenderer = std::make_shared<CRenderer>();
    };

    void CreateDocument()
    {
        m_pDocument = std::make_shared<CDocument>();
    }

    // process path
    void ImportDocument(const std::string & path) {}
    void ExportDocument(const std::string & path) {}

    void AddObject(ePrimitiveObjectType eObjType) const
    {
        std::shared_ptr<CPrimitiveBase> ptr;
        switch (eObjType)
        {
            case E_POT_CIRCLE:
                ptr = std::make_shared<CPrimitiveCircle>();
                break;
            case E_POT_RECTANGLE:
                ptr = std::make_shared<CPrimitiveRectangle>();
                break;
            case E_POT_TRIANGLE:
                ptr = std::make_shared<CPrimitiveTriangle>();
                break;
        }

        m_pDocument->AddPrimitive(ptr);

        auto data = m_pDocument->GetObjectsList();

        m_pRenderer->Render(data);
    };

    void RemoveObject(uint32_t nObjId) {}

private:
    std::shared_ptr<CDocument> m_pDocument;
    std::shared_ptr<CRenderer> m_pRenderer;
};

#endif //_CONTROLLER_H_
