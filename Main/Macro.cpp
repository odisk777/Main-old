#include "stdafx.h"
#include "Macro.h"

CMacro gMacro;

CMacro::CMacro()
{

}

CMacro::~CMacro()
{

}

void CMacro::Load(char* path)
{
    FILE* pFile = fopen(path, "rt");

    if (pFile == NULL)
    {
        return;
    }

    for (size_t i = 0; i < MAX_MACRO; i++)
    {
        char Macro[MAX_MACRO_LEN];

        fscanf(pFile, "%s", Macro);

        this->m_MacroGame[i] = Macro;
    }

    fclose(pFile);
}