//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"


//=============================================================================
//�}�N����`
//=============================================================================
#define MESHFIELD_X_BLOCK 100//X�����̃u���b�N��
#define MESHFIELD_Z_BLOCK 100//Y�����̃u���b�N��
#define MESH_LENGTH 20	//��Ђ̒���
#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))	//���_��
#define MESHFIELD_INDEX_NUM (((MESHFIELD_X_BLOCK+1)*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)	//�C���f�b�N�X��
#define MESHFIELD_PRIMITIVE_NUM	((MESHFIELD_X_BLOCK*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*4)	//�|���S����



//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);


#endif








////=============================================================================
////
//// DirectX���^���� [light.h]
//// Author :tutui
////
////=============================================================================
//
////=============================================================================
//// �C���N���[�h�t�@�C��
////=============================================================================
//#include "main.h"
//
////=============================================================================
//// �}�N����`
////=============================================================================
//#define MESHFIELD_X_BLOCK 2		//X�����̃u���b�N��
//#define MESHFIELD_Z_BLOCK 2		//Z�����̃u���b�N��
//#define MESHFIELD_LENGTH 100	//��Ђ̒���
//#define MESHFILED_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))				//���_��
//#define MESHFILED_INDEX_NUM (((MESHFIELD_X_BLOCK+1)*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)	//�C���f�b�N�X��
//#define MESHFILED_PREMITIVE_NUM ((MESHFIELD_Z_BLOCK*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*4)	//�|���S����
////=============================================================================
//// �v���g�^�C�v�錾
////=============================================================================
//void InitMeshField(void);
//void UninitMeshField(void);
//void UpdateMeshField(void);
//void DrawMeshField(void);