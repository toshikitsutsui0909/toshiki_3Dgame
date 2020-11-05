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
#include "goal.h"
#include "game.h"
#include "sound.h"
//=============================================================================
//グローバル変数
//=============================================================================

GOAL g_goal;
extern int g_nCountItem;
//=============================================================================
//初期化処理
//=============================================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//カメラ情報を取得得する
	CAMERA*camera = GetCamera();

	g_goal.pMeshgoal = NULL;
	g_goal.pBuffMatgoal = NULL;
	g_goal.nNumMatgoal = 0;
	g_goal.used = false;
	//Xファイルの読み込み
	D3DXLoadMeshFromX("texture/車.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_goal.pBuffMatgoal,
		NULL,
		&g_goal.nNumMatgoal,
		&g_goal.pMeshgoal);
}
//=============================================================================
//終了処理
//=============================================================================
void UninitGoal(void)
{
	//メッシュの破棄
	if (g_goal.pMeshgoal != NULL)
	{
		g_goal.pMeshgoal->Release();
		g_goal.pMeshgoal = NULL;
	}
	//マテリアルの破棄
	if (g_goal.pBuffMatgoal != NULL)
	{
		g_goal.pBuffMatgoal->Release();
		g_goal.pBuffMatgoal = NULL;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateGoal(void)
{

}

//=============================================================================
//描画処理
//=============================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保持用
	D3DXMATERIAL*pMat;			//マテリアルデータへのポインタ
	
	if (g_goal.used)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_goal.mtxWorldgoal);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_goal.rot.x, g_goal.rot.y,
			g_goal.rot.z);
		D3DXMatrixMultiply(&g_goal.mtxWorldgoal, &g_goal.mtxWorldgoal, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_goal.pos.x, g_goal.pos.y,
			g_goal.pos.z);
		D3DXMatrixMultiply(&g_goal.mtxWorldgoal, &g_goal.mtxWorldgoal, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD,
			&g_goal.mtxWorldgoal);

		//現在のマテリアルを取得する
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_goal.pBuffMatgoal->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_goal.nNumMatgoal; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//モデルパーツの描画
			g_goal.pMeshgoal->DrawSubset(nCntMat);
		}
		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}
void SetGoal(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	g_goal.pos = pos;
	g_goal.size = size;
}
bool CollisionGoal(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();
	CAMERA*pCamera = GetCamera();
	int nCountItem = 0;

		//trueの時
		if (g_goal.used)
		{

			D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
				size.y / 2, size.z / 2) + *pPos;
			D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
				-size.y / 2, -size.z / 2) + *pPos;
			D3DXVECTOR3 rectItemMax = D3DXVECTOR3(g_goal.size.x / 2,
				g_goal.size.y / 2, g_goal.size.z / 2) + g_goal.pos;
			D3DXVECTOR3 rectItemMin = D3DXVECTOR3(-g_goal.size.x / 2,
				-g_goal.size.y / 2, -g_goal.size.z / 2) + g_goal.pos;


			if (rectPlayerMax.x > rectItemMin.x &&//blockから見て左
				rectPlayerMin.x < rectItemMax.x &&//blockから見て右
				rectPlayerMax.z > rectItemMin.z &&//blockから見て下
				rectPlayerMin.z < rectItemMax.z) //blockから見て上
			{
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
				PlaySound(SOUND_LABEL_SE_GOAL);
				SetGameState(GAMESTATE_CLEAR);
			}
		}
	return isGround;
}
GOAL*GetGoal(void)
{
	return &g_goal;
}
