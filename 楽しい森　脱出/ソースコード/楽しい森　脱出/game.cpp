//=============================================================================
//
// シューティングゲームの作成の処理 [game.cpp]
// Author : toshiki
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "main.h"
#include "enemy.h"
#include "block.h"
#include "camera.h"
#include "wall.h"
#include "light.h"
#include "meshfield.h"
#include "item.h"
#include "goal.h"
#include "fade.h"
#include "sound.h"
#include "model.h"
#include "model2.h"
#include "ui.h"
//=============================================================================
//グローバル変数
//=============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;
PLAYER g_play;
int g_nCounterGameState = 0;

#define COUNT_WAIT_FINISH_GAME (3)
extern int g_nCountItem;
//=============================================================================
//初期化処理
//=============================================================================
void InitGame(void)
{
	CAMERA*pCamera = GetCamera();
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_nCountItem = 0;
	InitUi();
	InitMeshField();
	InitCamera();
	InitLight();
	InitWall();
	InitBlock();
	InitEnemy();
	InitPlayer();
	InitItem();
	InitGoal();
	InitModel();
	InitModel2();
	PlaySound(SOUND_LABEL_BGM000);
	pCamera->use = true;
	//縦
	SetModel(D3DXVECTOR3(-200.0f, 0.0f, 150.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-400.0f, 0.0f, 150.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-600.0f, 0.0f, 150.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, 150.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-900.0f, 0.0f, 150.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	
	SetModel(D3DXVECTOR3(-900.0f, 0.0f, 950.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, 950.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-600.0f, 0.0f, 950.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-400.0f, 0.0f, 950.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-200.0f, 0.0f, 950.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	
	SetModel(D3DXVECTOR3(-270.0f, 0.0f, 580.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-420.0f, 0.0f, 580.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-270.0f, 0.0f, 475.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-270.0f, 0.0f, 325.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-270.0f, 0.0f, 235.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-400.0f, 0.0f, 235.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-470.0f, 0.0f, 235.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-755.0f, 0.0f, 235.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-755.0f, 0.0f, 450.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-670.0f, 0.0f, 720.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-700.0f, 0.0f, 720.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-500.0f, 0.0f, 825.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-300.0f, 0.0f, 825.0f), D3DXVECTOR3(215.0f, 20.0f, 50.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));


	//横
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, 250.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, 450.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, 650.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, 850.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-800.0f, 0.0f, 950.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetModel(D3DXVECTOR3(-100.0f, 0.0f, 950.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-100.0f, 0.0f, 850.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-100.0f, 0.0f, 650.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-100.0f, 0.0f, 400.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-100.0f, 0.0f, 250.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetModel(D3DXVECTOR3(-500.0f, 0.0f, 600.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-500.0f, 0.0f, 400.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-380.0f, 0.0f, 400.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-195.0f, 0.0f, 310.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-500.0f, 0.0f, 310.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-680.0f, 0.0f, 420.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-595.0f, 0.0f, 310.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-595.0f, 0.0f, 420.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-595.0f, 0.0f, 610.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-700.0f, 0.0f, 900.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-195.0f, 0.0f, 700.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetModel(D3DXVECTOR3(-195.0f, 0.0f, 755.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	SetModel2(D3DXVECTOR3(800.0f, 7.0f, -500.0f), D3DXVECTOR3(50.0f, 20.0f, 215.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetItem(D3DXVECTOR3(-730.0f, 4.0f, 380.0f), D3DXVECTOR3(5.0f, 20.0f, 1.0f));
	SetItem(D3DXVECTOR3(-550.5f, 4.0f, 290.0f), D3DXVECTOR3(5.0f, 20.0f, 1.0f));
	SetGoal(D3DXVECTOR3(800.0f, 8.0f, -450.0f), D3DXVECTOR3(50.0f, 20.0f, 100.0f));
	SetEnemy(D3DXVECTOR3(-1000.0f, 20.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 100.0f),D3DXVECTOR3(25.0f, 25.0f, 1.0f));
	for (int nCntBlock = 0; nCntBlock < 80; nCntBlock++)
	{
		int x = rand() % 1000;
		int z = rand() % 1000;
		SetBlock(D3DXVECTOR3(x, 10.0f, z), D3DXVECTOR3(20.0f, 20.0f, 20.0f));
	}
	for (int nCntItem = 0; nCntItem < 1; nCntItem++)
	{
		int x = rand() % 1000;
		int z = rand() % 1000;
		SetItem(D3DXVECTOR3(x, 4.0f, z), D3DXVECTOR3(5.0f, 20.0f, 1.0f));
	}
}

void UninitGame(void)
{
	StopSound();
}

void UpdateGame(void)
{
	UpdateUi();
	UpdateLight();
	UpdateMeshField();
	UpdateCamera();
	UpdateKeyboard();
	UpdateWall();
	UpdateBlock();
	UpdateEnemy();
	UpdatePlayer();
	UpdateItem();
	UpdateGoal();
	UpdateModel();
	UpdateModel2();
}

void DrawGame(void)
{
	DrawMeshField();
	SetCamera();
	DrawWall();
	DrawBlock();
	DrawItem();
	DrawGoal();
	DrawModel();
	DrawModel2();
	DrawEnemy();
	DrawUi();
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END:
		g_nCounterGameState++;
		if (g_nCounterGameState >= COUNT_WAIT_FINISH_GAME && GetFade() == FADE_NONE)
		{
			g_play.use = false;
			g_nCounterGameState = 0;
			//画面モードの設定
			SetFade(MODE_RESULT);
		}
		break;
	case GAMESTATE_CLEAR:
		g_nCounterGameState++;
		if (g_nCounterGameState >= COUNT_WAIT_FINISH_GAME && GetFade() == FADE_NONE)
		{
			g_play.use = false;
			g_nCounterGameState = 0;
			//画面モードの設定
			SetFade(MODE_CLEAR);
		}
		break;
	}

}
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;//初期化
}
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
