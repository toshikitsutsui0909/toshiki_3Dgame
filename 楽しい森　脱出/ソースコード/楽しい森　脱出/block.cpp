//=============================================================================
//
// DirectX���^���� [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "block.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================


BLOCK g_Block[MAX_BLOCK];
//=============================================================================
//����������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�J���������擾������
	CAMERA*camera = GetCamera();
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pMeshBlock = NULL;
		g_Block[nCntBlock].pBuffMatBlock = NULL;
		g_Block[nCntBlock].nNumMatBlock = 0;

		g_Block[nCntBlock].used = false;
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("texture/��.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlock].pBuffMatBlock,
			NULL,
			&g_Block[nCntBlock].nNumMatBlock,
			&g_Block[nCntBlock].pMeshBlock);
	}
}
//=============================================================================
//�I������
//=============================================================================
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���b�V���̔j��
		if (g_Block[nCntBlock].pMeshBlock != NULL)
		{
			g_Block[nCntBlock].pMeshBlock->Release();
			g_Block[nCntBlock].pMeshBlock = NULL;
		}
		//�}�e���A���̔j��
		if (g_Block[nCntBlock].pBuffMatBlock != NULL)
		{
			g_Block[nCntBlock].pBuffMatBlock->Release();
			g_Block[nCntBlock].pBuffMatBlock = NULL;
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateBlock(void)
{

}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;			//�}�e���A���f�[�^�ւ̃|�C���^


	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].used)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCntBlock].rot.x, g_Block[nCntBlock].rot.y,
				g_Block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y,
				g_Block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_Block[nCntBlock].mtxWorld);



			//���݂̃}�e���A�����擾����
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Block[nCntBlock].pBuffMatBlock->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_Block[nCntBlock].nNumMatBlock; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				g_Block[nCntBlock].pMeshBlock->DrawSubset(nCntMat);
			}
			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	{
		int nCntBlock;

		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			//false�̎�
			if (!g_Block[nCntBlock].used)
			{
				g_Block[nCntBlock].pos = pos;
				g_Block[nCntBlock].size = size;
				g_Block[nCntBlock].used = true;
				break;
			}
		}
	}
}

bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//true�̎�
		if (g_Block[nCntBlock].used)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectBlockMax = D3DXVECTOR3(g_Block[nCntBlock].size.x / 2,
				g_Block[nCntBlock].size.y / 2, g_Block[nCntBlock].size.z / 2) + g_Block[nCntBlock].pos;
			D3DXVECTOR3 rectBlockMin = D3DXVECTOR3(-g_Block[nCntBlock].size.x / 2,
				-g_Block[nCntBlock].size.y / 2, -g_Block[nCntBlock].size.z / 2) + g_Block[nCntBlock].pos;


			if (rectPlayerMax.x > rectBlockMin.x &&//block���猩�č�
				rectPlayerMin.x < rectBlockMax.x &&//block���猩�ĉE
				rectPlayerMax.z > rectBlockMin.z &&//block���猩�ĉ�
				rectPlayerMin.z < rectBlockMax.z) //block���猩�ď�
			{
				if (rectPlayerMax.x > rectBlockMin.x &&
					pPosOld->x + (size.x / 2) <= rectBlockMin.x)
				{//��
					pPos->x = rectBlockMin.x - (size.x / 2);
				}

				if (rectPlayerMin.x < rectBlockMax.x &&
					pPosOld->x + (size.x / 2) >= rectBlockMax.x)
				{//�E
					pPos->x = + rectBlockMax.x + (size.x / 2);
				}

				if (rectPlayerMax.z > rectBlockMin.z &&
					pPosOld->z + (size.z / 2) <= rectBlockMin.z)
				{//�O
					pPos->z = rectBlockMin.z - (size.z / 2);
				}

				if (rectPlayerMin.z < rectBlockMax.z &&
					pPosOld->z + (size.z / 2) >= rectBlockMax.z)
				{//��
					pPos->z = rectBlockMax.z + (size.z / 2);
				}
			}
		}
	}
	return isGround;
}
BLOCK*GetBlock(void)
{
	return &g_Block[0];
}