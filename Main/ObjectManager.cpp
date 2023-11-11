#include "stdafx.h"
#include "GameState.h"
#include "MapManager.h"
#include "BMDManager.h"
#include "OperatesManager.h"
#include "ObjectBlockManager.h"
#include "ObjectManager.h"

CObjectManager gObjectManager;

CObjectManager::CObjectManager()
{
	sizeof(CObjectManager);
}

CObjectManager::~CObjectManager()
{

}

CObjectManager* CObjectManager::CreateObject(int ID, vec3_t vecTA2, vec3_t vecTA3, float a4)
{
    int v9 = (int)(vecTA2[0] * 0.000625f);

    int v4 = (int)(vecTA2[1] * 0.000625f);

    if (v9 < 0 || v4 < 0 || v9 >= 16 || v4 >= 16)
    {
        return 0;
    }

    int ObjectBlockID = v4 + 16 * v9;

    CObjectBlockManager* lpObjectBlock = &gObjectBlockManager[ObjectBlockID];

    CObjectManager* lpObject = (CObjectManager*)operator new(sizeof(CObjectManager));

    memset(lpObject, 0, sizeof(CObjectBlockManager));

    if (lpObjectBlock->lpObject1 != NULL)
    {
        lpObjectBlock->lpObject2->lpObject2 = lpObject;

        lpObject->lpObject1 = lpObjectBlock->lpObject2;

        lpObject->lpObject2 = NULL;
    }
    else
    {
        lpObject->lpObject1 = NULL;

        lpObject->lpObject2 = NULL;

        lpObjectBlock->lpObject1 = lpObject;
    }

    lpObjectBlock->lpObject2 = lpObject;

    lpObject->byte_0 = 1;

    lpObject->byte_150 = 0;

    lpObject->byte_151 = 0;

    lpObject->byte_CC = 1;

    lpObject->byte_D4 = 0;

    lpObject->byte_100 = 0;

    lpObject->ID = ID;

    lpObject->float_8 = a4;

    lpObject->float_158 = 1.0f;

    lpObject->float_154 = 1.0f;

    lpObject->float_BC = 0.16f;

    lpObject->float_C4 = 50.0f;

    lpObject->dword_54 = -1;

    lpObject->byte_F5 = 0;

    lpObject->byte_F6 = 0;

    lpObject->float_F8 = 0.0f;

    lpObject->float_FC = 0.0f;

    lpObject->ObjectBlockID = ObjectBlockID;

    lpObject->dword_60 = -1;

    lpObject->float_64 = 1.0f;

    lpObject->float_68 = 0.0f;

    lpObject->float_6C = 0.0f;

    lpObject->byte_71 = 0;

    lpObject->float_C0 = -30.0f;

    lpObject->float_74 = 0.0f;

    lpObject->float_C = vecTA2[0];

    lpObject->float_10 = vecTA2[1];

    lpObject->float_14 = vecTA2[2];

    lpObject->float_18 = vecTA3[0];

    lpObject->float_1C = vecTA3[1];

    lpObject->float_20 = vecTA3[2];

    lpObject->float_108 = -40.0f;

    lpObject->float_10C = -40.0f;

    lpObject->float_D8 = 0.0f;

    lpObject->float_DC = 0.0f;

    lpObject->float_E0 = 0.0f;

    lpObject->float_24 = 0.0f;

    lpObject->float_28 = 0.0f;

    lpObject->float_2C = 0.0f;

    lpObject->float_B0 = 0.0f;

    lpObject->float_B4 = 0.0f;

    lpObject->float_B8 = 0.0f;

    lpObject->float_110 = 0.0f;

    lpObject->float_114 = 40.0f;

    lpObject->float_118 = 40.0f;

    lpObject->float_11C = 80.0f;

    if (SceneFlag == SenceFlag_Login || SceneFlag == 4)
    {
        switch (ID)
        {
        case 60:
            lpObject->float_8 = 0.8f;
            lpObject->float_D8 = 0.2f;
            lpObject->float_DC = 0.2f;
            lpObject->float_E0 = 0.2f;
            lpObject->byte_CC = 1;
            break;
        case BMD_MODEL_INDEX_LOGO_1:
            lpObject->float_8 = 0.044f;
            lpObject->dword_60 = 1;
            lpObject->float_64 = 1.0f;
            lpObject->float_D8 = 1.0f;
            lpObject->float_DC = 1.0f;
            lpObject->float_E0 = 1.0f;
            lpObject->byte_CC = 0;
            break;
        case BMD_MODEL_INDEX_LOGO_2:
            lpObject->float_8 = 0.8f;
            lpObject->dword_60 = 0;
            lpObject->float_64 = 1.0f;
            lpObject->float_D8 = 1.0f;
            lpObject->float_DC = 1.0f;
            lpObject->float_E0 = 1.0f;
        case BMD_MODEL_INDEX_LOGO_3:
            lpObject->float_8 = 0.6f;
            lpObject->dword_60 = 1;
            lpObject->byte_CC = 0;
            break;
        case BMD_MODEL_INDEX_LOGO_4:
            lpObject->float_8 = 3.0f;
            lpObject->dword_60 = 0;
            lpObject->float_D8 = 0.5f;
            lpObject->float_DC = 0.5f;
            lpObject->float_E0 = 0.5f;
            break;
        case 164:
            lpObject->dword_60 = 10;
            lpObject->float_D8 = 1.0f;
            lpObject->float_DC = 1.0f;
            lpObject->float_E0 = 1.0f;
            break;
        default:
            break;
        }
    }

    switch (gMapManager.GetWorld())
    {
    case MAP_ID_LOGIN:
        lpObject->float_108 = -150.0f;
        lpObject->float_10C = -150.0f;
        lpObject->float_110 = 0.0f;
        lpObject->float_114 = 150.0f;
        lpObject->float_118 = 150.0f;
        lpObject->float_11C = 500.0f;
        lpObject->float_BC = (1.0f / lpObject->float_8) * 0.4f;
        break;
    case MAP_ID_LORENCIA:
        if (ID == 59)
        {
            gOperatesManager.CreateOperate(lpObject);
        }
        else if(ID == BMD_MODEL_INDEX_SHIP_1)
        {
            gOperatesManager.CreateOperate(lpObject);
            lpObject->float_114 = 40.0f;
            lpObject->float_118 = 40.0f;
            lpObject->float_11C = 160.0f;
            lpObject->dword_54 = -2;
        }
        break;
    case MAP_ID_DUNGEON:
        lpObject->dword_60 = 0;
        break;
    case MAP_ID_DEVIAS:
        lpObject->dword_60 = 1;
        break;
    case MAP_ID_ARENA:
        if (ID == 39)
        {
            gOperatesManager.CreateOperate(lpObject);
            lpObject->dword_54 = -2;
        }
        break;
    default:
        break;
    }

    return lpObject;
}