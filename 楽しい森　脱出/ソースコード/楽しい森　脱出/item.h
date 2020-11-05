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
	LPD3DXMESH pMeshItem;
	LPD3DXBUFFER pBuffMatItem;
	DWORD nNumMatItem;
	D3DXMATRIX mtxWorldItem;
	bool used;
	bool count;
}ITEM;

#define MAX_ITEM 3
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 size);
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size);

ITEM * GetItem();