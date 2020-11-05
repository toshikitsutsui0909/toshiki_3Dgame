//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.cpp]
// Author : �c�c�C�Ƃ�����
//
//=============================================================================
#include "meshfield.h"


//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshFiled = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posMeshField;	//���b�V���t�B�[���h�̈ʒu
D3DXVECTOR3 g_rotMeshFiled;	//���b�V���t�B�[���h�̌���
D3DXMATRIX g_mtxWorldMeshFiled;	//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X


//=============================================================================
//����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntX;
	int nCntZ;
	int nCount = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshFiled,
		NULL);

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, "texture/block000.jpg", &g_pTextureMeshField);

	//�C���f�b�N�X�o�b�t�@�i�|���S���o�b�t�@�j�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * (MESHFIELD_INDEX_NUM),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);


	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshFiled->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	for (nCntZ = 0; nCntZ < (MESHFIELD_Z_BLOCK + 1); nCntZ++)
	{
		for (nCntX = 0; nCntX < (MESHFIELD_X_BLOCK + 1); nCntX++)
		{
			pVtx[nCount].pos = D3DXVECTOR3(
				(float)nCntX * MESH_LENGTH - (MESHFIELD_X_BLOCK * (MESH_LENGTH / 2)),
				0.5f,
				(float)nCntZ*-MESH_LENGTH + (MESHFIELD_Z_BLOCK * (MESH_LENGTH / 2)));

			//pVtx[nCount].tex = D3DXVECTOR2(nCntX, nCntZ);
			nCount += 1;


		}
	}

	//���_�̖@���E�J���[�ݒ�
	for (int nCnt = 0; nCnt < MESHFIELD_VERTEX_NUM; nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DCOLOR_RGBA(0, 255, 0, 255);

	}


	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshFiled->Unlock();


	WORD*pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X���W�̐ݒ�
	nCount = 0;

	for (int nIdZ = 0; nIdZ < MESHFIELD_Z_BLOCK; nIdZ++)
	{
		if (nIdZ != 0)
		{
			pIdx[nCount] = (MESHFIELD_X_BLOCK + 1 + (nIdZ*(MESHFIELD_X_BLOCK + 1)));
			nCount += 1;
		}
		for (int nIdxX = 0; nIdxX < (MESHFIELD_X_BLOCK + 1); nIdxX++)
		{

			pIdx[nCount] = (MESHFIELD_X_BLOCK + 1 + nIdxX + (nIdZ*(MESHFIELD_X_BLOCK + 1)));
			nCount += 1;

			pIdx[nCount] = (pIdx[nCount - 1] - (MESHFIELD_X_BLOCK + 1));
			nCount += 1;
		}
		if (nIdZ != (MESHFIELD_Z_BLOCK - 1))
		{
			pIdx[nCount] = pIdx[nCount - 1];
			nCount += 1;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();
}


//=============================================================================
//�I������
//=============================================================================
void UninitMeshField(void)
{
	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshFiled != NULL)
	{
		g_pVtxBuffMeshFiled->Release();
		g_pVtxBuffMeshFiled = NULL;
	}

	//�e�N�X�`���̉��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}


	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}


}


//=============================================================================
//�X�V����
//=============================================================================
void UpdateMeshField(void)
{
	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshFiled->Lock(0, 0, (void**)&pVtx, 0);


	/*pVtx[5].pos.y = 150.0f;
	pVtx[6].pos.y = 100.0f;*/

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshFiled->Unlock();
}


//=============================================================================
//�`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�̃}�g���N�X
									//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshFiled);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshFiled.y, g_rotMeshFiled.x, g_rotMeshFiled.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshFiled, &g_mtxWorldMeshFiled, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshFiled, &g_mtxWorldMeshFiled, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshFiled);


	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshFiled, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		MESHFIELD_VERTEX_NUM,
		0,
		MESHFIELD_PRIMITIVE_NUM);

	//�e�N�X�`���̐ݒ��߂�
	pDevice->SetTexture(0, NULL);
}