//=============================================================================
//
// DirectX���^���� [light.cpp]
// Author :tutui
//
//=============================================================================

#include "main.h"
#include "player.h"
#include "camera.h"
#include "light.h"

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================

D3DLIGHT9 g_light;//���C�g���
POINT g_cursorPosOld;
//=============================================================================
//����������
//=============================================================================
void InitLight(void)
{
	CAMERA*pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^
	GetCursorPos(&g_cursorPosOld);
	D3DXVECTOR3 vecDir;//���C�g�̕����x�N�g��
	//���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));
	//���C�g�̎�ނ�ݒ�
	g_light.Type = D3DLIGHT_SPOT;
	//���C�g�̊g�U����ݒ�
	g_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���C�g�̌��̐F��ݒ�
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
		//���C�g�̕�����ݒ�
	vecDir = pCamera->posR - pCamera->posV;
		//pCamera->posR - pCamera->posV;
	D3DXVec3Normalize(&vecDir, &vecDir);//���K������i�傫���P�̃x�N�g���ɂ���K�v������j

	g_light.Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�A���r�G���g���C�g�i�����j��ݒ肷��
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x01111111);

	//�X�y�L�����i���ʔ��ˁj��L���ɂ���
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
}
//=============================================================================
//�I������
//=============================================================================
void UninitLight(void)
{

}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateLight(void)
{
	CAMERA*pCamera = GetCamera();
	D3DXVECTOR3 vecDir;//���C�g�̕����x�N�g��
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�ւ̃|�C���^
	POINT cursorPos;
	static float mouseMoveX = 0, mouseMoveY = 0;
	GetCursorPos(&cursorPos);

	g_light.Position.x = pCamera->posV.x;
	g_light.Position.y = pCamera->posV.y - 7.0f;
	g_light.Position.z = pCamera->posV.z;

	mouseMoveX += cursorPos.x - g_cursorPosOld.x;
	mouseMoveY += cursorPos.y - g_cursorPosOld.y;
	g_cursorPosOld = cursorPos;
	//���C�g�̕�����ݒ�
	vecDir = pCamera->posR - pCamera->posV;
	D3DXVec3Normalize(&vecDir, &vecDir);//���K������i�傫���P�̃x�N�g���ɂ���K�v������j
	vecDir.x += sinf(D3DXToRadian(pCamera->rot.y + 90)) * mouseMoveX * 0.001f;
	vecDir.z += cosf(D3DXToRadian(pCamera->rot.y + 90)) * mouseMoveX * 0.001f;
	//vecDir.x += sinf(D3DXToRadian(pCamera->rot.y + 180)) * mouseMoveY;
	//vecDir.z += cosf(D3DXToRadian(pCamera->rot.y + 180)) * mouseMoveY;
	//cursorPos.x 
	g_light.Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light);
}
