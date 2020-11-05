//=============================================================================
//
// シューティングゲームの作成の処理 [bullet.cpp]
// Author : toshiki
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "title.h"
#include "fade.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;

FADE g_fade;
MODE g_ModeNext = MODE_TITLE;
D3DXCOLOR g_ColorFade;

void InitFade(MODE ModeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
		D3DUSAGE_WRITEONLY,//（固定）
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffFade,//変数名が変わると変更が必要
		NULL);

	VERTEX_2D*pVtx;//頂点情報へのポインタ
				   //頂点データの範囲をロックし、頂点バッファへのポインタを取得
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


	//頂点データをアンロックする
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
	VERTEX_2D*pVtx;//頂点情報へのポインタ

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
	//頂点バッファの範囲をロック
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = g_ColorFade;
	pVtx[1].col = g_ColorFade;
	pVtx[2].col = g_ColorFade;
	pVtx[3].col = g_ColorFade;

	//頂点データのをアンロックする
	g_pVtxBuffFade->Unlock();
}

void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);


}

