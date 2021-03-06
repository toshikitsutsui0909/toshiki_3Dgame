//=============================================================================
//
// シューティングゲームの作成の処理 [title.cpp]
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
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//頂点バッファへのポインタ


//=============================================================================
// 初期化処理
//=============================================================================
void InitResult(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

				   //頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX * 2,//バッファサイズ
		D3DUSAGE_WRITEONLY,//（固定）
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffResult,//変数名が変わると変更が必要
		NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCreateTextureFromFile(pDevice, "texture/ゲームオーバー画面.jpg", &g_pTextureResult);


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
	g_pVtxBuffResult->Unlock();
	PlaySound(SOUND_LABEL_BGM003);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{

	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	StopSound();
}

//=============================================================================
// 更新処理
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
// 描画処理
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);


}
