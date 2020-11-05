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
#include "goal.h"
#include "sound.h"
#include "ui.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================

ITEM g_item[MAX_ITEM];
int g_nCountItem = 0;
//=============================================================================
//����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�J���������擾������
	CAMERA*camera = GetCamera();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_item[nCntItem].pMeshItem = NULL;
		g_item[nCntItem].pBuffMatItem = NULL;
		g_item[nCntItem].nNumMatItem = 0;
		g_item[nCntItem].used = false;

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("texture/�K�\�����^���N.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_item[nCntItem].pBuffMatItem,
			NULL,
			&g_item[nCntItem].nNumMatItem,
			&g_item[nCntItem].pMeshItem);
	}
}
//=============================================================================
//�I������
//=============================================================================
void UninitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���b�V���̔j��
		if (g_item[nCntItem].pMeshItem != NULL)
		{
			g_item[nCntItem].pMeshItem->Release();
			g_item[nCntItem].pMeshItem = NULL;
		}
		//�}�e���A���̔j��
		if (g_item[nCntItem].pBuffMatItem != NULL)
		{
			g_item[nCntItem].pBuffMatItem->Release();
			g_item[nCntItem].pBuffMatItem = NULL;
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateItem(void)
{

}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;			//�}�e���A���f�[�^�ւ̃|�C���^
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].used)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_item[nCntItem].mtxWorldItem);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_item[nCntItem].rot.x, g_item[nCntItem].rot.y,
				g_item[nCntItem].rot.z);
			D3DXMatrixMultiply(&g_item[nCntItem].mtxWorldItem, &g_item[nCntItem].mtxWorldItem, &mtxRot);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_item[nCntItem].pos.x, g_item[nCntItem].pos.y,
				g_item[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_item[nCntItem].mtxWorldItem, &g_item[nCntItem].mtxWorldItem, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD,
				&g_item[nCntItem].mtxWorldItem);

			//���݂̃}�e���A�����擾����
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_item[nCntItem].pBuffMatItem->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_item[nCntItem].nNumMatItem; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//���f���p�[�c�̕`��
				g_item[nCntItem].pMeshItem->DrawSubset(nCntMat);
			}
			//�ێ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	{
		int nCntItem;

		for (nCntItem = 0; nCntItem < MAX_BLOCK; nCntItem++)
		{
			//false�̎�
			if (!g_item[nCntItem].used)
			{
				g_item[nCntItem].pos = pos;
				g_item[nCntItem].size = size;
				g_item[nCntItem].used = true;
				break;
			}
		}
	}
}
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();
	GOAL*pGoal = GetGoal();
	UI*pUi = GetUi();
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//true�̎�
		if (g_item[nCntItem].used)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectItemMax = D3DXVECTOR3(g_item[nCntItem].size.x / 2,
				g_item[nCntItem].size.y / 2, g_item[nCntItem].size.z / 2) + g_item[nCntItem].pos;
			D3DXVECTOR3 rectItemMin = D3DXVECTOR3(-g_item[nCntItem].size.x / 2,
				-g_item[nCntItem].size.y / 2, -g_item[nCntItem].size.z / 2) + g_item[nCntItem].pos;


			if (rectPlayerMax.x > rectItemMin.x &&//block���猩�č�
				rectPlayerMin.x < rectItemMax.x &&//block���猩�ĉE
				rectPlayerMax.z > rectItemMin.z &&//block���猩�ĉ�
				rectPlayerMin.z < rectItemMax.z) //block���猩�ď�
			{
				g_item[nCntItem].used = false;
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
				PlaySound(SOUND_LABEL_SE_ITEMGET);
				g_nCountItem++;
				pUi->nPatternAnim -= 1;
				if (g_nCountItem == 3)
				{
					pGoal->used = true;
				}
			}

		}
	}
	return isGround;
}
ITEM*GetItem(void)
{
	return &g_item[0];
}
