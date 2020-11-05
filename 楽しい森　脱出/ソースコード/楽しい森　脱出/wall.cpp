//=============================================================================
//
// DirectX雛型処理 [polygon.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "wall.h"

//=============================================================================
//グローバル変数
//=============================================================================

//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffwall = NULL;

//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturewall = NULL;

//ポリゴンの位置
D3DXVECTOR3 g_poswall;

//ポリゴンの向き
D3DXVECTOR3 g_rotwall;

//ポリゴンのワールドマトリックス
D3DXMATRIX g_mtxWorldwall;

WALL g_wall[MAX_WALL];
//=============================================================================
//初期化処理
//=============================================================================
void InitWall(void)
{
	int nCntwall;
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (nCntwall = 0; nCntwall < MAX_WALL; nCntwall++)
	{
		g_wall[nCntwall].bUse = false;
	}

	D3DXCreateTextureFromFile(pDevice, "texture/gettyimages-473076907-640x640.jpg", &g_pTexturewall);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffwall,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntwall = 0; nCntwall < MAX_WALL; nCntwall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f);
		pVtx[1].pos = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);
		pVtx[2].pos = D3DXVECTOR3(-1000.0f, 0.0f, -1000.0f);
		pVtx[3].pos = D3DXVECTOR3(1000.0f, 0.0f, -1000.0f);

		//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
		pVtx[0].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		//頂点カラーの設定
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

	//頂点バッファのアンロック
	g_pVtxBuffwall->Unlock();

	SetWall(D3DXVECTOR3(0.0f, 700.0f, 1000.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));

	SetWall(D3DXVECTOR3(0.0f, 700.0f, -500.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f));

	SetWall(D3DXVECTOR3(1000.0f, 700.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, D3DXToRadian(90.0f)));

	SetWall(D3DXVECTOR3(-1000.0f, 700.0f, 0.0f), D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, D3DXToRadian(90.0f)));
}


//=============================================================================
//終了処理
//=============================================================================
void UninitWall(void)
{
	//テクスチャの解放
	if (g_pTexturewall != NULL)
	{
		g_pTexturewall->Release();
		g_pTexturewall = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffwall != NULL)
	{
		g_pVtxBuffwall->Release();
		g_pVtxBuffwall = NULL;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
//描画処理
//=============================================================================
void DrawWall(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//行列計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans;

	pDevice->SetTexture(0, g_pTexturewall);
	for (int i = 0; i < MAX_WALL; i++)
	{
		if (g_wall[i].bUse)
		{
			D3DXMatrixIdentity(&g_wall[i].mtxWorld);
			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_wall[i].rot.y, g_wall[i].rot.x,
				g_wall[i].rot.z);
			D3DXMatrixMultiply(&g_wall[i].mtxWorld, &g_wall[i].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_wall[i].pos.x, g_wall[i].pos.y,
				g_wall[i].pos.z);
			D3DXMatrixMultiply(&g_wall[i].mtxWorld, &g_wall[i].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_wall[i].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffwall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画
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
