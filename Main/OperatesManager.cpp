#include "stdafx.h"
#include "OperatesManager.h"

COperatesManager gOperatesManager;

COperatesManager::COperatesManager()
{
	sizeof(COperatesManager);
}

COperatesManager::~COperatesManager()
{
}

void COperatesManager::CreateOperate(CObjectManager* lpObject)
{
    for (size_t i = 0; i < MAX_OPERATES; i++)
    {
        if (this->m_List[i].isCreated != 0)
        {
            continue;
        }

        this->m_List[i].isCreated = 1;

        this->m_List[i].lpObject = lpObject;

        break;
    }
}