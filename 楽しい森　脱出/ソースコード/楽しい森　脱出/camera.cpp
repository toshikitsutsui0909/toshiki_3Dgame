//=============================================================================
//
// DirectX���^���� [camera.cpp](���@�L�����N�^�[�ڐ��j
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
CAMERA g_camera;//�J�������

//=============================================================================
//����������
//=============================================================================
void InitCamera(void)
{
	g_camera.fCamera = 0.9f;
	//�J�����̈ʒu�E�����_�E��������w�肷��@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@
	g_camera.posV = D3DXVECTOR3(0.0f, 20.0f, -100.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.fDistance = g_camera.posR.z - g_camera.posV.z;

	/*GetCursorPos(&g_CursorPosOld);*/
}

//=============================================================================
//�I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
//�X�V����
//==========================================================================
void UpdateCamera(void)
{
	g_camera.posVOld = g_camera.posV;
	if (g_camera.use = true)
	{
		//�O
		if (GetKeyboardPress(DIK_W))
		{
			g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;
			g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;

			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		}

		//��
		if (GetKeyboardPress(DIK_S))
		{
			g_camera.posV.x -= sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;
			g_camera.posV.z -= cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;

			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		}

		//�E
		if (GetKeyboardPress(DIK_D))
		{
			g_camera.rot.y += 1.1f;
			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
		}
		//��
		if (GetKeyboardPress(DIK_A))
		{
			g_camera.rot.y -= 1.1f;
			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
		}
	}
}

//=============================================================================
//�Ȃ񂩃J�����Z�b�g������
//=============================================================================
void SetCamera(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1500.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_camera.mtxProjection);

}

CAMERA*GetCamera()
{
	return &g_camera;
}