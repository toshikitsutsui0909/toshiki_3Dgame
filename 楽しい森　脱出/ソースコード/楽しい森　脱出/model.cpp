//=============================================================================
//
// DirectX���^���� [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "player.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
#define MAX_MODEL 45
MODEL g_model[MAX_MODEL];
//=============================================================================
//����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�J���������擾������
	CAMERA*camera = GetCamera();
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_model[nCntModel].pMeshModel = NULL;
		g_model[nCntModel].pBuffMatModel = NULL;
		g_model[nCntModel].nNumMatModel = 0;
		g_model[nCntModel].use = false;
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("texture/��.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_model[nCntModel].pBuffMatModel,
			NULL,
			&g_model[nCntModel].nNumMatModel,
			&g_model[nCntModel].pMeshModel);
	}

}
//=============================================================================
//�I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//���b�V���̔j��
		if (g_model[nCntModel].pMeshModel != NULL)
		{
			g_model[nCntModel].pMeshModel->Release();
			g_model[nCntModel].pMeshModel = NULL;
		}
		//�}�e���A���̔j��
		if (g_model[nCntModel].pBuffMatModel != NULL)
		{
			g_model[nCntModel].pBuffMatModel->Release();
			g_model[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_model[nCntModel].mtxWorldModel);
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCntModel].rot.x, g_model[nCntModel].rot.y,
			g_model[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_model[nCntModel].mtxWorldModel, &g_model[nCntModel].mtxWorldModel, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_model[nCntModel].pos.x, g_model[nCntModel].pos.y,
			g_model[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_model[nCntModel].mtxWorldModel, &g_model[nCntModel].mtxWorldModel, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_model[nCntModel].mtxWorldModel);


		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_model[nCntModel].pBuffMatModel->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_model[nCntModel].nNumMatModel; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//���f���p�[�c�̕`��
			g_model[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

}
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (!g_model[nCntModel].use)
		{
			g_model[nCntModel].pos  = pos;
			g_model[nCntModel].size = size;
			g_model[nCntModel].rot  = rot;
			g_model[nCntModel].use  = true;
			break;
		}
	}
}

bool CollisionModel(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{

	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//true�̎�
		if (g_model[nCntModel].use)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectModelMax = D3DXVECTOR3(g_model[nCntModel].size.x / 2,
				g_model[nCntModel].size.y / 2, g_model[nCntModel].size.z / 2) + g_model[nCntModel].pos;
			D3DXVECTOR3 rectModelMin = D3DXVECTOR3(-g_model[nCntModel].size.x / 2,
				-g_model[nCntModel].size.y / 2, -g_model[nCntModel].size.z / 2) + g_model[nCntModel].pos;


			if (rectPlayerMax.x > rectModelMin.x &&//block���猩�č�
				rectPlayerMin.x < rectModelMax.x &&//block���猩�ĉE
				rectPlayerMax.z > rectModelMin.z &&//block���猩�ĉ�
				rectPlayerMin.z < rectModelMax.z) //block���猩�ď�
			{
				if (rectPlayerMax.x > rectModelMin.x &&
					pPosOld->x + (size.x / 2) <= rectModelMin.x)
				{//��
					pPos->x = rectModelMin.x - (size.x / 2);
				}

				if (rectPlayerMin.x < rectModelMax.x &&
					pPosOld->x + (size.x / 2) >= rectModelMax.x)
				{//�E
					pPos->x = +rectModelMax.x + (size.x / 2);
				}

				if (rectPlayerMax.z > rectModelMin.z &&
					pPosOld->z + (size.z / 2) <= rectModelMin.z)
				{//�O
					pPos->z = rectModelMin.z - (size.z / 2);
				}

				if (rectPlayerMin.z < rectModelMax.z &&
					pPosOld->z + (size.z / 2) >= rectModelMax.z)
				{//��
					pPos->z = rectModelMax.z + (size.z / 2);
				}
			}
		}
	}
	return isGround;
}



MODEL*GetModel()
{
	return &g_model[0];
}