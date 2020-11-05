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
	D3DXVECTOR3 rotDest; //�ړI�̊p�x
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