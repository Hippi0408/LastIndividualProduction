//=============================================================================
//
// ���I���� [ballast_acquired.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "ballast_acquired.h"
#include "convenience_function.h"

const float CBallast_Acquired::GRAVITY = 2.0f;
const float CBallast_Acquired::MOVE_ATTENUATION = 0.05f;
const float CBallast_Acquired::MOVE_MAGNIFICATION = 3.0f;

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBallast_Acquired::CBallast_Acquired()
{
	m_Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBallast_Acquired::~CBallast_Acquired()
{
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBallast_Acquired::Update()
{

	D3DXVECTOR3 move = GetPosMove();

	move += (move - D3DXVECTOR3(0.0f, GRAVITY, 0.0f)) * MOVE_ATTENUATION;

	SetPosMove(move);

	if (GetParentPos().y < 0.0f)
	{
		SetPosMove(D3DXVECTOR3(0.0f,0.0f,0.0f));

		D3DXVECTOR3 pos = GetParentPos();
		SetParentPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));
	}

	//�e�N���X�̍X�V
	CBallast::Update();
}

//*****************************************************************************
// �Ԃ���ԃx�N�g���̐ݒ�
//*****************************************************************************
void CBallast_Acquired::SetVec(D3DXVECTOR3 Vec)
{
	//�ۑ�
	m_Vec = Vec;

	//�ړ���
	D3DXVECTOR3 move = m_Vec * MOVE_MAGNIFICATION;

	SetPosMove(move);
}
