#include "stdafx.h"
#include "OpenGL.h"
#include "Texture.h"
#include "Path.h"
#include "Util.h"
#include "Main.h"
#include "MapManager.h"
#include "BMDManager.h"
#include "ObjectManager.h"
#include "CharacterManager.h"
#include "InterfaceManager.h"
#include "GameState.h"

float g_Luminosity;

float WorldTime;

int SceneFlag = SenceFlag_Create_Scene;

void Scene(HDC a1)
{
    g_Luminosity = sin(WorldTime * 0.0040000002) * 0.15000001 + 0.60000002; /*#Need Real Values*/

    switch (SceneFlag)
    {
        case SenceFlag_Create_Scene:
            WebzenScene(a1);
            break;
        /*case 3:
            LoadingScene(a1);
            break;*/
        case SenceFlag_Login:
        //case 4:
        //case 5:
            MainScene(a1);
            break;
        case SenceFlag_Test:
            TestF();
            break;
        default:
            break;
    }

    if (g_iNoMouseTime > 79)
    {
        KillGLWindow();
    }
}

void WebzenScene(HDC a1)
{
    //hacer una funcion para limpiar todas dentro de la clase!

    for (size_t i = 0; i < MAX_TEXTURE; i++)
    {
        memset(gTexture.GetTexture(i), 0x00, sizeof(gTexture.GetTexture(i)));
    }

    OpenFont();

    //sub_426F20();                                 // ClearInput???

    //MessageBox(NULL, "???", NULL, MB_OK);

    gInterfaceManager.LoadImageJpg("logo\\Webzenlogo.jpg", TEXTURE_ID_WEBZEN_LOGO, GL_NEAREST, GL_CLAMP, NULL, true);

    FogEnable = 0;

    BeginOpengl(0, 0, 640, 480);

    glClear(GL_COLOR_BUFFER_BIT);

    BeginBitmap();

    glColor3f(1.0f, 1.0f, 1.0f);

    float PosY = WindowWidth * 0.375 - 97.5;

    float PosX = WindowWidth * 0.5 - 128.0;

    gInterfaceManager.RenderBitmap(TEXTURE_ID_WEBZEN_LOGO, PosX, PosY, 256.0, 195.0, 0, 0, 1.0, 0.76171875, 0, 0.0);

    if (byte_81C1648 == 1)
    {
        SelectObject(glHdc, g_hFont);

        //RenderText(0, 0, "male version.", 0, 0, 0);
    }

    pGLPopMatrix();

    pGLMatrixExit();

    glFlush();

    SwapBuffers(a1);

    gTexture.UnloadTexture(TEXTURE_ID_WEBZEN_LOGO);

    if (byte_81C1648 == 1)  //offline mode?
    {
       /* SceneFlag = 5;
        byte_81C4979 = 1;
        OpenBasicData();
        OpenWorld(World);
        HeroKey = 0;
        v3 = sub_41B810(0, 0, 0, 1183493120, 1176307712, 0);    //create player obj?
        *(_DWORD*)(v3 + 788) = 177;
        *(_DWORD*)(v3 + 792) = 100;*/
    }
    else
    {
        SceneFlag = SenceFlag_Login;

        OpenBasicData();
    }

    //SceneFlag = SenceFlag_Test;
}

void MainScene(HDC a1)
{
    /*DWORD v1; // edi
    char v2; // bl
    int i; // eax
    bool v4; // zf
    signed int v5; // eax
    int v6; // ecx
    int v7; // eax
    int v8; // [esp-4h] [ebp-184h]
    char buffer[100]; // [esp+1Ch] [ebp-164h] BYREF
    char buffer2[256]; // [esp+80h] [ebp-100h] BYREF*/

    //CalcFPS();

    while (TimeCurrent >= 40)
    {
       // sub_4501A0(); //proc 

        switch (SceneFlag)
        {
            case SenceFlag_Login:
                NewMoveLogInScene();
                break;
            /*case 4:
                NewMoveCharacterScene();
                break;
            case 5:
                MoveMainScene();
                break;*/
        }

        /*sub_427760();

        sub_427C00();

        if (PressKey(44) == true)
        {
            GrabEnable = GrabEnable == false;
        }*/

        if (ChatTime > 0)
        {
            ChatTime--;
        }

        if (MacroTime > 0)
        {
            MacroTime--;
        }

        WaterTextureNumber = (WaterTextureNumber + 1) % 32;

        int TMoveSceneFrame = MoveSceneFrame;

        TimeCurrent -= 40;

        MoveSceneFrame++;

        //sprintf(buffer, "%d", TMoveSceneFrame);
    }

    if (Destroy == 1)
    {
        return;
    }

    //Set3DSoundPosition();

    /*if (GrabEnable == true)
    {
        _SYSTEMTIME SystemTime;

        GetLocalTime(&SystemTime);

        sprintf(GrabFileName, "Screen(%02d_%02d-%02d_%02d)-%04d.jpg", SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, GrabScreen);

        sprintf(buffer2, m_TextGame[459], GrabFileName, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute);

        sub_4279C0(&byte_54CA6CC, buffer2, 1);
    }*/

    DWORD TNowTime = GetTickCount();    //TimeCurrent

    bool FlagRefresh = false;

    switch (SceneFlag)
    {
        /*case SenceFlag_Login:
            FlagRefresh = NewRenderLogInScene();
            break;*/
        /*case 4:
            FlagRefresh = NewRenderCharacterScene();
            break;
        case 5:
            FlagRefresh = RenderMainScene();
            break;*/
    }

    /*if (GrabEnable == 1)
    {
        GrabEnable = 0;

        if (byte_81C1648)
        {
            SaveWorld(World);
        }

        SaveScreen();
    }*/

    if (FlagRefresh == true)
    {
        glFlush();

        SwapBuffers(a1);
    }

    int i = 0;

    for (i = GetTickCount() - TNowTime; i < 40; i = GetTickCount() - TNowTime)
        ;

    TimeCurrent += i;

   /* if (EnableSocket && SceneFlag == 5 && CWsctlc::GetSocket(&SocketClient) == -1)
    {
        dword_81C498C = 113;
    }*/

    if (SceneFlag == SenceFlag_Login)
    {
        //PlayMp3(off_48290C);
    }

    if (SceneFlag != 5)
    {
        return;
    }

    return;

    /*

    switch (World)
    {
    case 0:
        if (HeroTile == 4)
        {
            StopBuffer(0, 1);
            StopBuffer(1, 1);
        }
        else
        {
            PlayBuffer(0, 0, 1);
            if (dword_7B785B4 > 0)
                PlayBuffer(1, 0, 1);
        }
        break;
    case 1:
        PlayBuffer(3, 0, 1);
        break;
    case 2:
        if (HeroTile == 3 || HeroTile >= 10)
            StopBuffer(0, 1);
        else
            PlayBuffer(0, 0, 1);
        break;
    case 3:
        PlayBuffer(0, 0, 1);
        v5 = rand() & 0x800001FF;
        v4 = v5 == 0;
        if (v5 < 0)
            v4 = (((_WORD)v5 - 1) | 0xFFFFFE00) == -1;
        if (v4)
            PlayBuffer(2, 0, 0);
        break;
    case 4:
        PlayBuffer(5, 0, 1);
        break;
    case 5:
        PlayBuffer(7, 0, 1);
        break;
    case 7:
        PlayBuffer(6, 0, 1);
        break;
    default:
        break;
    }
    if (World)
    {
        StopBuffer(0, 1);
        StopBuffer(1, 1);
    }
    if (World != 1)
        StopBuffer(3, 1);
    if (World != 2)
        StopBuffer(0, 1);
    if (World != 3)
    {
        StopBuffer(0, 1);
        StopBuffer(2, 1);
    }
    if (World != 4)
        StopBuffer(5, 1);
    if (World != 7)
        StopBuffer(6, 1);
    if (World)
    {
        StopMp3(g_lpszMp3);
        StopMp3(off_48290C);
    }
    else
    {
        if (!Hero->InSafeZone)
        {
        LABEL_82:
            StopMp3(off_482910);
            StopMp3(off_482914);
            goto LABEL_83;
        }
        if (HeroTile == 4)
            PlayMp3(g_lpszMp3);
        else
            PlayMp3(off_48290C);
    }
    if (World != 2)
        goto LABEL_82;
    if (!Hero->InSafeZone)
        goto LABEL_86;
    v6 = Hero->X;
    if (v6 < 205 || v6 > 214 || (v7 = Hero->Y, v7 < 13) || v7 > 31)
        PlayMp3(off_482914);
    else
        PlayMp3(off_482910);
LABEL_83:
    if (World == 3)
    {
        if (!Hero->InSafeZone)
        {
        LABEL_89:
            StopMp3(off_48291C);
            return;
        }
        PlayMp3(off_482918);
        goto LABEL_87;
    }
LABEL_86:
    StopMp3(off_482918);
LABEL_87:
    if (World != 1 && World != 5)
        goto LABEL_89;
    PlayMp3(off_48291C);

    */
}

void TestF()
{
    BeginOpengl(0, 0, 640, 480);

    glClear(GL_COLOR_BUFFER_BIT);

    BeginBitmap();

    glColor3f(1.0f, 1.0f, 1.0f);

    float PosY = WindowWidth * 0.375 - 97.5;

    float PosX = WindowWidth * 0.5 - 128.0;

    gInterfaceManager.RenderBitmap(TEXTURE_ID_WEBZEN_LOGO, PosX, PosY, 256.0, 195.0, 0, 0, 1.0, 0.76171875, 0, 0.0);
}

void OpenFont()
{
    gPath.InitPath();
    
    gInterfaceManager.LoadImageTga("Interface\\FontInput.tga", TEXTURE_ID_FONT_INPUT, GL_NEAREST, GL_CLAMP, NULL, true);

    gInterfaceManager.LoadImageTga("Interface\\Font.tga", TEXTURE_ID_FONT, GL_NEAREST, GL_CLAMP, NULL, true);
}

void OpenBasicData()
{
    /*gInterfaceManager.LoadImageTga(aInterfaceCurso, 2u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_0, 3u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_1, 4u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_2, 5u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_3, 6u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_4, 7u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_5, 8u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_6, 9u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceCur_7, 0xAu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMenu0, 0xE6u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMen_0, 0xE7u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMen_1, 0xE8u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aInterfaceMen_2, 0xE9u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMenu_, 0xEAu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMen_3, 0xEBu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMen_4, 0xECu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMen_5, 0xEDu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMen_6, 0xEEu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceDialo, 0xEFu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMessa, 0xF0u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceOk_jp, 0xF1u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceOk2_j, 0xF2u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceCance, 0xF3u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceCan_0, 0xF4u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceLevel, 0xF5u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceLev_0, 0xF6u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceMen_7, 0xF7u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceDia_0, 0xF8u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceDia_1, 0xF9u, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aInterfaceGuild, 0xFAu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectFire01_j, 0x479u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectFire02_j, 0x47Au, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectFlame01_, 0x47Eu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectFlare01_, 0x44Cu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectMagic_gr, 0x4BBu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectMagic_ci, 0x4BCu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectSpark02_, 0x465u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectSpark03_, 0x466u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectSmoke01_, 0x492u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aEffectSmoke02_, 0x493u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aEffectBlood01_, 0x483u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageTga(aEffectBlood_tg, 0x484u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectExplotio, 0x48Du, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectShiny01_, 0x49Cu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectShiny02_, 0x49Du, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectShiny03_, 0x49Eu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectEye01_jp, 0x49Fu, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectChrome01, 0x460u, GL_LINEAR, GL_REPEAT, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectBlur01_j, 0x45Bu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectBab2_jpg, 0x461u, GL_LINEAR, GL_REPEAT, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectMotion_b, 0x45Cu, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectMotion_0, 0x45Du, GL_NEAREST, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectLightnin, 0x475u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectThunder0, 0x46Au, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectSpark01_, 0x4B6u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectJointthu, 0x4B4u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectJointspi, 0x4B3u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectJointlas, 0x4B7u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectJointene, 0x4B8u, GL_LINEAR, GL_CLAMP, 0, 1);
    gInterfaceManager.LoadImageJpg(aEffectJointl_0, 0x4BAu, GL_LINEAR, GL_REPEAT, 0, 1);
    
    
    */

     OpenPlayers();

     /*
      OpenPlayerTextures();
      OpenItems();
      OpenItemTextures();
      OpenSkills();
      OpenImages();
      OpenSounds();
      if ( LoadDataType == 1)
      {
        sub_425960(aDataItemItem_b);
        sub_4253B0(aDataSkillSkill);
        sub_424E80(aDataGate_bmd);
        sub_424BC0(aDataFilter_bmd);
      }
      else
      {
       /* sprintf(v0, "Data2\\item(%s).txt", Language);
        sub_425460(v0);
        OpenItemScript(aDataItemItem_b);
        sprintf(v0, "Data2\\skill(%s).txt", Language);
        sub_424F00(v0);
        OpenSkillScript(aDataSkillSkill);
        sub_424CA0(aData2Gate_txt);
        OpenGateScript(aDataGate_bmd);
        sub_424AF0(aData2Filter_tx);
        OpenFilterFile(aDataFilter_bmd);
        }
    
   */

    /*
    sprintf(v0, "Data\\NpcName(%s).txt", Language);
    OpenMonsterScript(v0);
    if ( byte_81C1648 )
      sub_4266B0(aData2Monsterse);
    LoadWaveFile(4, aDataSoundItitl, 1, 0);
    LoadWaveFile(27, aDataSoundIbutt, 2, 0);
    LoadWaveFile(25, aDataSoundIbu_0, 1, 0);
    LoadWaveFile(26, aDataSoundIbu_1, 1, 0);
    LoadWaveFile(28, aDataSoundIcrea, 1, 0);

      */
}

void NewMoveLogInScene()
{
    if (InitLogIn == false)
    {
        InitLogIn = TRUE;

        gMapManager.SetWorld(MAP_ID_LOGIN);

        CurrentProtocolState = 0;

        //CreateSocket(szServerIpAddress, g_ServerPort);

        EnableSocket = true;

        ServerListCount = 0;

        OpenCharacterSceneData();

        for (size_t i = 0; i < 7; i++)
        {
            gCharacterManager.GetCharacter(i)->float_158 = 0.0f;
        }
  
        vec3_t Vect_2 = { 0.0f,0.0f,0.0f };

        vec3_t Vect_1 = { 0.0f,-520.0f,0.0f };

        gObjectManager.CreateObject(BMD_MODEL_INDEX_LOGO_1, Vect_1, Vect_2, 1.0f);

        Vect_2[0] = 0.0f; Vect_2[1] = 0.0f; Vect_2[2] = 180.0f;

        Vect_1[0] = -700.0f; Vect_1[1] = 700.0f; Vect_1[2] = 0.0f;

        gObjectManager.CreateObject(BMD_MODEL_INDEX_SHIP_1, Vect_1, Vect_2, 1.0f);

        gObjectManager.CreateObject(BMD_MODEL_INDEX_LOGO_2, Vect_1, Vect_2, 1.0f);

        Vect_2[0] = 0.0f; Vect_2[1] = 0.0f; Vect_2[2] = 180.0f;

        Vect_1[0] = 400.0f; Vect_1[1] = 400.0f; Vect_1[2] = 0.0f;

        gObjectManager.CreateObject(BMD_MODEL_INDEX_SHIP_1, Vect_1, Vect_2, 1.0f);

        gObjectManager.CreateObject(BMD_MODEL_INDEX_LOGO_2, Vect_1, Vect_2, 1.0f);

        Vect_2[0] = 0.0f; Vect_2[1] = 0.0f; Vect_2[2] = 180.0f;

        Vect_1[0] = -200.0f; Vect_1[1] = -400.0f; Vect_1[2] = 0.0f;

        gObjectManager.CreateObject(BMD_MODEL_INDEX_SHIP_1, Vect_1, Vect_2, 1.0f);

        gObjectManager.CreateObject(161, Vect_1, Vect_2, 1.0f);

        Vect_2[0] = 0.0f; Vect_2[1] = 0.0f; Vect_2[2] = 0.0f;

        Vect_1[0] = 0.0f; Vect_1[1] = -600.0f; Vect_1[2] = 480.0f;

        gObjectManager.CreateObject(162, Vect_1, Vect_2, 1.0f);

        Vect_2[0] = 0.0f; Vect_2[1] = 0.0f; Vect_2[2] = 0.0f;

        Vect_1[0] = -110.0f; Vect_1[1] = 1600.0f; Vect_1[2] = 50.0f;

        gObjectManager.CreateObject(BMD_MODEL_INDEX_LOGO_4, Vect_1, Vect_2, 1.0f);

        gCharacterManager.CreateHero(1, 1, 0, 0.0, 0.0, 0);

        CHARACTER* lpCharacter = gCharacterManager.GetCharacter(1);

        lpCharacter->BodyScale = 0.6f;
        lpCharacter->BodyAngle[0] = 0.0f;
        lpCharacter->BodyAngle[1] = 0.0f;
        lpCharacter->BodyAngle[2] = 180.0f;
        lpCharacter->BodyOrigin[0] = -200.0f;
        lpCharacter->BodyOrigin[1] = -750.0f;
        lpCharacter->BodyOrigin[2] = 250.0f;

        gCharacterManager.CreateHero(2, 0, 0, 0.0, 0.0, 0);

        lpCharacter = gCharacterManager.GetCharacter(2);

        lpCharacter->BodyScale = 0.6f;
        lpCharacter->BodyAngle[0] = 0.0f;
        lpCharacter->BodyAngle[1] = 0.0f;
        lpCharacter->BodyAngle[2] = 180.0f;
        lpCharacter->BodyOrigin[0] = -240.0f;
        lpCharacter->BodyOrigin[1] = -770.0f;
        lpCharacter->BodyOrigin[2] = 250.0f;

        gCharacterManager.CreateHero(3, 2, 0, 0.0, 0.0, 0);

        lpCharacter = gCharacterManager.GetCharacter(3);

        lpCharacter->BodyScale = 0.6f;
        lpCharacter->BodyAngle[0] = 0.0f;
        lpCharacter->BodyAngle[1] = 0.0f;
        lpCharacter->BodyAngle[2] = 180.0f;
        lpCharacter->BodyOrigin[0] = 400.0f;
        lpCharacter->BodyOrigin[1] = 50.0f;

        lpCharacter->BodyOrigin[2] = 250.0f;

        /*CreateBug(558, lpCharacter->BodyOrigin, lpCharacter, 0);

        dword_81C497C = 0;
        dword_81C4980 = 0;
        dword_4829E0 = 480;
        dword_4829E4 = -200;
        dword_4829D4 = -1;
        dword_4829D8 = -1;
        dword_81C499C = 0;
        byte_7C41CEF = 0;
        byte_7C41CF0 = 0;
        byte_7C41CF1 = 0;
        byte_47CEB8 = 1;
        sub_426F20();
        dword_47CEBC = 2;
        BYTE1(dword_7C41368) = 1;
        strcpy(dword_7BE8BC0, m_ID);
        v3 = strlen(dword_7BE8BC0) + 1;
        v4 = 120;
        dword_7BA8558[0] = v3 - 1;
        dword_7C41CF8 = v3 != 1;

        do
        {
            sub_4279C0(&byte_54CA6CC, &byte_54CA6CC, 0);
            --v4;
        } while (v4);

        if (!Hero)
        {
            MEMORY[0xC] = 0;                          // Hero->BodyOrigin[0]=0.0f
            Hero->BodyOrigin[1] = 0.0;
            Hero->BodyOrigin[2] = 0.0;
        }

        CameraPosition[0] = 0.0;
        CameraPosition[1] = 0.0;
        CameraPosition[2] = 0.0;

        CameraAngle[0] = 0.0;
        CameraAngle[1] = 0.0;
        CameraAngle[2] = 0.0;

        v5 = &dword_482938[6 * dword_81C4994];
        dword_81C4950 = *v5;
        v6 = &dword_48292C[6 * dword_81C4994];
        v7 = v5[1];
        v8 = v5[2];
        dword_81C4954 = v7;
        v9 = *v6;
        dword_81C4958 = v8;
        v10 = v6[1];
        dword_81C1828 = v9;
        v11 = v6[2];
        dword_482928 = -1;
        dword_81C182C = v10;
        dword_81C1830 = v11;*/
    }

}

void OpenPlayers()
{
    gInterfaceManager.AccessModel(BMD_MODEL_INDEX_PLAYER, "Data\\Player\\", "Player", -1);

    if (gBMDManager[BMD_MODEL_INDEX_PLAYER].NumMeshs > 0)
    {
        MessageBox(g_pnpGL, "Player.bmd file error!!!", 0, 0);

        SendMessage(g_pnpGL, WM_DESTROY, 0, 0);
    }

    /*
    v3 = 1;
    do
    {
        AccessModel(v3 + 605, aDataPlayer, aHelmclass, v3);
        AccessModel(v3 + 609, aDataPlayer, aArmorclass, v3);
        AccessModel(v3 + 613, aDataPlayer, aPantclass, v3);
        AccessModel(v3 + 617, aDataPlayer, aGloveclass, v3);
        AccessModel(v3 + 621, aDataPlayer, aBootclass, v3);
        ++v3;
    } while (v3 - 1 < 4);
    v4 = 1;
    do
    {
        AccessModel(v4 + 461, aDataPlayer, aHelmmale, v4);
        AccessModel(v4 + 477, aDataPlayer, aArmormale, v4);
        AccessModel(v4 + 493, aDataPlayer, aPantmale, v4);
        AccessModel(v4 + 509, aDataPlayer, aGlovemale, v4);
        AccessModel(v4 + 525, aDataPlayer, aBootmale, v4);
        ++v4;
    } while (v4 - 1 < 10);
    v5 = 1;
    do
    {
        AccessModel(v5 + 471, aDataPlayer, aHelmelf, v5);
        AccessModel(v5 + 487, aDataPlayer, aArmorelf, v5);
        AccessModel(v5 + 503, aDataPlayer, aPantelf, v5);
        AccessModel(v5 + 519, aDataPlayer, aGloveelf, v5);
        AccessModel(v5 + 535, aDataPlayer, aBootelf, v5);
        ++v5;
    } while (v5 - 1 < 5);
    AccessModel(493, aDataPlayer, aArmormale, 16);
    AccessModel(509, aDataPlayer, aPantmale, 16);
    AccessModel(525, aDataPlayer, aGlovemale, 16);
    AccessModel(541, aDataPlayer, aBootmale, 16);
    AccessModel(341, aDataPlayer, aShadow, 1);
    BMD_LIST[340].BoneHead = 20;
    BMD_LIST[340].BoneFoot[0] = 6;
    BMD_LIST[340].BoneFoot[1] = 13;
    for (i = 1; i <= 12; BMD_LIST[340].lpAnimation[i - 1].SpeedAnimation = 0.28)
        ++i;
    for (j = 13; j <= 33; BMD_LIST[340].lpAnimation[j - 1].SpeedAnimation = 0.30000001)
        ++j;
    BMD_LIST[340].lpAnimation[21].SpeedAnimation = 0.34999999;
    v8 = 34;
    BMD_LIST[340].lpAnimation[29].SpeedAnimation = 0.34999999;
    do
        BMD_LIST[340].lpAnimation[v8++].SpeedAnimation = 0.46000001;
    while (v8 <= 60);
    for (k = 46; k <= 49; BMD_LIST[340].lpAnimation[k - 1].SpeedAnimation = 0.5)
        ++k;
    for (l = 54; l <= 55; BMD_LIST[340].lpAnimation[l - 1].SpeedAnimation = 0.5)
        ++l;
    for (m = 61; m <= 65; BMD_LIST[340].lpAnimation[m - 1].SpeedAnimation = 0.36000001)
        ++m;
    for (n = 66; n <= 69; BMD_LIST[340].lpAnimation[n - 1].SpeedAnimation = 0.38)
        ++n;
    for (ii = 70; ii <= 105; BMD_LIST[340].lpAnimation[ii - 1].SpeedAnimation = 0.31999999)
        ++ii;
    for (jj = 106; jj <= 107; BMD_LIST[340].lpAnimation[jj - 1].SpeedAnimation = 0.44999999)
        ++jj;
    for (kk = 108; kk < 116; BMD_LIST[340].lpAnimation[kk - 1].SpeedAnimation = 0.40000001)
        ++kk;
    BMD_LIST[340].lpAnimation[60].SpeedAnimation = 0.36000001;
    BMD_LIST[340].lpAnimation[3].SpeedAnimation = 0.25999999;
    BMD_LIST[340].lpAnimation[4].SpeedAnimation = 0.23999999;
    BMD_LIST[340].lpAnimation[5].SpeedAnimation = 0.23999999;
    BMD_LIST[340].lpAnimation[7].SpeedAnimation = 0.22;
    BMD_LIST[340].lpAnimation[8].SpeedAnimation = 0.22;
    BMD_LIST[340].lpAnimation[58].SpeedAnimation = 0.28;
    BMD_LIST[340].lpAnimation[68].SpeedAnimation = 0.34999999;
    BMD_LIST[340].lpAnimation[105].SpeedAnimation = 0.40000001;
    BMD_LIST[340].lpAnimation[89].SpeedAnimation = 0.28;
    BMD_LIST[340].lpAnimation[90].SpeedAnimation = 0.28;
    BMD_LIST[340].lpAnimation[112].SpeedAnimation = 0.2;
    BMD_LIST[340].lpAnimation[113].SpeedAnimation = 0.2;
    BMD_LIST[340].lpAnimation[106].NoRepeat = 1;
    BMD_LIST[340].lpAnimation[107].NoRepeat = 1;
    BMD_LIST[340].lpAnimation[104].NoRepeat = 1;

    */
}

void OpenCharacterSceneData()
{
    return;


    gInterfaceManager.LoadImageTga("Logo\\0Account_new.tga", TEXTURE_ID_WEBZEN_LOGO, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageJpg("Logo\\0On_Botton.jpg", TEXTURE_ID_BUTTON_0, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageJpg("Logo\\0On_Botton2.jpg", TEXTURE_ID_BUTTON_1, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageJpg("Logo\\0Text_Box.jpg", TEXTURE_ID_TEXT_BOX, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageTga("Logo\\0New_Account01.tga", TEXTURE_ID_NEW_ACCOUNT_1, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageTga("Logo\\0New_Account02.tga", TEXTURE_ID_NEW_ACCOUNT_2, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageJpg("Logo\\0Box.jpg", TEXTURE_ID_BOX, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageJpg("Interface\\Progress_Back.jpg", TEXTURE_ID_PROGRESS_BACK, GL_NEAREST, GL_CLAMP, 0, 1);

    gInterfaceManager.LoadImageJpg("Interface\\Progress.jpg", TEXTURE_ID_PROGRESS, GL_NEAREST, GL_CLAMP, 0, 1);

    /*if (LoadDataType == 0)
    {
        sub_4461D0(60, aData2Object1, aShip_smd);
        sub_4461D0(160, aData2Logo, aSC_smd);
        sub_4461D0(161, aData2Logo, aSC2_smd);
        sub_4461D0(162, aData2Logo, aMu_smd);
        sub_4461D0(163, aData2Logo, aSun_smd);
    }*/

    gInterfaceManager.AccessModel(BMD_MODEL_INDEX_SHIP_1, "Data\\Object1\\", "Ship", 1);

    for (int i = 0; i < 4; i++)
    {
        gInterfaceManager.AccessModel(BMD_MODEL_INDEX_LOGO_1 + i, "Data\\Logo\\", "Logo", i + 1);
    }

    gTexture.SetTextureCount(1220); // need define?

    gInterfaceManager.OpenTexture(BMD_MODEL_INDEX_SHIP_1, "Object1\\", GL_LINEAR, true);

    for (int i = 0; i < 4; i++)
    {
        gInterfaceManager.OpenTexture(BMD_MODEL_INDEX_LOGO_1 + i, "Logo\\", GL_LINEAR, true);
    }

    //OpenKotKeyScript(aDataHotkey_txt);
}
