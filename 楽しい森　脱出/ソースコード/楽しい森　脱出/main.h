//=============================================================================
//
// DirectX���^���� [main.h]
// Author :tutui
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

// DirectInput�o�[�W�����̐錾
//#define DIRECTINPUT_VERSION 0x0800

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <windows.h>
#include "d3dx9.h"
#include <dinput.h>
#include <xaudio2.h>
//=============================================================================
// ���C�u�����̃����N
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�p�ɕK�v
#pragma comment(lib,"dinput8.lib")
//=============================================================================
// �}�N����`
//=============================================================================
typedef struct
{

	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//�I�����_���W
	D3DXVECTOR3 nor;	//�I���@���x�N�g��
	D3DCOLOR col;		//�I�����_�J���[
	D3DXVECTOR2 tex;
}VERTEX_3D;

//���[�h�̎��
typedef enum
{

	MODE_TITLE = 0,		//�^�C�g��
	MODE_TUTORIAL,
	MODE_GAME,			//�Q�[��
	MODE_RESULT,		//���U���g
	MODE_CLEAR,
	MODE_MAX,

}MODE;
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1280)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���W�E�@���E�J���[�E�e�N�X�`��
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define NUM_VERTEX	(4)
#define NUM_POLYGON	(2)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);

void SetMode(MODE mode);
MODE GetMode(void);

#endif

