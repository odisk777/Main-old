#include "stdafx.h"
#include "CharacterMachine.h"
#include "CharacterManager.h"

CCharacterManager gCharacterManager;

CCharacterManager::CCharacterManager()
{

}

CCharacterManager::~CCharacterManager()
{

}

int CCharacterManager::FindCharacterIndex(int aIndex)
{
    for (size_t i = 0; i < MAX_CHARACTER; i++)
    {
        if (this->m_Character[i].isCreated == 0 || this->m_Character[i].aIndex != aIndex)
        {
            continue;
        }

        return i;
    }

    return MAX_CHARACTER;
}

CHARACTER* CCharacterManager::CreateHero(int index, DWORD Class, BYTE a3, float BodyOriginX, float BodyOriginY, float BodyOriginZ)
{
    CHARACTER* lpCharacter = &this->m_Character[index];

    //CreateCharacterPointer(lpCharacter, 340, 0, 0, BodyOriginZ);

    lpCharacter->BodyOrigin[0] = BodyOriginX;

    lpCharacter->vEffectColor[0] = 0.3f;

    lpCharacter->vEffectColor[1] = 0.3f;

    lpCharacter->vEffectColor[2] = 0.3f;

    lpCharacter->BodyOrigin[1] = BodyOriginY;

    lpCharacter->byte_179 = a3;

    lpCharacter->InventoryWear[1].ObjectID = Class + 606;

    lpCharacter->InventoryWear[2].ObjectID = Class + 610;

    lpCharacter->InventoryWear[3].ObjectID = Class + 614;

    lpCharacter->InventoryWear[4].ObjectID = Class + 618;

    lpCharacter->aIndex = index;

    lpCharacter->Class = Class;

    lpCharacter->InventoryWear[5].ObjectID = Class + 622;

    lpCharacter->InventoryWear[6].ObjectID = -1;

    lpCharacter->InventoryWear[7].ObjectID = -1;

    lpCharacter->InventoryWear[8].ObjectID = -1;

    lpCharacter->InventoryWear[9].ObjectID = -1;

    switch (Class)
    {
    case 4:
        lpCharacter->InventoryWear[8].ObjectID = 363;
        lpCharacter->InventoryWear[6].ObjectID = 423;
        lpCharacter->Class = 1;
        break;
    case 5:
        lpCharacter->InventoryWear[8].ObjectID = 543;
        lpCharacter->InventoryWear[9].ObjectID = 559;
        lpCharacter->InventoryWear[6].ObjectID = 356;
        lpCharacter->InventoryWear[7].ObjectID = 356;
        lpCharacter->Class = 1;
        break;
    case 6:
        lpCharacter->InventoryWear[8].ObjectID = 544;
        lpCharacter->InventoryWear[6].ObjectID = 431;
        lpCharacter->Class = 1;
        break;
    case 9:
        lpCharacter->InventoryWear[6].ObjectID = 373;
        lpCharacter->Class = 1;
        break;
    case 10:
        lpCharacter->InventoryWear[8].ObjectID = 354;
        lpCharacter->InventoryWear[6].ObjectID = 354;
        lpCharacter->Class = 1;
        break;
    case 11:
        lpCharacter->InventoryWear[6].ObjectID = 407;
        lpCharacter->Class = 1;
        break;
    case 12:
        lpCharacter->InventoryWear[7].ObjectID = 418;
        lpCharacter->Class = 1;
        break;
    case 13:
        lpCharacter->InventoryWear[6].ObjectID = 408;
        lpCharacter->Class = 1;
        break;
    }

    if (Class >= 4)
    {
        lpCharacter->Class = 1;
    }

    this->SetCharacterScale(lpCharacter);

    //SetPlayerStop(lpCharacter);

    return lpCharacter;
}

void CCharacterManager::SetCharacterScale(CHARACTER* lpCharacter)
{
    if (lpCharacter->isVisivle == 0)
    {
        return;
    }

    int ObjectID = lpCharacter->InventoryWear[1].ObjectID;

    if (ObjectID == 462 || ObjectID == 464 || ObjectID >= 472 && ObjectID <= 475)
    {
        lpCharacter->InventoryWear[0].ObjectID = lpCharacter->Class + 606;
    }
    else
    {
        lpCharacter->InventoryWear[0].ObjectID = -1;
    }

    switch (lpCharacter->Class)
    {
        case CLASS_DW:
        case CLASS_DK:
            lpCharacter->BodyScale = 0.9f;
            break;
        case CLASS_FE:
            lpCharacter->BodyScale = 0.88f;
            break;
        case CLASS_MG:
            lpCharacter->BodyScale = 0.95f;
            break;
        default:
            return;
    }

}

