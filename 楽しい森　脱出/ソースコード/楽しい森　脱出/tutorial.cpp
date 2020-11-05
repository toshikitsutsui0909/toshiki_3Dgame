//=============================================================================
//
// シューティングゲームの作成の処理 [title.cpp]
// Author : toshiki
//
//=============================================================================
#include "title.h"
#include "player.h"
#include "input.h"
#include "main.h"
#include "sound.h"
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//頂点バッファへのポインタ


//=============================================================================
// 初期化処理
//=============================================================================
void InitTutorial(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

				   //頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX * 2,//バッファサイズ
		D3DUSAGE_WRITEONLY,//（固定）
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffTutorial,//変数名が変わると変更が必要
		NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCreateTextureFromFile(pDevice, "texture/おおお.jpg", &g_pTextureTutorial);


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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + 1.0f);
	//頂点データをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{

	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
	StopSound();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);


}
