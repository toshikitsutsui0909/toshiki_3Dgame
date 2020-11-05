//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author :tutui
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

// DirectInputバージョンの宣言
//#define DIRECTINPUT_VERSION 0x0800

//=============================================================================
// インクルードファイル
//=============================================================================
#include <windows.h>
#include "d3dx9.h"
#include <dinput.h>
#include <xaudio2.h>
//=============================================================================
// ライブラリのリンク
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")//システム時刻取得用に必要
#pragma comment(lib,"dinput8.lib")
//=============================================================================
// マクロ定義
//=============================================================================
typedef struct
{

	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//！＜頂点座標
	D3DXVECTOR3 nor;	//！＜法線ベクトル
	D3DCOLOR col;		//！＜頂点カラー
	D3DXVECTOR2 tex;
}VERTEX_3D;

//モードの種類
typedef enum
{

	MODE_TITLE = 0,		//タイトル
	MODE_TUTORIAL,
	MODE_GAME,			//ゲーム
	MODE_RESULT,		//リザルト
	MODE_CLEAR,
	MODE_MAX,

}MODE;
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1280)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//座標・法線・カラー・テクスチャ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_VERTEX	(4)
#define NUM_POLYGON	(2)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);

void SetMode(MODE mode);
MODE GetMode(void);

#endif

