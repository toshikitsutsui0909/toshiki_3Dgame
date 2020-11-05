//=============================================================================
//
// DirectX���^���� [polygon.h]
// Author :tutui
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================

#include "main.h"
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}WALL;
#define MAX_WALL (5)
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);