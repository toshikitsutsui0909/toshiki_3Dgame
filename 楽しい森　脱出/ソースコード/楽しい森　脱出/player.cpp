//=============================================================================
//
// DirectX���^���� [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "enemy.h"
#include "goal.h"
#include "model.h"
#include "sound.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
LPD3DXMESH g_pMeshPlayer = NULL;			//���b�V�����ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;	//�}�e���A�����ւ̃|�C���^
DWORD g_nNumMatPlayer = 0;		//�}�e���A�����̐�
D3DXMATRIX g_mtxWorldPlayer;		//���[���h�}�g���b�N�X
int g_dirPlayer;
D3DXVECTOR3 dirPlayer;

PLAYER g_player;
CAMERA g_cameraPlayer;
//=============================================================================
//����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�J���������擾������
	CAMERA*camera = GetCamera();
	g_player.use = true;
	g_player.walk = true;
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("texture/ziki.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_nNumMatPlayer,
		&g_pMeshPlayer);

	g_player.movePos = D3DXVECTOR3(0.0f, 15.0f, -100.0f);
	g_player.moveRot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_player.moveRot.y = D3DXToRadian(camera->rot.y);
	g_cameraPlayer.fCamera = 0.9f;
	g_cameraPlayer.fDistance = 10.0f;
	dirPlayer = D3DXVECTOR3(-sinf(D3DXToRadian(camera->rot.y)), 0, -cosf(D3DXToRadian(camera->rot.y)));

}
//=============================================================================
//�I������
//=============================================================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
	StopSound();
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�J���������擾������
	CAMERA*camera = GetCamera();

	//�J�����̌�������A�O�㍶�E�Ƀ��f�����ړ�������
	
	g_player.posOld = g_player.movePos;
	if (g_player.walk = true)
	{
		//�O
		if (GetKeyboardPress(DIK_W))
		{
			g_dirPlayer = 1;
			g_player.movePos.x += sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;
			g_player.movePos.z += cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;

			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;

			g_cameraPlayer.posV.z = g_player.movePos.z +
				cosf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;
		}

		//��
		if (GetKeyboardPress(DIK_S))
		{
			g_dirPlayer = 2;
			g_player.movePos.x -= sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;
			g_player.movePos.z -= cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;

			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;

			g_cameraPlayer.posV.z = g_player.movePos.z +
				cosf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;
		}
		//�E
		if (GetKeyboardPress(DIK_D))
		{
			g_dirPlayer = 3;
			g_cameraPlayer.rot.y += 0.8f;
			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
			g_cameraPlayer.posV.z = g_player.movePos.z + cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
		}

		//��
		if (GetKeyboardPress(DIK_A))
		{
			g_dirPlayer = 4;
			g_cameraPlayer.rot.y -= 0.8f;
			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
			g_cameraPlayer.posV.z = g_player.movePos.z + cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
		}

		switch (g_dirPlayer)
		{
		case 1:
			dirPlayer = D3DXVECTOR3(sinf(D3DXToRadian(camera->rot.y)), 0, cosf(D3DXToRadian(camera->rot.y)));
			break;
		case 2:
			dirPlayer = D3DXVECTOR3(-sinf(D3DXToRadian(camera->rot.y + 90)), 0, -cosf(D3DXToRadian(camera->rot.y + 90)));
			break;
		case 3:
			dirPlayer = D3DXVECTOR3(-sinf(D3DXToRadian(camera->rot.y)), 0, -cosf(D3DXToRadian(camera->rot.y)));
			break;
		case 4:
			dirPlayer = D3DXVECTOR3(sinf(D3DXToRadian(camera->rot.y + 90)), 0, cosf(D3DXToRadian(camera->rot.y + 90)));
			break;
		default:
			break;
		}

		if (CollisionBlock(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionItem(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionBlock(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionItem(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionEnemy(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionEnemy(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionGoal(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionGoal(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionModel(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionModel(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
	}
	
}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.moveRot.y, g_player.moveRot.x,
		g_player.moveRot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.movePos.x, g_player.movePos.y,
		g_player.movePos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,
		&g_mtxWorldPlayer);


	//���݂̃}�e���A�����擾����
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//���f���p�[�c�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}

PLAYER*GetPlayer()
{
	return &g_player;
}
