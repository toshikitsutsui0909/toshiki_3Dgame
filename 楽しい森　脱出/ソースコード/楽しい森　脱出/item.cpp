//=============================================================================
//
// DirectX雛型処理 [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "goal.h"
#include "sound.h"
#include "ui.h"
//=============================================================================
//グローバル変数
//=============================================================================

ITEM g_item[MAX_ITEM];
int g_nCountItem = 0;
//=============================================================================
//初期化処理
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//カメラ情報を取得得する
	CAMERA*camera = GetCamera();

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_item[nCntItem].pMeshItem = NULL;
		g_item[nCntItem].pBuffMatItem = NULL;
		g_item[nCntItem].nNumMatItem = 0;
		g_item[nCntItem].used = false;

		//Xファイルの読み込み
		D3DXLoadMeshFromX("texture/ガソリンタンク.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_item[nCntItem].pBuffMatItem,
			NULL,
			&g_item[nCntItem].nNumMatItem,
			&g_item[nCntItem].pMeshItem);
	}
}
//=============================================================================
//終了処理
//=============================================================================
void UninitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//メッシュの破棄
		if (g_item[nCntItem].pMeshItem != NULL)
		{
			g_item[nCntItem].pMeshItem->Release();
			g_item[nCntItem].pMeshItem = NULL;
		}
		//マテリアルの破棄
		if (g_item[nCntItem].pBuffMatItem != NULL)
		{
			g_item[nCntItem].pBuffMatItem->Release();
			g_item[nCntItem].pBuffMatItem = NULL;
		}
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateItem(void)
{

}

//=============================================================================
//描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保持用
	D3DXMATERIAL*pMat;			//マテリアルデータへのポインタ
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].used)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_item[nCntItem].mtxWorldItem);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_item[nCntItem].rot.x, g_item[nCntItem].rot.y,
				g_item[nCntItem].rot.z);
			D3DXMatrixMultiply(&g_item[nCntItem].mtxWorldItem, &g_item[nCntItem].mtxWorldItem, &mtxRot);
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_item[nCntItem].pos.x, g_item[nCntItem].pos.y,
				g_item[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_item[nCntItem].mtxWorldItem, &g_item[nCntItem].mtxWorldItem, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&g_item[nCntItem].mtxWorldItem);

			//現在のマテリアルを取得する
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_item[nCntItem].pBuffMatItem->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_item[nCntItem].nNumMatItem; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//モデルパーツの描画
				g_item[nCntItem].pMeshItem->DrawSubset(nCntMat);
			}
			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	{
		int nCntItem;

		for (nCntItem = 0; nCntItem < MAX_BLOCK; nCntItem++)
		{
			//falseの時
			if (!g_item[nCntItem].used)
			{
				g_item[nCntItem].pos = pos;
				g_item[nCntItem].size = size;
				g_item[nCntItem].used = true;
				break;
			}
		}
	}
}
bool CollisionItem(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();
	GOAL*pGoal = GetGoal();
	UI*pUi = GetUi();
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//trueの時
		if (g_item[nCntItem].used)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectItemMax = D3DXVECTOR3(g_item[nCntItem].size.x / 2,
				g_item[nCntItem].size.y / 2, g_item[nCntItem].size.z / 2) + g_item[nCntItem].pos;
			D3DXVECTOR3 rectItemMin = D3DXVECTOR3(-g_item[nCntItem].size.x / 2,
				-g_item[nCntItem].size.y / 2, -g_item[nCntItem].size.z / 2) + g_item[nCntItem].pos;


			if (rectPlayerMax.x > rectItemMin.x &&//blockから見て左
				rectPlayerMin.x < rectItemMax.x &&//blockから見て右
				rectPlayerMax.z > rectItemMin.z &&//blockから見て下
				rectPlayerMin.z < rectItemMax.z) //blockから見て上
			{
				g_item[nCntItem].used = false;
				if (rectPlayerMax.x > rectItemMin.x &&
					pPosOld->x + (size.x / 2) <= rectItemMin.x)
				{//左
					pPos->x = rectItemMin.x - (size.x / 2);
				}

				if (rectPlayerMin.x < rectItemMax.x &&
					pPosOld->x + (size.x / 2) >= rectItemMax.x)
				{//右
					pPos->x = +rectItemMax.x + (size.x / 2);
				}

				if (rectPlayerMax.z > rectItemMin.z &&
					pPosOld->z + (size.z / 2) <= rectItemMin.z)
				{//前
					pPos->z = rectItemMin.z - (size.z / 2);
				}

				if (rectPlayerMin.z < rectItemMax.z &&
					pPosOld->z + (size.z / 2) >= rectItemMax.z)
				{//上
					pPos->z = rectItemMax.z + (size.z / 2);
				}
				PlaySound(SOUND_LABEL_SE_ITEMGET);
				g_nCountItem++;
				pUi->nPatternAnim -= 1;
				if (g_nCountItem == 3)
				{
					pGoal->used = true;
				}
			}

		}
	}
	return isGround;
}
ITEM*GetItem(void)
{
	return &g_item[0];
}
