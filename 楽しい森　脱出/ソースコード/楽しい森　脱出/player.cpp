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
#include "enemy.h"
#include "goal.h"
#include "model.h"
#include "sound.h"
//=============================================================================
//グローバル変数
//=============================================================================
LPD3DXMESH g_pMeshPlayer = NULL;			//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;	//マテリアル情報へのポインタ
DWORD g_nNumMatPlayer = 0;		//マテリアル情報の数
D3DXMATRIX g_mtxWorldPlayer;		//ワールドマトリックス
int g_dirPlayer;
D3DXVECTOR3 dirPlayer;

PLAYER g_player;
CAMERA g_cameraPlayer;
//=============================================================================
//初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//カメラ情報を取得得する
	CAMERA*camera = GetCamera();
	g_player.use = true;
	g_player.walk = true;
	//Xファイルの読み込み
	D3DXLoadMeshFromX("texture/ziki.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_nNumMatPlayer,
		&g_pMeshPlayer);

	g_player.movePos = D3DXVECTOR3(0.0f, 15.0f, -100.0f);
	g_player.moveRot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_player.moveRot.y = D3DXToRadian(camera->rot.y);
	g_cameraPlayer.fCamera = 0.9f;
	g_cameraPlayer.fDistance = 10.0f;
	dirPlayer = D3DXVECTOR3(-sinf(D3DXToRadian(camera->rot.y)), 0, -cosf(D3DXToRadian(camera->rot.y)));

}
//=============================================================================
//終了処理
//=============================================================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
	StopSound();
}

//=============================================================================
//更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//カメラ情報を取得得する
	CAMERA*camera = GetCamera();

	//カメラの向きから、前後左右にモデルを移動させる
	
	g_player.posOld = g_player.movePos;
	if (g_player.walk = true)
	{
		//前
		if (GetKeyboardPress(DIK_W))
		{
			g_dirPlayer = 1;
			g_player.movePos.x += sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;
			g_player.movePos.z += cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;

			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;

			g_cameraPlayer.posV.z = g_player.movePos.z +
				cosf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;
		}

		//後
		if (GetKeyboardPress(DIK_S))
		{
			g_dirPlayer = 2;
			g_player.movePos.x -= sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;
			g_player.movePos.z -= cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fCamera;

			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;

			g_cameraPlayer.posV.z = g_player.movePos.z +
				cosf(D3DXToRadian(g_cameraPlayer.rot.y)) * g_cameraPlayer.fDistance;
		}
		//右
		if (GetKeyboardPress(DIK_D))
		{
			g_dirPlayer = 3;
			g_cameraPlayer.rot.y += 0.8f;
			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
			g_cameraPlayer.posV.z = g_player.movePos.z + cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
		}

		//左
		if (GetKeyboardPress(DIK_A))
		{
			g_dirPlayer = 4;
			g_cameraPlayer.rot.y -= 0.8f;
			g_cameraPlayer.posV.x = g_player.movePos.x + sinf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
			g_cameraPlayer.posV.z = g_player.movePos.z + cosf(D3DXToRadian(g_cameraPlayer.rot.y))*g_cameraPlayer.fDistance;
		}

		switch (g_dirPlayer)
		{
		case 1:
			dirPlayer = D3DXVECTOR3(sinf(D3DXToRadian(camera->rot.y)), 0, cosf(D3DXToRadian(camera->rot.y)));
			break;
		case 2:
			dirPlayer = D3DXVECTOR3(-sinf(D3DXToRadian(camera->rot.y + 90)), 0, -cosf(D3DXToRadian(camera->rot.y + 90)));
			break;
		case 3:
			dirPlayer = D3DXVECTOR3(-sinf(D3DXToRadian(camera->rot.y)), 0, -cosf(D3DXToRadian(camera->rot.y)));
			break;
		case 4:
			dirPlayer = D3DXVECTOR3(sinf(D3DXToRadian(camera->rot.y + 90)), 0, cosf(D3DXToRadian(camera->rot.y + 90)));
			break;
		default:
			break;
		}

		if (CollisionBlock(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionItem(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionBlock(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionItem(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionEnemy(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionEnemy(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionGoal(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionGoal(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionModel(&camera->posV, &camera->posVOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
		if (CollisionModel(&g_player.movePos, &g_player.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
		{
		}
	}
	
}

//=============================================================================
//描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保持用
	D3DXMATERIAL*pMat;			//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.moveRot.y, g_player.moveRot.x,
		g_player.moveRot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.movePos.x, g_player.movePos.y,
		g_player.movePos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD,
		&g_mtxWorldPlayer);


	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//モデルパーツの描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}

PLAYER*GetPlayer()
{
	return &g_player;
}
