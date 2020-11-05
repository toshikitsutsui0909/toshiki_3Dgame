//=============================================================================
//
// シューティングゲームの作成の処理 [game.h]
// Author : toshiki
//
//=============================================================================
#ifndef _GAME_H
#define _GAME_H
#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"

//ゲーム状態
typedef enum
{

	GAMESTATE_NONE = 0,//何もしていない状態
	GAMESTATE_NORMAL,  //通常状態
	GAMESTATE_CLEAR,   //クリア状態
	GAMESTATE_END,	   //ゲーム終了状態（画面移開始待ち状態）
	GAMESTATE_MAX

}GAMESTATE;
//プロトタイプ宣言
void SetGameState(GAMESTATE state);

GAMESTATE GetGameState(void);

void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void InitMous(void);

#endif