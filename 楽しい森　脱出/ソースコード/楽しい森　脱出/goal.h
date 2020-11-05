//=============================================================================
//
// DirectX���^���� [model.h]
// Author :tutui
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 size;
	LPD3DXMESH pMeshgoal;
	LPD3DXBUFFER pBuffMatgoal;
	DWORD nNumMatgoal;
	D3DXMATRIX mtxWorldgoal;
	bool used;
	bool itemget;
}GOAL;

void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 size);
bool CollisionGoal(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

GOAL * GetGoal();