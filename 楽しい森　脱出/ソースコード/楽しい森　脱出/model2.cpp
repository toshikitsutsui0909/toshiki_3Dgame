//=============================================================================
//
// DirectX���^���� [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "light.h"
#include "model2.h"
#include "input.h"
#include "player.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
#define MAX_MODEL2 1
MODEL2 g_model2[MAX_MODEL2];
//=============================================================================
//����������
//=============================================================================
void InitModel2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�J���������擾������
	CAMERA*camera = GetCamera();
	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		g_model2[nCntModel].pMeshModel = NULL;
		g_model2[nCntModel].pBuffMatModel = NULL;
		g_model2[nCntModel].nNumMatModel = 0;
		g_model2[nCntModel].use = false;
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("texture/�g���l��.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_model2[nCntModel].pBuffMatModel,
			NULL,
			&g_model2[nCntModel].nNumMatModel,
			&g_model2[nCntModel].pMeshModel);
	}

}
//=============================================================================
//�I������
//=============================================================================
void UninitModel2(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		//���b�V���̔j��
		if (g_model2[nCntModel].pMeshModel != NULL)
		{
			g_model2[nCntModel].pMeshModel->Release();
			g_model2[nCntModel].pMeshModel = NULL;
		}
		//�}�e���A���̔j��
		if (g_model2[nCntModel].pBuffMatModel != NULL)
		{
			g_model2[nCntModel].pBuffMatModel->Release();
			g_model2[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateModel2(void)
{

}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawModel2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ێ��p
	D3DXMATERIAL*pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_model2[nCntModel].mtxWorldModel);
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model2[nCntModel].rot.x, g_model2[nCntModel].rot.y,
			g_model2[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_model2[nCntModel].mtxWorldModel, &g_model2[nCntModel].mtxWorldModel, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_model2[nCntModel].pos.x, g_model2[nCntModel].pos.y,
			g_model2[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_model2[nCntModel].mtxWorldModel, &g_model2[nCntModel].mtxWorldModel, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_model2[nCntModel].mtxWorldModel);


		//���݂̃}�e���A�����擾����
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_model2[nCntModel].pBuffMatModel->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_model2[nCntModel].nNumMatModel; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//���f���p�[�c�̕`��
			g_model2[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

}
void SetModel2(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		if (!g_model2[nCntModel].use)
		{
			g_model2[nCntModel].pos = pos;
			g_model2[nCntModel].size = size;
			g_model2[nCntModel].rot = rot;
			g_model2[nCntModel].use = true;
			break;
		}
	}
}

MODEL2*GetModel2()
{
	return &g_model2[0];
}