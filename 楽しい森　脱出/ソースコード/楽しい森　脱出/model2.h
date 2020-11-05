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
	D3DXVECTOR3 rotDest; //�ړI�̊p�x
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