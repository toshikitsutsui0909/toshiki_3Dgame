//=============================================================================
//
// DirectX雛型処理 [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "light.h"
#include "model2.h"
#include "input.h"
#include "player.h"
//=============================================================================
//グローバル変数
//=============================================================================
#define MAX_MODEL2 1
MODEL2 g_model2[MAX_MODEL2];
//=============================================================================
//初期化処理
//=============================================================================
void InitModel2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//カメラ情報を取得得する
	CAMERA*camera = GetCamera();
	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		g_model2[nCntModel].pMeshModel = NULL;
		g_model2[nCntModel].pBuffMatModel = NULL;
		g_model2[nCntModel].nNumMatModel = 0;
		g_model2[nCntModel].use = false;
		//Xファイルの読み込み
		D3DXLoadMeshFromX("texture/トンネル.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_model2[nCntModel].pBuffMatModel,
			NULL,
			&g_model2[nCntModel].nNumMatModel,
			&g_model2[nCntModel].pMeshModel);
	}

}
//=============================================================================
//終了処理
//=============================================================================
void UninitModel2(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		//メッシュの破棄
		if (g_model2[nCntModel].pMeshModel != NULL)
		{
			g_model2[nCntModel].pMeshModel->Release();
			g_model2[nCntModel].pMeshModel = NULL;
		}
		//マテリアルの破棄
		if (g_model2[nCntModel].pBuffMatModel != NULL)
		{
			g_model2[nCntModel].pBuffMatModel->Release();
			g_model2[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateModel2(void)
{

}

//=============================================================================
//描画処理
//=============================================================================
void DrawModel2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保持用
	D3DXMATERIAL*pMat;			//マテリアルデータへのポインタ

	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_model2[nCntModel].mtxWorldModel);
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model2[nCntModel].rot.x, g_model2[nCntModel].rot.y,
			g_model2[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_model2[nCntModel].mtxWorldModel, &g_model2[nCntModel].mtxWorldModel, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_model2[nCntModel].pos.x, g_model2[nCntModel].pos.y,
			g_model2[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_model2[nCntModel].mtxWorldModel, &g_model2[nCntModel].mtxWorldModel, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD,
			&g_model2[nCntModel].mtxWorldModel);


		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_model2[nCntModel].pBuffMatModel->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_model2[nCntModel].nNumMatModel; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//モデルパーツの描画
			g_model2[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

}
void SetModel2(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL2; nCntModel++)
	{
		if (!g_model2[nCntModel].use)
		{
			g_model2[nCntModel].pos = pos;
			g_model2[nCntModel].size = size;
			g_model2[nCntModel].rot = rot;
			g_model2[nCntModel].use = true;
			break;
		}
	}
}

MODEL2*GetModel2()
{
	return &g_model2[0];
}