//=============================================================================
//
// DirectX雛型処理 [polygon.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "enemy.h"
#include "wall.h"
#include "player.h"
#include "fade.h"
#include "camera.h"
#include "game.h"
#include "block.h"
#include "model.h"
#include "sound.h"
//=============================================================================
//グローバル変数
//=============================================================================

//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;

//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;

//影
ENEMY g_Enemy;

//=============================================================================
//初期化処理
//=============================================================================
void InitEnemy(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	D3DXCreateTextureFromFile(pDevice, "texture/016.png", &g_pTextureEnemy);

	VERTEX_3D * pVtx = NULL;


	//頂点バッファをロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_Enemy.use = false;
	g_Enemy.play = false;
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-50.0f / 2, 50.0f / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f / 2, 50.0f / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f / 2, -50.0f / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f / 2, -50.0f / 2, 0.0f);

		//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffEnemy->Unlock();

}

//=============================================================================
//終了処理
//=============================================================================
void UninitEnemy(void)
{
	//テクスチャの解放
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
	//頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

}
//=============================================================================
//更新処理
//=============================================================================
void UpdateEnemy(void)
{
	CAMERA*pCamera = GetCamera();
	PLAYER*pPlayer = GetPlayer();

	//プレイヤーと自分との角度を毎回求める
	g_Enemy.fAngle = atan2f((-g_Enemy.pos.x - -pCamera->posV.x),
		(-g_Enemy.pos.z - -pCamera->posV.z));

	//求めた角度に向かって移動量に加算
	g_Enemy.move.x = sinf(g_Enemy.fAngle) * 0.5f;
	g_Enemy.move.z = cosf(g_Enemy.fAngle) * 0.5f;
	//位置更新
	g_Enemy.pos.x += g_Enemy.move.x;
	g_Enemy.pos.z += g_Enemy.move.z;
	D3DXVECTOR3 diff = pPlayer->movePos - g_Enemy.pos;
	float distance = D3DXVec3Length(&diff);
	if (distance < 300.0f && g_Enemy.play == false)
	{
		StopSound(SOUND_LABEL_BGM000);
		PlaySound(SOUND_LABEL_BGM001);
		g_Enemy.play = true;

	}
	if (distance > 300.0f && g_Enemy.play == true)
	{
		StopSound(SOUND_LABEL_BGM001);
		PlaySound(SOUND_LABEL_BGM000);
		g_Enemy.play = false;

	}
	if (CollisionModel(&g_Enemy.pos, &g_Enemy.posOld, D3DXVECTOR3(10.0f, 10.0f, 10.0f)) == true)
	{
	}
}
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	D3DXVec3Normalize(&rot, &rot);//正規化する（大きさ１のベクトルにする必要がある）

	if (!g_Enemy.use)
	{
		g_Enemy.use = true;
		g_Enemy.pos = pos;
		g_Enemy.rot = rot;
		g_Enemy.size = size;
	}
}
//=============================================================================
//描画処理
//=============================================================================
void DrawEnemy(void)
{

	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//行列計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans;
	PLAYER*pPlayer = GetPlayer();
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->LightEnable(0, FALSE);
	if (g_Enemy.use)
	{
		pDevice->SetTexture(0, g_pTextureEnemy);

		//ワールドマトリックス初期化
		D3DXMatrixIdentity(&g_Enemy.mtxWorld);
		//開店の逆行列を生成
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&g_Enemy.mtxWorld, NULL, &mtxRot);
		g_Enemy.mtxWorld._41 = 0;
		g_Enemy.mtxWorld._42 = 0;
		g_Enemy.mtxWorld._43 = 0;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Enemy.pos.x, g_Enemy.pos.y,
			g_Enemy.pos.z);
		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxTrans);
		
		//アルファテストを有効化
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		//アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//アルファテストの比較方法の設定
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.mtxWorld);

		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		pDevice->SetTexture(0, NULL);



	}
	D3DXVECTOR3 v = pPlayer->pos - g_Enemy.pos;
	float length = D3DXVec3Length(&v);
	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
bool CollisionEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3 size)
{
	bool isGround = false;
	PLAYER*pPlayer = GetPlayer();
	CAMERA*pCamera = GetCamera();
	//trueの時
	if (g_Enemy.use)
	{

		D3DXVECTOR3 rectPlayerMax = D3DXVECTOR3(size.x / 2,
			size.y / 2, size.z / 2) + *pPos;
		D3DXVECTOR3 rectPlayerMin = D3DXVECTOR3(-size.x / 2,
			-size.y / 2, -size.z / 2) + *pPos;
		D3DXVECTOR3 rectEnemyMax = D3DXVECTOR3(g_Enemy.size.x / 2,
			g_Enemy.size.y / 2, g_Enemy.size.z / 2) + g_Enemy.pos;
		D3DXVECTOR3 rectEnemyMin = D3DXVECTOR3(-g_Enemy.size.x / 2,
			-g_Enemy.size.y / 2, -g_Enemy.size.z / 2) + g_Enemy.pos;


		if (rectPlayerMax.x > rectEnemyMin.x &&//blockから見て左
			rectPlayerMin.x < rectEnemyMax.x &&//blockから見て右
			rectPlayerMax.z > rectEnemyMin.z &&//blockから見て下
			rectPlayerMin.z < rectEnemyMax.z) //blockから見て上
		{
			if (rectPlayerMax.x > rectEnemyMin.x &&
				pPosOld->x + (size.x / 2) <= rectEnemyMin.x)
			{//左
				pPos->x = rectEnemyMin.x - (size.x / 2);
			}

			if (rectPlayerMin.x < rectEnemyMax.x &&
				pPosOld->x + (size.x / 2) >= rectEnemyMax.x)
			{//右
				pPos->x = +rectEnemyMax.x + (size.x / 2);
			}

			if (rectPlayerMax.z > rectEnemyMin.z &&
				pPosOld->z + (size.z / 2) <= rectEnemyMin.z)
			{//前
				pPos->z = rectEnemyMin.z - (size.z / 2);
			}

			if (rectPlayerMin.z < rectEnemyMax.z &&
				pPosOld->z + (size.z / 2) >= rectEnemyMax.z)
			{//上
				pPos->z = rectEnemyMax.z + (size.z / 2);
			}
			pPlayer->use = false;
			g_Enemy.use = false;
			pCamera->posV.y = 1000.0f;
			SetGameState(GAMESTATE_END);
		}
	}
	return isGround;
}

ENEMY*GetEnemy()
{
	return &g_Enemy;
}