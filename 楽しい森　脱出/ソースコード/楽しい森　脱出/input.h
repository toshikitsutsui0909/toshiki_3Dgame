//=============================================================================
//
// シューティングゲームの作成の処理 [input.h]
// Author : toshiki
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

#endif // !_INPUT_H_