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
	D3DXVECTOR3 size;
	D3DXVECTOR3 rotDest; //目的の角度
	D3DXMATRIX mtxWorldModel;
	LPD3DXMESH pMeshModel;
	LPD3DXBUFFER pBuffMatModel;
	DWORD nNumMatModel;
	bool use;
}MODEL2;

void InitModel2(void);
void UninitModel2(void);
void UpdateModel2(void);
void DrawModel2(void);
void SetModel2(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

MODEL2 * GetModel2();