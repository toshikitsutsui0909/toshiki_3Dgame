//=============================================================================
//
// DirectX雛型処理 [camera.h]
// Author : tutui
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

typedef struct
{
	D3DXVECTOR3 posV;	//！＜カメラの座標
	D3DXVECTOR3 posR;	//！＜注視点
	D3DXVECTOR3 vecU;	//！＜上方向ベクトル
	D3DXVECTOR3 rot;	//！＜向き取得用
	D3DXMATRIX mtxProjection;//！＜プロジェクションマトリックス
	D3DXMATRIX mtxView;	//！＜ビューマトリックス
	D3DXVECTOR3 posVDest;//カメラの座標（目的値）
	D3DXVECTOR3 posRDest;//注意点（目的値）
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posVOld;
	float fDistance;	//！＜視点ー注視点の距離
	float fCamera;
	bool use;

}CAMERA;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);

CAMERA * GetCamera(void);