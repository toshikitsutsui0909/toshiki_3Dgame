//=============================================================================
//
// �V���[�e�B���O�Q�[���̍쐬�̏��� [title.cpp]
// Author : toshiki
//
//=============================================================================
#include "result.h"
#include "player.h"
#include "input.h"
#include "main.h"
#include "fade.h"
#include "sound.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//���_�o�b�t�@�ւ̃|�C���^


//=============================================================================
// ����������
//=============================================================================
void InitResult(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX * 2,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//�i�Œ�j
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffResult,//�ϐ������ς��ƕύX���K�v
		NULL);

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCreateTextureFromFile(pDevice, "texture/�Q�[���I�[�o�[���.jpg", &g_pTextureResult);


	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 250);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 250);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 250);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 250);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + 1.0f);
	//���_�f�[�^���A�����b�N����
	g_pVtxBuffResult->Unlock();
	PlaySound(SOUND_LABEL_BGM003);
}
//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{

	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	StopSound();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (/*GetKeyboardTrigger(DIK_RETURN) &&*/ GetFade() == FADE_NONE)
	{
		SetFade(MODE_TITLE);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);


}
