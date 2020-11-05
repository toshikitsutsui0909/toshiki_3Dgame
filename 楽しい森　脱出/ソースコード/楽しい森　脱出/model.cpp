//=============================================================================
//
// DirectX雛型処理 [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "player.h"
//=============================================================================
//グローバル変数
//=============================================================================
#define MAX_MODEL 45
MODEL g_model[MAX_MODEL];
//=============================================================================
//初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//カメラ情報を取得得する
	CAMERA*camera = GetCamera();
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_model[nCntModel].pMeshModel = NULL;
		g_model[nCntModel].pBuffMatModel = NULL;
		g_model[nCntModel].nNumMatModel = 0;
		g_model[nCntModel].use = false;
		//Xファイルの読み込み
		D3DXLoadMeshFromX("texture/壁.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_model[nCntModel].pBuffMatModel,
			NULL,
			&g_model[nCntModel].nNumMatModel,
			&g_model[nCntModel].pMeshModel);
	}

}
//=============================================================================
//終了処理
//=============================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//メッシュの破棄
		if (g_model[nCntModel].pMeshModel != NULL)
		{
			g_model[nCntModel].pMeshModel->Release();
			g_model[nCntModel].pMeshModel = NULL;
		}
		//マテリアルの破棄
		if (g_model[nCntModel].pBuffMatModel != NULL)
		{
			g_model[nCntModel].pBuffMatModel->Release();
			g_model[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateModel(void)
{

}

//=============================================================================
//描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保持用
	D3DXMATERIAL*pMat;			//マテリアルデータへのポインタ

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_model[nCntModel].mtxWorldModel);
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_model[nCntModel].rot.x, g_model[nCntModel].rot.y,
			g_model[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_model[nCntModel].mtxWorldModel, &g_model[nCntModel].mtxWorldModel, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_model[nCntModel].pos.x, g_model[nCntModel].pos.y,
			g_model[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_model[nCntModel].mtxWorldModel, &g_model[nCntModel].mtxWorldModel, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD,
			&g_model[nCntModel].mtxWorldModel);


		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_model[nCntModel].pBuffMatModel->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_model[nCntModel].nNumMatModel; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//モデルパーツの描画
			g_model[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

}
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (!g_model[nCntModel].use)
		{
			g_model[nCntModel].pos  = pos;
			g_model[nCntModel].size = size;
			g_model[nCntModel].rot  = rot;
			g_model[nCntModel].use  = true;
			break;
		}
	}
}

bool CollisionModel(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{

	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//trueの時
		if (g_model[nCntModel].use)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectModelMax = D3DXVECTOR3(g_model[nCntModel].size.x / 2,
				g_model[nCntModel].size.y / 2, g_model[nCntModel].size.z / 2) + g_model[nCntModel].pos;
			D3DXVECTOR3 rectModelMin = D3DXVECTOR3(-g_model[nCntModel].size.x / 2,
				-g_model[nCntModel].size.y / 2, -g_model[nCntModel].size.z / 2) + g_model[nCntModel].pos;


			if (rectPlayerMax.x > rectModelMin.x &&//blockから見て左
				rectPlayerMin.x < rectModelMax.x &&//blockから見て右
				rectPlayerMax.z > rectModelMin.z &&//blockから見て下
				rectPlayerMin.z < rectModelMax.z) //blockから見て上
			{
				if (rectPlayerMax.x > rectModelMin.x &&
					pPosOld->x + (size.x / 2) <= rectModelMin.x)
				{//左
					pPos->x = rectModelMin.x - (size.x / 2);
				}

				if (rectPlayerMin.x < rectModelMax.x &&
					pPosOld->x + (size.x / 2) >= rectModelMax.x)
				{//右
					pPos->x = +rectModelMax.x + (size.x / 2);
				}

				if (rectPlayerMax.z > rectModelMin.z &&
					pPosOld->z + (size.z / 2) <= rectModelMin.z)
				{//前
					pPos->z = rectModelMin.z - (size.z / 2);
				}

				if (rectPlayerMin.z < rectModelMax.z &&
					pPosOld->z + (size.z / 2) >= rectModelMax.z)
				{//上
					pPos->z = rectModelMax.z + (size.z / 2);
				}
			}
		}
	}
	return isGround;
}



MODEL*GetModel()
{
	return &g_model[0];
}