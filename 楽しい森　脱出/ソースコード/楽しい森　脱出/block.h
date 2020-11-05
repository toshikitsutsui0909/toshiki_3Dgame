//=============================================================================
//
// DirectX雛型処理 [model.h]
// Author :tutui
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 size;
	D3DXMATRIX mtxWorld;
	LPD3DXMESH pMeshBlock;
	LPD3DXBUFFER pBuffMatBlock;
	DWORD nNumMatBlock;
	bool used;
}BLOCK;

#define MAX_BLOCK 128
//=============================================================================
// プロトタイプ宣言
//=============================================================================

void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);



BLOCK * GetBlock(void);

#endif // !_BLOCK_H_
