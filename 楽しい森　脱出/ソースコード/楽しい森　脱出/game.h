//=============================================================================
//
// �V���[�e�B���O�Q�[���̍쐬�̏��� [game.h]
// Author : toshiki
//
//=============================================================================
#ifndef _GAME_H
#define _GAME_H
#define _CRT_SECURE_NO_WARNINGS

//�C���N���[�h�t�@�C��
#include "main.h"

//�Q�[�����
typedef enum
{

	GAMESTATE_NONE = 0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,  //�ʏ���
	GAMESTATE_CLEAR,   //�N���A���
	GAMESTATE_END,	   //�Q�[���I����ԁi��ʈڊJ�n�҂���ԁj
	GAMESTATE_MAX

}GAMESTATE;
//�v���g�^�C�v�錾
void SetGameState(GAMESTATE state);

GAMESTATE GetGameState(void);

void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void InitMous(void);

#endif