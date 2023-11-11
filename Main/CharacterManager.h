#pragma once

#define MAX_CHARACTER 300

struct _PATH_t
{
	_PATH_t()
	{
		sizeof(_PATH_t);
	}
	BYTE byte0;
	BYTE byte1;
	BYTE byte2;
	BYTE gap3[15];
	BYTE byte12;
};

struct WEAR_ITEM
{
	WEAR_ITEM()
	{
		sizeof(WEAR_ITEM);
	}
	WORD ObjectID;
	WORD Level;
	WORD NumBones;
	BYTE field_5[13];
	BYTE END;
};

struct CHARACTER	// SIZE = 800
{
	CHARACTER()
	{
		sizeof(CHARACTER);
	}

	BYTE isCreated;
	BYTE byte_1;
	WORD ObjectID;
	DWORD ChangeSkin;
	float BodyScale;
	float BodyOrigin[3];
	float BodyAngle[3];
	BYTE field_24[48];
	DWORD dword_54;
	BYTE field_58[4];
	DWORD dword_5C;
	DWORD dword_60;
	float float_64;
	BYTE field_68[9];
	BYTE byte_71;
	BYTE byte_72;
	BYTE aling_73;
	DWORD dword_74;
	BYTE byte_78;
	BYTE field_79[3];
	BYTE byte_7C;
	BYTE field_7D[63];
	float float_BC;
	float float_C0;
	DWORD dword_C4;
	BYTE field_C8[4];
	BYTE LightEnable;
	BYTE field_CD[7];
	BYTE ConstratEnable;
	BYTE field_D5[3];
	float vEffectColor[3];
	BYTE field_E4[8];
	CHARACTER* lpCharacterTarget;
	BYTE field_F0[5];
	BYTE CurrentAction;
	BYTE OldCurrentAction;
	BYTE byte_F7;
	float ModelSpeedAct;
	float OldModelSpeedAct;
	BYTE byte_100;
	BYTE field_101[3];
	float* pEffectOnBone;
	float float_108;
	float float_10C;
	float float_110;
	float float_114;
	float float_118;
	float float_11C;
	BYTE field_120[48];
	BYTE byte_150;
	BYTE byte_151;
	BYTE field_152[2];
	float float_154;
	float float_158;
	BYTE field_15C[28];
	BYTE Class;
	BYTE byte_179;
	WORD Level;
	BYTE field_17C[24];
	WORD word_194;
	WORD aIndex;
	WEAR_ITEM InventoryWear[11];
	BYTE byte_274;
	BYTE byte_275;
	BYTE byte_276;
	BYTE OnMovePath;
	BYTE field_278[14];
	WORD word_286;
	BYTE Dir;
	BYTE DieAccionCount;
	BYTE byte_28A;
	BYTE aling_28B;
	BYTE byte_28C;
	BYTE field_28D[4];
	BYTE byte_291;
	BYTE OldX;
	BYTE OldY;
	BYTE field_294[24];
	DWORD dword_2AC;
	DWORD dword_2B0;
	DWORD dword_2B4;
	BYTE byte_2B8;
	BYTE field_2B9[3];
	int dword_2BC;
	float float_2C0;
	BYTE field_2C4[4];
	DWORD dword_2C8;
	BYTE field_2CC[14];
	BYTE InSafeZone;
	BYTE isVisivle;
	BYTE byte2DC;
	BYTE field_2DD[3];
	_PATH_t Path_t;
	BYTE field_2F3[33];
	DWORD X;
	DWORD Y;
	DWORD dword31C;
};

class CCharacterManager
{
public:
	CCharacterManager();
	~CCharacterManager();
	int FindCharacterIndex(int aIndex);
	CHARACTER* CreateHero(int index, DWORD Class, BYTE a3, float BodyOriginX, float BodyOriginY, float BodyOriginZ);
	void SetCharacterScale(CHARACTER* lpCharacter);
	inline CHARACTER* GetCharacter(int Slot) { /*DebugMessageBox("Index:%d", Slot);*/ return &this->m_Character[Slot]; }
private:
	CHARACTER m_Character[MAX_CHARACTER];
};

extern CCharacterManager gCharacterManager;