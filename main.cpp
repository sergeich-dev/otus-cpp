#include <iostream>
#include "editor/controller/controller.h"

void onCreateDocument(CController * pController)
{
    pController->CreateDocument();
}

void onImportDocument(CController * pController, const std::string & path)
{
    pController->ImportDocument(path);
}

void onExportDocument(CController * pController, const std::string & path)
{
    pController->ExportDocument(path);
}

void onCreatePrimitive(CController * pController, ePrimitiveObjectType eObjType)
{
    pController->AddObject(eObjType);
}
void onRemovePrimitive(CController * pController, uint32_t nObjId)
{
    pController->RemoveObject(nObjId);
}

int main()
{
    try
    {
        CController controller;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
