//=============================================================================
//
// DirectX雛型処理 [model.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "block.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "input.h"
//=============================================================================
//グローバル変数
//=============================================================================


BLOCK g_Block[MAX_BLOCK];
//=============================================================================
//初期化処理
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//カメラ情報を取得得する
	CAMERA*camera = GetCamera();
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_Block[nCntBlock].pMeshBlock = NULL;
		g_Block[nCntBlock].pBuffMatBlock = NULL;
		g_Block[nCntBlock].nNumMatBlock = 0;

		g_Block[nCntBlock].used = false;
		//Xファイルの読み込み
		D3DXLoadMeshFromX("texture/木.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Block[nCntBlock].pBuffMatBlock,
			NULL,
			&g_Block[nCntBlock].nNumMatBlock,
			&g_Block[nCntBlock].pMeshBlock);
	}
}
//=============================================================================
//終了処理
//=============================================================================
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//メッシュの破棄
		if (g_Block[nCntBlock].pMeshBlock != NULL)
		{
			g_Block[nCntBlock].pMeshBlock->Release();
			g_Block[nCntBlock].pMeshBlock = NULL;
		}
		//マテリアルの破棄
		if (g_Block[nCntBlock].pBuffMatBlock != NULL)
		{
			g_Block[nCntBlock].pBuffMatBlock->Release();
			g_Block[nCntBlock].pBuffMatBlock = NULL;
		}
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateBlock(void)
{

}

//=============================================================================
//描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保持用
	D3DXMATERIAL*pMat;			//マテリアルデータへのポインタ


	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].used)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);
			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCntBlock].rot.x, g_Block[nCntBlock].rot.y,
				g_Block[nCntBlock].rot.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y,
				g_Block[nCntBlock].pos.z);
			D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&g_Block[nCntBlock].mtxWorld);



			//現在のマテリアルを取得する
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Block[nCntBlock].pBuffMatBlock->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_Block[nCntBlock].nNumMatBlock; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//モデルパーツの描画
				g_Block[nCntBlock].pMeshBlock->DrawSubset(nCntMat);
			}
			//保持していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	{
		int nCntBlock;

		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			//falseの時
			if (!g_Block[nCntBlock].used)
			{
				g_Block[nCntBlock].pos = pos;
				g_Block[nCntBlock].size = size;
				g_Block[nCntBlock].used = true;
				break;
			}
		}
	}
}

bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//trueの時
		if (g_Block[nCntBlock].used)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectBlockMax = D3DXVECTOR3(g_Block[nCntBlock].size.x / 2,
				g_Block[nCntBlock].size.y / 2, g_Block[nCntBlock].size.z / 2) + g_Block[nCntBlock].pos;
			D3DXVECTOR3 rectBlockMin = D3DXVECTOR3(-g_Block[nCntBlock].size.x / 2,
				-g_Block[nCntBlock].size.y / 2, -g_Block[nCntBlock].size.z / 2) + g_Block[nCntBlock].pos;


			if (rectPlayerMax.x > rectBlockMin.x &&//blockから見て左
				rectPlayerMin.x < rectBlockMax.x &&//blockから見て右
				rectPlayerMax.z > rectBlockMin.z &&//blockから見て下
				rectPlayerMin.z < rectBlockMax.z) //blockから見て上
			{
				if (rectPlayerMax.x > rectBlockMin.x &&
					pPosOld->x + (size.x / 2) <= rectBlockMin.x)
				{//左
					pPos->x = rectBlockMin.x - (size.x / 2);
				}

				if (rectPlayerMin.x < rectBlockMax.x &&
					pPosOld->x + (size.x / 2) >= rectBlockMax.x)
				{//右
					pPos->x = + rectBlockMax.x + (size.x / 2);
				}

				if (rectPlayerMax.z > rectBlockMin.z &&
					pPosOld->z + (size.z / 2) <= rectBlockMin.z)
				{//前
					pPos->z = rectBlockMin.z - (size.z / 2);
				}

				if (rectPlayerMin.z < rectBlockMax.z &&
					pPosOld->z + (size.z / 2) >= rectBlockMax.z)
				{//上
					pPos->z = rectBlockMax.z + (size.z / 2);
				}
			}
		}
	}
	return isGround;
}
BLOCK*GetBlock(void)
{
	return &g_Block[0];
}