#ifndef _UI_H_
#define _UI_H_

#include "main.h"

//構造体定義
typedef struct
{
	int nPatternAnim;
	bool use;
}UI;

void InitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);

UI * GetUi(void);

#endif // !_Ui_H_
