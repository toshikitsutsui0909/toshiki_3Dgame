//=============================================================================
//
// DirectX���^���� [polygon.cpp]
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
//�O���[�o���ϐ�
//=============================================================================

//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;

//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;

//�e
ENEMY g_Enemy;

//=============================================================================
//����������
//=============================================================================
void InitEnemy(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	D3DXCreateTextureFromFile(pDevice, "texture/016.png", &g_pTextureEnemy);

	VERTEX_3D * pVtx = NULL;


	//���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_Enemy.use = false;
	g_Enemy.play = false;
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-50.0f / 2, 50.0f / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f / 2, 50.0f / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f / 2, -50.0f / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f / 2, -50.0f / 2, 0.0f);

		//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();

}

//=============================================================================
//�I������
//=============================================================================
void UninitEnemy(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

}
//=============================================================================
//�X�V����
//=============================================================================
void UpdateEnemy(void)
{
	CAMERA*pCamera = GetCamera();
	PLAYER*pPlayer = GetPlayer();

	//�v���C���[�Ǝ����Ƃ̊p�x�𖈉񋁂߂�
	g_Enemy.fAngle = atan2f((-g_Enemy.pos.x - -pCamera->posV.x),
		(-g_Enemy.pos.z - -pCamera->posV.z));

	//���߂��p�x�Ɍ������Ĉړ��ʂɉ��Z
	g_Enemy.move.x = sinf(g_Enemy.fAngle) * 0.5f;
	g_Enemy.move.z = cosf(g_Enemy.fAngle) * 0.5f;
	//�ʒu�X�V
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
	D3DXVec3Normalize(&rot, &rot);//���K������i�傫���P�̃x�N�g���ɂ���K�v������j

	if (!g_Enemy.use)
	{
		g_Enemy.use = true;
		g_Enemy.pos = pos;
		g_Enemy.rot = rot;
		g_Enemy.size = size;
	}
}
//=============================================================================
//�`�揈��
//=============================================================================
void DrawEnemy(void)
{

	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�s��v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans;
	PLAYER*pPlayer = GetPlayer();
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->LightEnable(0, FALSE);
	if (g_Enemy.use)
	{
		pDevice->SetTexture(0, g_pTextureEnemy);

		//���[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&g_Enemy.mtxWorld);
		//�J�X�̋t�s��𐶐�
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&g_Enemy.mtxWorld, NULL, &mtxRot);
		g_Enemy.mtxWorld._41 = 0;
		g_Enemy.mtxWorld._42 = 0;
		g_Enemy.mtxWorld._43 = 0;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Enemy.pos.x, g_Enemy.pos.y,
			g_Enemy.pos.z);
		D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxTrans);
		
		//�A���t�@�e�X�g��L����
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		//�A���t�@�e�X�g��l�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//�A���t�@�e�X�g�̔�r���@�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.mtxWorld);

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�|���S���̕`��
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
	//true�̎�
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


		if (rectPlayerMax.x > rectEnemyMin.x &&//block���猩�č�
			rectPlayerMin.x < rectEnemyMax.x &&//block���猩�ĉE
			rectPlayerMax.z > rectEnemyMin.z &&//block���猩�ĉ�
			rectPlayerMin.z < rectEnemyMax.z) //block���猩�ď�
		{
			if (rectPlayerMax.x > rectEnemyMin.x &&
				pPosOld->x + (size.x / 2) <= rectEnemyMin.x)
			{//��
				pPos->x = rectEnemyMin.x - (size.x / 2);
			}

			if (rectPlayerMin.x < rectEnemyMax.x &&
				pPosOld->x + (size.x / 2) >= rectEnemyMax.x)
			{//�E
				pPos->x = +rectEnemyMax.x + (size.x / 2);
			}

			if (rectPlayerMax.z > rectEnemyMin.z &&
				pPosOld->z + (size.z / 2) <= rectEnemyMin.z)
			{//�O
				pPos->z = rectEnemyMin.z - (size.z / 2);
			}

			if (rectPlayerMin.z < rectEnemyMax.z &&
				pPosOld->z + (size.z / 2) >= rectEnemyMax.z)
			{//��
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