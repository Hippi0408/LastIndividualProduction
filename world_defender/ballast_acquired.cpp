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
#include "manager.h"
#include "game.h"
#include "meshfield.h"
#include "ballast_manager.h"

const float CBallast_Acquired::GRAVITY = -0.5f;
const float CBallast_Acquired::MOVE_ATTENUATION = 0.1f;
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

	move += (move - D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * MOVE_ATTENUATION;

	SetPosMove(move);

	if (GetParentPos().y < 0.0f)
	{
		SetPosMove(D3DXVECTOR3(0.0f,0.0f,0.0f));

		D3DXVECTOR3 pos = GetParentPos();
		SetParentPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));

		CManager* pManager = GetManager();
		CGame* pGame = (CGame*)pManager->GetGameObject();
		CMeshfield* pMeshfield = pGame->GetMeshfield();
		//�}�b�v�`�b�v�̔ԍ�
		int nMap = pMeshfield->CheckPosLocation(GetParentPos());
		//��L�̕ۑ�
		SetListNumber(nMap);

		CBallast_Manager* pBallast_Manager = pGame->GetBallast_Manager();

		//���X�g�̓���ւ�
		pBallast_Manager->ReplacementList(this, nMap);
	}
	else if(GetParentPos().y > 0.0f)
	{
		move.y += GRAVITY;

		SetPosMove(move);
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
