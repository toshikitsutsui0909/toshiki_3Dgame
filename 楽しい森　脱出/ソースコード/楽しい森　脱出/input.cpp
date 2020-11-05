//=============================================================================
//
// �V���[�e�B���O�Q�[���̍쐬�̏��� [input.cpp]
// Author : toshiki
//
//=============================================================================

#include "main.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_KEY_MAX (256)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECTINPUT8 g_pInput = NULL;					//�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X�u�L�[�{�[�h�v�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̓��͏�񃏁[�N
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̃g���K�[���
BYTE g_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h�̃����[�X���
//=============================================================================
// ����������
//=============================================================================

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{

	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̉��
	if (g_pDevKeyboard != NULL)
	{

		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;

	}
	//DerectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntkey;

	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyStateTrigger[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey])&aKeyState[nCntkey];
			g_aKeyStateRelease[nCntkey] = (g_aKeyState[nCntkey] ^ aKeyState[nCntkey])&aKeyState[nCntkey];
			g_aKeyState[nCntkey] = aKeyState[nCntkey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}


bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

bool GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}