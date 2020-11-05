#include "ui.h"
#include "player.h"
#include "item.h"

LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;//頂点バッファへのポインタ
UI g_Ui;

void InitUi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D*pVtx;//頂点情報へのポインタ

	g_Ui.nPatternAnim = 3;

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D)*NUM_VERTEX,//バッファサイズ
		D3DUSAGE_WRITEONLY,//（固定）
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,//（固定）
		&g_pVtxBuffLife,//変数名が変わると変更が必要
		NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCreateTextureFromFile(pDevice, "texture/ハート.png", &g_pTextureLife);

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

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロックする
	g_pVtxBuffLife->Unlock();
}

void UninitUi(void)
{
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//頂点バッファの開放
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
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(1250.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1850.0f - g_Ui.nPatternAnim * 200.0f, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1250.0f, 200.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1850.0f - g_Ui.nPatternAnim * 200.0f, 200.0f, 0.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f - g_Ui.nPatternAnim*0.33333f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f - g_Ui.nPatternAnim*0.33333f, 1.0f + 1.0f);



	//頂点データをアンロックする
	g_pVtxBuffLife->Unlock();
}

void DrawUi(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLife);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}

UI * GetUi(void)
{
	return &g_Ui;
}
