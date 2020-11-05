//=============================================================================
//
// �V���[�e�B���O�Q�[���̍쐬�̏��� [bullet.cpp]
// Author : toshiki
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "title.h"
#include "fade.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;

FADE g_fade;
MODE g_ModeNext = MODE_TITLE;
D3DXCOLOR g_ColorFade;

void InitFade(MODE ModeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,//�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,//�i�Œ�j
		FVF_VERTEX_2D,//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,//�i�Œ�j
		&g_pVtxBuffFade,//�ϐ������ς��ƕύX���K�v
		NULL);

	VERTEX_2D*pVtx;//���_���ւ̃|�C���^
				   //���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


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


	//���_�f�[�^���A�����b�N����
	g_pVtxBuffFade->Unlock();

	g_fade = FADE_OUT;
	g_ModeNext = ModeNext;
	g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

void UninitFade(void)
{

}

FADE GetFade(void)
{
	return g_fade;
}
void SetFade(MODE ModeNext)
{

	g_fade = FADE_OUT;
	g_ModeNext = ModeNext;

}

void UpdateFade(void)
{
	VERTEX_2D*pVtx;//���_���ւ̃|�C���^

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_ColorFade.a -= FADE_RATE;
			if (g_ColorFade.a <= 0.0f)
			{
				g_ColorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_ColorFade.a += FADE_RATE;
			if (g_ColorFade.a >= 1.0f)
			{
				g_ColorFade.a = 1.0f;
				g_fade = FADE_IN;

				SetMode(g_ModeNext);
			}
		}
	}
	//���_�o�b�t�@�͈̔͂����b�N
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = g_ColorFade;
	pVtx[1].col = g_ColorFade;
	pVtx[2].col = g_ColorFade;
	pVtx[3].col = g_ColorFade;

	//���_�f�[�^�̂��A�����b�N����
	g_pVtxBuffFade->Unlock();
}

void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);


}

