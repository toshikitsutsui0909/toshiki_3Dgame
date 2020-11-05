//=============================================================================
//
// DirectX���^���� [camera.h]
// Author : tutui
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

typedef struct
{
	D3DXVECTOR3 posV;	//�I���J�����̍��W
	D3DXVECTOR3 posR;	//�I�������_
	D3DXVECTOR3 vecU;	//�I��������x�N�g��
	D3DXVECTOR3 rot;	//�I�������擾�p
	D3DXMATRIX mtxProjection;//�I���v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;	//�I���r���[�}�g���b�N�X
	D3DXVECTOR3 posVDest;//�J�����̍��W�i�ړI�l�j
	D3DXVECTOR3 posRDest;//���ӓ_�i�ړI�l�j
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posVOld;
	float fDistance;	//�I�����_�[�����_�̋���
	float fCamera;
	bool use;

}CAMERA;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

CAMERA * GetCamera(void);