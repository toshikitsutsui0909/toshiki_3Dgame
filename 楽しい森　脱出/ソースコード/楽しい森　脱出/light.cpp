//=============================================================================
//
// DirectX雛型処理 [light.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "player.h"
#include "camera.h"
#include "light.h"

//=============================================================================
//グローバル変数
//=============================================================================

D3DLIGHT9 g_light;//ライト情報
POINT g_cursorPosOld;
//=============================================================================
//初期化処理
//=============================================================================
void InitLight(void)
{
	CAMERA*pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ
	GetCursorPos(&g_cursorPosOld);
	D3DXVECTOR3 vecDir;//ライトの方向ベクトル
	//ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	//ライトの種類を設定
	g_light.Type = D3DLIGHT_SPOT;
	//ライトの拡散光を設定
	g_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//ライトの光の色を設定
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_light.Position.x = pCamera->posV.x;
	g_light.Position.y = pCamera->posV.y - 7.0f;
	g_light.Position.z = pCamera->posV.z;

	g_light.Theta = D3DXToRadian(30.0f);
	g_light.Phi = D3DXToRadian(60.0f);

	g_light.Attenuation0 = 0.5f;
	g_light.Attenuation1 = 0;
	g_light.Attenuation2 = 0;

	g_light.Range = 300.0f;

	g_light.Falloff = 3.0f;
		//ライトの方向を設定
	vecDir = pCamera->posR - pCamera->posV;
		//pCamera->posR - pCamera->posV;
	D3DXVec3Normalize(&vecDir, &vecDir);//正規化する（大きさ１のベクトルにする必要がある）

	g_light.Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アンビエントライト（環境光）を設定する
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x01111111);

	//スペキュラ（鏡面反射）を有効にする
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
}
//=============================================================================
//終了処理
//=============================================================================
void UninitLight(void)
{

}
//=============================================================================
//更新処理
//=============================================================================
void UpdateLight(void)
{
	CAMERA*pCamera = GetCamera();
	D3DXVECTOR3 vecDir;//ライトの方向ベクトル
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスへのポインタ
	POINT cursorPos;
	static float mouseMoveX = 0, mouseMoveY = 0;
	GetCursorPos(&cursorPos);

	g_light.Position.x = pCamera->posV.x;
	g_light.Position.y = pCamera->posV.y - 7.0f;
	g_light.Position.z = pCamera->posV.z;

	mouseMoveX += cursorPos.x - g_cursorPosOld.x;
	mouseMoveY += cursorPos.y - g_cursorPosOld.y;
	g_cursorPosOld = cursorPos;
	//ライトの方向を設定
	vecDir = pCamera->posR - pCamera->posV;
	D3DXVec3Normalize(&vecDir, &vecDir);//正規化する（大きさ１のベクトルにする必要がある）
	vecDir.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * mouseMoveX * 0.001f;
	vecDir.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * mouseMoveX * 0.001f;
	//vecDir.x += sinf(D3DXToRadian(pCamera->rot.y + 180)) * mouseMoveY;
	//vecDir.z += cosf(D3DXToRadian(pCamera->rot.y + 180)) * mouseMoveY;
	//cursorPos.x 
	g_light.Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_light);
}
