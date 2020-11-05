//=============================================================================
//
// シューティングゲームの作成の処理 [title.h]
// Author : toshiki
//
//=============================================================================
#ifndef _TITLE_H
#define _TITLE_H
//#define _CRT_SECURE_NO_WARNINGS

#define MAX_TITLE (2)
#define MAX_TYPE_TITLE (4)
//インクルードファイル
#include "main.h"

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif