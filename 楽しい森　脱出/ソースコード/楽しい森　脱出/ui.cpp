#include "ui.h"
#include "player.h"
#include "item.h"

LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;//���_�o�b�t�@�ւ̃|�C���^
UI g_Ui;

void InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	g_Ui.nPatternAnim = 3;

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//�i�Œ�j
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffLife,//�ϐ������ς��ƕύX���K�v
		NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCreateTextureFromFile(pDevice, "texture/�n�[�g.png", &g_pTextureLife);

	pVtx[0].pos = D3DXVECTOR3(1250, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1850, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1250, 200, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1850, 200, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 250);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 250);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 250);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 250);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

void UninitUi(void)
{
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

void UpdateUi(void)
{
	VERTEX_2D*pVtx;
	ITEM*pItem = GetItem();
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(1250.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1850.0f - g_Ui.nPatternAnim * 200.0f, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1250.0f, 200.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1850.0f - g_Ui.nPatternAnim * 200.0f, 200.0f, 0.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f - g_Ui.nPatternAnim*0.33333f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f - g_Ui.nPatternAnim*0.33333f, 1.0f + 1.0f);



	//���_�f�[�^���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLife);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

UI * GetUi(void)
{
	return &g_Ui;
}
