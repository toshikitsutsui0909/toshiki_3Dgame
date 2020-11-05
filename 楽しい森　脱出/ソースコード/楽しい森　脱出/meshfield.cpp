//=============================================================================
//
// メッシュフィールド処理 [meshfield.cpp]
// Author : ツツイとし来い
//
//=============================================================================
#include "meshfield.h"


//=============================================================================
//グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshFiled = NULL;	//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//インデックスバッファへのポインタ
D3DXVECTOR3 g_posMeshField;	//メッシュフィールドの位置
D3DXVECTOR3 g_rotMeshFiled;	//メッシュフィールドの向き
D3DXMATRIX g_mtxWorldMeshFiled;	//メッシュフィールドのワールドマトリックス


//=============================================================================
//初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntX;
	int nCntZ;
	int nCount = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshFiled,
		NULL);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice, "texture/block000.jpg", &g_pTextureMeshField);

	//インデックスバッファ（ポリゴンバッファ）の生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * (MESHFIELD_INDEX_NUM),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);


	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshFiled->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
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

	//頂点の法線・カラー設定
	for (int nCnt = 0; nCnt < MESHFIELD_VERTEX_NUM; nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DCOLOR_RGBA(0, 255, 0, 255);

	}


	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffMeshFiled->Unlock();


	WORD*pIdx;

	//インデックスバッファをロック
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//インデックス座標の設定
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

	//インデックスバッファのアンロック
	g_pIdxBuffMeshField->Unlock();
}


//=============================================================================
//終了処理
//=============================================================================
void UninitMeshField(void)
{
	//頂点バッファの解放
	if (g_pVtxBuffMeshFiled != NULL)
	{
		g_pVtxBuffMeshFiled->Release();
		g_pVtxBuffMeshFiled = NULL;
	}

	//テクスチャの解放
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}


	//インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}


}


//=============================================================================
//更新処理
//=============================================================================
void UpdateMeshField(void)
{
	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshFiled->Lock(0, 0, (void**)&pVtx, 0);


	/*pVtx[5].pos.y = 150.0f;
	pVtx[6].pos.y = 100.0f;*/

	//頂点バッファのアンロック
	g_pVtxBuffMeshFiled->Unlock();
}


//=============================================================================
//描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用のマトリクス
									//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshFiled);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshFiled.y, g_rotMeshFiled.x, g_rotMeshFiled.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshFiled, &g_mtxWorldMeshFiled, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshFiled, &g_mtxWorldMeshFiled, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshFiled);


	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshFiled, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		MESHFIELD_VERTEX_NUM,
		0,
		MESHFIELD_PRIMITIVE_NUM);

	//テクスチャの設定を戻す
	pDevice->SetTexture(0, NULL);
}