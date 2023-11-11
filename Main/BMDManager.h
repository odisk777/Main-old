#pragma once
#include "OpenGL.h"

#define MAX_BOUNDING 400

#define MAX_BOUNDING_VERTICES 200

#define MAX_BMD 630	//verificar bien pero parece que es este el size


enum BMD_MODEL_INDEX
{
	BMD_MODEL_INDEX_SHIP_1 = 60,
	

	BMD_MODEL_INDEX_LOGO_1 = 160,
	BMD_MODEL_INDEX_LOGO_2 = 161,
	BMD_MODEL_INDEX_LOGO_3 = 162,
	BMD_MODEL_INDEX_LOGO_4 = 163,

	BMD_MODEL_INDEX_PLAYER = 340,

	BMD_MODEL_INDEX_FULL = 630,
};

struct Vertex_t	//size = 16
{
	Vertex_t()
	{
		sizeof(Vertex_t);
	}

	__int16 Node;
	vec3_t Position;
};

struct Normal_t	//size = 20
{
	Normal_t()
	{
		sizeof(Normal_t);
	}
	__int16 Node;
	vec3_t Normal;
	__int16 BindVertex;
	__int16 padding;
};

struct TexCoord_t	//size = 8
{
	TexCoord_t()
	{
		sizeof(TexCoord_t);
	}
	float TexCoordU;
	float TexCoordV;
};

struct Triangle_t	 //size = 64 - en la 99b copia 32 pero suma 64, habria que ver si es igual aqui!
{
	Triangle_t()
	{
		sizeof(Triangle_t);
	}

	char Polygon;
	__int16 VertexIndex[4];
	__int16 NormalIndex[4];
	__int16 TexCoordIndex[4];
	__int16 EdgeTriangleIndex[4];
	char Front;
	char padding;
	BYTE Field[28];
};

struct TextureScript
{
	char m_bBright;
	char m_bHiddenMesh;
	char m_bStreamMesh;
	char m_bNoneBlendMesh;
	char m_byShadowMesh;
};

struct Mesh_t	//size = 36
{
	Mesh_t()
	{
		sizeof(Mesh_t);
	}

	//char NoneBlendMesh; //99B+
	__int16 Texture;
	__int16 NumVertices;
	__int16 NumNormals;	
	__int16 NumTexCoords;
	__int16 NumTriangles;	
	__int16 NumCommandBytes;	
	BYTE Aling[4];
	Vertex_t* Vertices;	
	Normal_t* Normals;	
	TexCoord_t* TexCoords;	
	Triangle_t* Triangles;
	unsigned __int8* CommandBytes;
	//TextureScript* m_csTScript;
};

struct struct_lpMesh
{
	struct_lpMesh()
	{
		sizeof(struct_lpMesh);
	}

	WORD word0;
	__int16 int162;
	__int16 int164;
	__int16 int166;
	__int16 int168;
	__declspec(align(8)) void* pvoid10;
	void* pvoid14;
	DWORD dword18;
	void* pvoid1C;
};

struct BoneMatrix_t		//SIZE = 8
{
	BoneMatrix_t()
	{
		sizeof(BoneMatrix_t);
	}
	vec3_t* Position;
	vec3_t* Rotation;
	//vec3_t* Quaternion; //99b+
};

struct Bone_t	//size = 140
{
	Bone_t()
	{
		sizeof(Bone_t);
	}
	char Name[32];
	__int16 Parent;
	char Dummy;
	BoneMatrix_t* BoneMatrixes;
	char BoundingBox;
	vec3_t BoundingVertices[8];
};

struct Action_t	//size = 16
{
	Action_t()
	{
		sizeof(Action_t);
	}

	char Loop;
	float PlaySpeed;
	__int16 NumAnimationKeys;
	char LockPositions;
	vec3_t* Positions;
};

struct Texture_t
{
	char FileName[32];
};

struct BMD	// size == 184
{
	char Name[32];
	BYTE Version;
	WORD NumBones;
	WORD NumMeshs;
	WORD NumActions;
	Mesh_t* lpMeshs;
	Bone_t* lpBones;
	Action_t* lpActions;
	Texture_t* lpTextures;
	WORD* lpIndexTexture;
	short NumLightMaps;
	short IndexLightMap;
	int LightMaps;
	bool LightEnable;
	bool ConstratEnable;
	vec3_t BodyLight;
	int BoneHead;
	int BoneFoot[4];
	float BodyScale;
	vec3_t BodyOrigin;
	vec3_t BodyAngle;
	float BodyHeight;
	char StreamMesh;
	vec3_t ShadowAngle;
	char Skin;
	bool HideSkin;
	float Velocity;
	BYTE CurrentAction;
	BYTE PriorAction;
	float CurrentAnimation;
	WORD CurrentAnimationFrame;
	WORD Sounds[5];
	int renderCount;
};

class CBMDManager	// size == 184
{
public:
	CBMDManager();
	~CBMDManager();
	void Init(BYTE Mode);
	bool Open(char* path, char* modelname);
	void CreateBoundingBox();
public:
	char Name[32];
	BYTE Version;
	WORD NumBones;
	WORD NumMeshs;
	WORD NumActions;
	Mesh_t* lpMeshs;
	Bone_t* lpBones;
	Action_t* lpActions;
	Texture_t* lpTextures;
	WORD* lpIndexTexture;
	short NumLightMaps;
	short IndexLightMap;
	int LightMaps;
	bool LightEnable;
	bool ConstratEnable;
	vec3_t BodyLight;
	int BoneHead;
	int BoneFoot[4];
	float BodyScale;
	vec3_t BodyOrigin;
	vec3_t BodyAngle;
	float BodyHeight;
	char StreamMesh;
	vec3_t ShadowAngle;
	char Skin;
	bool HideSkin;
	float Velocity;
	BYTE CurrentAction;
	BYTE PriorAction;
	float CurrentAnimation;
	WORD CurrentAnimationFrame;
	WORD Sounds[5];
	int renderCount;
};

extern CBMDManager gBMDManager[MAX_BMD];

static vec3_t BoundingMin[MAX_BOUNDING];

static vec3_t BoundingMax[MAX_BOUNDING];

static WORD BoundingVertices[MAX_BOUNDING_VERTICES];