//=============================================================================
//
// DirectX雛型処理 [model.h]
// Author :tutui
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest; //目的の角度
	D3DXVECTOR3 movePos;
	D3DXVECTOR3 moveRot;
	D3DXVECTOR3 posOld;
	bool use;
	bool walk;
}PLAYER;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER * GetPlayer();