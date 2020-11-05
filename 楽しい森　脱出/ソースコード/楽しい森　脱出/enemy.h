//=============================================================================
//
// DirectX雛型処理 [shadow.h]
// Author :tutui
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 move;
	D3DXVECTOR3 size;
	D3DXVECTOR3 posOld;
	D3DXVECTOR2 tex;
	D3DXMATRIX mtxWorld;
	bool use;
	float fAngle;
	bool play;
}ENEMY;

#define MAX_ENEMY (128)

void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
void DrawEnemy(void);
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

ENEMY*GetEnemy(void);