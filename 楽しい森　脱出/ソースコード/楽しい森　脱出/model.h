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
}MODEL;

void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
bool CollisionModel(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

MODEL * GetModel();