//=============================================================================
//
// DirectX���^���� [polygon.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "wall.h"

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================

//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffwall = NULL;

//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturewall = NULL;

//�|���S���̈ʒu
D3DXVECTOR3 g_poswall;

//�|���S���̌���
D3DXVECTOR3 g_rotwall;

//�|���S���̃��[���h�}�g���b�N�X
D3DXMATRIX g_mtxWorldwall;

WALL g_wall[MAX_WALL];
//=============================================================================
//����������
//=============================================================================
void InitWall(void)
{
	int nCntwall;
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntwall = 0; nCntwall < MAX_WALL; nCntwall++)
	{
		g_wall[nCntwall].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "texture/gettyimages-473076907-640x640.jpg", &g_pTexturewall);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffwall,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntwall = 0; nCntwall < MAX_WALL; nCntwall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f);
		pVtx[1].pos = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);
		pVtx[2].pos = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
		pVtx[3].pos = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);

		//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffwall->Unlock();

	SetWall(D3DXVECTOR3(0.0f, 700.0f, 1000.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));

	SetWall(D3DXVECTOR3(0.0f, 700.0f, -500.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));

	SetWall(D3DXVECTOR3(1000.0f, 700.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, D3DXToRadian(90.0f)));

	SetWall(D3DXVECTOR3(-1000.0f, 700.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, D3DXToRadian(90.0f)));
}


//=============================================================================
//�I������
//=============================================================================
void UninitWall(void)
{
	//�e�N�X�`���̉��
	if (g_pTexturewall != NULL)
	{
		g_pTexturewall->Release();
		g_pTexturewall = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffwall != NULL)
	{
		g_pVtxBuffwall->Release();
		g_pVtxBuffwall = NULL;
	}
}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawWall(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�s��v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetTexture(0, g_pTexturewall);
	for (int i = 0; i < MAX_WALL; i++)
	{
		if (g_wall[i].bUse)
		{
			D3DXMatrixIdentity(&g_wall[i].mtxWorld);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[i].rot.y, g_wall[i].rot.x,
				g_wall[i].rot.z);
			D3DXMatrixMultiply(&g_wall[i].mtxWorld, &g_wall[i].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_wall[i].pos.x, g_wall[i].pos.y,
				g_wall[i].pos.z);
			D3DXMatrixMultiply(&g_wall[i].mtxWorld, &g_wall[i].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_wall[i].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffwall, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	pDevice->SetTexture(0, NULL);

}
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	{
		int nCntwall;

		for (nCntwall = 0; nCntwall < MAX_WALL; nCntwall++)
		{

			if (!g_wall[nCntwall].bUse)
			{
				g_wall[nCntwall].pos = pos;
				g_wall[nCntwall].rot = rot;
				g_wall[nCntwall].bUse = true;
				break;
			}
		}
	}
}
