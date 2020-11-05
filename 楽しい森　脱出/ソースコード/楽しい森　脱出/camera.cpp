//=============================================================================
//
// DirectX雛型処理 [camera.cpp](自機キャラクター目線）
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
//=============================================================================
//グローバル変数
//=============================================================================
CAMERA g_camera;//カメラ情報

//=============================================================================
//初期化処理
//=============================================================================
void InitCamera(void)
{
	g_camera.fCamera = 0.9f;
	//カメラの位置・注視点・上方向を指定する　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
	g_camera.posV = D3DXVECTOR3(0.0f, 20.0f, -100.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.fDistance = g_camera.posR.z - g_camera.posV.z;

	/*GetCursorPos(&g_CursorPosOld);*/
}

//=============================================================================
//終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
//更新処理
//==========================================================================
void UpdateCamera(void)
{
	g_camera.posVOld = g_camera.posV;
	if (g_camera.use = true)
	{
		//前
		if (GetKeyboardPress(DIK_W))
		{
			g_camera.posV.x += sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;
			g_camera.posV.z += cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;

			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		}

		//後
		if (GetKeyboardPress(DIK_S))
		{
			g_camera.posV.x -= sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;
			g_camera.posV.z -= cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fCamera;

			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;

			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y)) * g_camera.fDistance;
		}

		//右
		if (GetKeyboardPress(DIK_D))
		{
			g_camera.rot.y += 1.1f;
			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
		}
		//左
		if (GetKeyboardPress(DIK_A))
		{
			g_camera.rot.y -= 1.1f;
			g_camera.posR.x = g_camera.posV.x + sinf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
			g_camera.posR.z = g_camera.posV.z + cosf(D3DXToRadian(g_camera.rot.y))*g_camera.fDistance;
		}
	}
}

//=============================================================================
//なんかカメラセットするやつ
//=============================================================================
void SetCamera(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1500.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_camera.mtxProjection);

}

CAMERA*GetCamera()
{
	return &g_camera;
}