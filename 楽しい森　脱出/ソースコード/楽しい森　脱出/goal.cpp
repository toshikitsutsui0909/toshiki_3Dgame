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
#include "goal.h"
#include "game.h"
#include "sound.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================

GOAL g_goal;
extern int g_nCountItem;
//=============================================================================
//����������
//=============================================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�J���������擾������
	CAMERA*camera = GetCamera();

	g_goal.pMeshgoal = NULL;
	g_goal.pBuffMatgoal = NULL;
	g_goal.nNumMatgoal = 0;
	g_goal.used = false;
	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("texture/��.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_goal.pBuffMatgoal,
		NULL,
		&g_goal.nNumMatgoal,
		&g_goal.pMeshgoal);
}
//=============================================================================
//�I������
//=============================================================================
void UninitGoal(void)
{
	//���b�V���̔j��
	if (g_goal.pMeshgoal != NULL)
	{
		g_goal.pMeshgoal->Release();
		g_goal.pMeshgoal = NULL;
	}
	//�}�e���A���̔j��
	if (g_goal.pBuffMatgoal != NULL)
	{
		g_goal.pBuffMatgoal->Release();
		g_goal.pBuffMatgoal = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateGoal(void)
{

}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;			//�}�e���A���f�[�^�ւ̃|�C���^
	
	if (g_goal.used)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_goal.mtxWorldgoal);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goal.rot.x, g_goal.rot.y,
			g_goal.rot.z);
		D3DXMatrixMultiply(&g_goal.mtxWorldgoal, &g_goal.mtxWorldgoal, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_goal.pos.x, g_goal.pos.y,
			g_goal.pos.z);
		D3DXMatrixMultiply(&g_goal.mtxWorldgoal, &g_goal.mtxWorldgoal, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_goal.mtxWorldgoal);

		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_goal.pBuffMatgoal->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_goal.nNumMatgoal; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//���f���p�[�c�̕`��
			g_goal.pMeshgoal->DrawSubset(nCntMat);
		}
		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	g_goal.pos = pos;
	g_goal.size = size;
}
bool CollisionGoal(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();
	CAMERA*pCamera = GetCamera();
	int nCountItem = 0;

		//true�̎�
		if (g_goal.used)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectItemMax = D3DXVECTOR3(g_goal.size.x / 2,
				g_goal.size.y / 2, g_goal.size.z / 2) + g_goal.pos;
			D3DXVECTOR3 rectItemMin = D3DXVECTOR3(-g_goal.size.x / 2,
				-g_goal.size.y / 2, -g_goal.size.z / 2) + g_goal.pos;


			if (rectPlayerMax.x > rectItemMin.x &&//block���猩�č�
				rectPlayerMin.x < rectItemMax.x &&//block���猩�ĉE
				rectPlayerMax.z > rectItemMin.z &&//block���猩�ĉ�
				rectPlayerMin.z < rectItemMax.z) //block���猩�ď�
			{
				if (rectPlayerMax.x > rectItemMin.x &&
					pPosOld->x + (size.x / 2) <= rectItemMin.x)
				{//��
					pPos->x = rectItemMin.x - (size.x / 2);
				}

				if (rectPlayerMin.x < rectItemMax.x &&
					pPosOld->x + (size.x / 2) >= rectItemMax.x)
				{//�E
					pPos->x = +rectItemMax.x + (size.x / 2);
				}

				if (rectPlayerMax.z > rectItemMin.z &&
					pPosOld->z + (size.z / 2) <= rectItemMin.z)
				{//�O
					pPos->z = rectItemMin.z - (size.z / 2);
				}

				if (rectPlayerMin.z < rectItemMax.z &&
					pPosOld->z + (size.z / 2) >= rectItemMax.z)
				{//��
					pPos->z = rectItemMax.z + (size.z / 2);
				}
				PlaySound(SOUND_LABEL_SE_GOAL);
				SetGameState(GAMESTATE_CLEAR);
			}
		}
	return isGround;
}
GOAL*GetGoal(void)
{
	return &g_goal;
}
