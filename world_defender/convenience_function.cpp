//=============================================================================
//
// convenience_function.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "convenience_function.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CConvenience_Function::CConvenience_Function()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CConvenience_Function::~CConvenience_Function()
{
}

//*****************************************************************************
// Rot�̐��K��
//*****************************************************************************
D3DXVECTOR3 CConvenience_Function::NormalizationRot(D3DXVECTOR3 In)
{
	D3DXVECTOR3 rot = In;

	if (rot.x > D3DX_PI)
	{
		rot.x -= D3DX_PI * 2.0f;
	}
	else if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}

	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	if (rot.z > D3DX_PI)
	{
		rot.z -= D3DX_PI * 2.0f;
	}
	else if (rot.z < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2.0f;
	}

	return rot;
}

//*****************************************************************************
// �~���m�̓����蔻��
//*****************************************************************************
bool CConvenience_Function::CircleCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//�ʒu�̕ۑ�
	D3DXVECTOR3 Pos1 = pos1;
	D3DXVECTOR3 Pos2 = pos2;

	//�Q���̕��̂̔��a���m�̘a
	float fDiff = fRadius1 + fRadius2;

	//�v�Z�p�ϐ�
	float fCalculationX, fCalculationZ;

	//X�̍���
	fCalculationX = Pos1.x - Pos2.x;
	//Y�̍���
	fCalculationZ = Pos1.z - Pos2.z;

	//���݂̂Q�_�̋���
	float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationZ * fCalculationZ);

	//�Q���̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
	if (fDiff >= fLength)
	{
		//��������
		return true;
	}

	//�������ĂȂ�
	return false;
}

//*****************************************************************************
// �����m�̓����蔻��
//*****************************************************************************
bool CConvenience_Function::SphereCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//�ʒu�̕ۑ�
	D3DXVECTOR3 Pos1 = pos1;
	D3DXVECTOR3 Pos2 = pos2;

	//�Q���̕��̂̔��a���m�̘a
	float fDiff = fRadius1 + fRadius2;

	//�v�Z�p�ϐ�
	D3DXVECTOR3 Distance;

	//2�_�Ƃ̋���
	Distance = Pos1 - Pos2;

	//���݂̂Q�_�̋���
	float fLength = sqrtf(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);

	//�Q���̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
	if (fDiff >= fLength)
	{
		//��������
		return true;
	}

	//�������ĂȂ�
	return false;
}
