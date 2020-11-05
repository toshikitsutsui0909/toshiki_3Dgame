//=============================================================================
//
// メッシュフィールド処理 [meshfield.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"


//=============================================================================
//マクロ定義
//=============================================================================
#define MESHFIELD_X_BLOCK 100//X方向のブロック数
#define MESHFIELD_Z_BLOCK 100//Y方向のブロック数
#define MESH_LENGTH 20	//一片の長さ
#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))	//頂点数
#define MESHFIELD_INDEX_NUM (((MESHFIELD_X_BLOCK+1)*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)	//インデックス数
#define MESHFIELD_PRIMITIVE_NUM	((MESHFIELD_X_BLOCK*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*4)	//ポリゴン数



//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);


#endif








////=============================================================================
////
//// DirectX雛型処理 [light.h]
//// Author :tutui
////
////=============================================================================
//
////=============================================================================
//// インクルードファイル
////=============================================================================
//#include "main.h"
//
////=============================================================================
//// マクロ定義
////=============================================================================
//#define MESHFIELD_X_BLOCK 2		//X方向のブロック数
//#define MESHFIELD_Z_BLOCK 2		//Z方向のブロック数
//#define MESHFIELD_LENGTH 100	//一片の長さ
//#define MESHFILED_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))				//頂点数
//#define MESHFILED_INDEX_NUM (((MESHFIELD_X_BLOCK+1)*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)	//インデックス数
//#define MESHFILED_PREMITIVE_NUM ((MESHFIELD_Z_BLOCK*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*4)	//ポリゴン数
////=============================================================================
//// プロトタイプ宣言
////=============================================================================
//void InitMeshField(void);
//void UninitMeshField(void);
//void UpdateMeshField(void);
//void DrawMeshField(void);