#pragma once

enum eSenceFlag
{
	SenceFlag_None = 0,
	SenceFlag_Create_Scene = 1,
	SenceFlag_Login = 2,

	SenceFlag_Test = 8,
};

void Scene(HDC a1);
void WebzenScene(HDC a1);
void MainScene(HDC a1);
void OpenFont();
void OpenBasicData();
void NewMoveLogInScene();
void OpenPlayers();
void OpenCharacterSceneData();


void TestF();


extern float g_Luminosity;
extern float WorldTime;
extern int SceneFlag;

