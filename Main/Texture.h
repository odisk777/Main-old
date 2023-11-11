#pragma once

#define MAX_TEXTURE 1300

#define TEXTURE_RANGE(x) (((x)<0)?0:((x)>=MAX_TEXTURE)?0:1)

typedef struct my_error_mgr* my_error_ptr;

enum TEXTURE_ID
{
	TEXTURE_ID_FONT_INPUT = 0,
	TEXTURE_ID_FONT = 1,

	TEXTURE_ID_WEBZEN_LOGO = 12,	//SE USA PARA 2 COSAS, EL LOGO Y EL ACCOUNT_NEW CORREGIR CUANDO SE PUEDA
	TEXTURE_ID_BUTTON_0 = 13,
	TEXTURE_ID_BUTTON_1 = 14,
	TEXTURE_ID_TEXT_BOX = 15,
	TEXTURE_ID_NEW_ACCOUNT_1 = 16,
	TEXTURE_ID_NEW_ACCOUNT_2 = 17,
	TEXTURE_ID_BOX = 18,
	TEXTURE_ID_PROGRESS_BACK = 19,
	TEXTURE_ID_PROGRESS = 20,



	TEXTURE_ID_FULL = 1300
};

struct TextureInfo	//SIZE = 48
{
	TextureInfo()
	{
		sizeof(TextureInfo);
	}

	char name[32];
	float width;
	float height;
	BYTE BitMapMul;
	//BYTE gap[3];
	BYTE* pBitmap;

	/*	99b
	char Name[32];		
	float width;			
	float height;		
	BYTE byte_28_Count;	
	GLuint Texture;		
	BYTE LoadCount;		
	BYTE* pColor;*/		
};

struct my_error_mgr
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
	char errorbuf[200];
};

class CTexture
{
public:
	CTexture();
	~CTexture();
	void Save_Image(size_t TCopySize, char* Format, char* path, BYTE* TextureInfo, size_t TextureSize);
	void UnloadTexture(int Index);
	int FindTexture(char* textureName);
	void SetTextureCount(int count);
	inline TextureInfo* GetTexture(int ID) { return &this->m_Texture[ID]; }
private:
	TextureInfo m_Texture[MAX_TEXTURE];
private:
};

extern CTexture gTexture;

static GLuint TextureCount;

static int TextureInit;	//inutilizable, solo se pasa a 0 siempre