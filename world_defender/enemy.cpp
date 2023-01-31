//=============================================================================
//
// enemy.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy.h"
#include "read.h"
#include "game.h"
#include "meshfield.h"
#include "motion_parts.h"
#include "player.h"
#include "input.h"
#include "object_type_list.h"
#include "convenience_function.h"

#ifdef _DEBUG
#include "psychokinesis_area.h"
#endif // _DEBUG

const D3DXVECTOR3 CEnemy::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f); 
const float CEnemy::MOVE_INERTIA = 0.1f; 
const float CEnemy::JUMP_INERTIA = 0.1f;
const float CEnemy::INIT_RADIUS = 1600.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy::CEnemy()
{
	CMovable_Obj::SetLife(INIT_LIFE);
	CMovable_Obj::SetRadius(INIT_RADIUS);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy::~CEnemy()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemy::Init()
{



#ifdef _DEBUG
	//�T�C�R�L�l�V�X�G���A�̏��̊m��
	m_pPsychokinesis_Area = new CPsychokinesis_Area;

	//������
	if (FAILED(m_pPsychokinesis_Area->Init()))
	{
		return -1;
	}

#endif // _DEBUG

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEnemy::Uninit()
{

#ifdef _DEBUG
	//�T�C�R�L�l�V�X�G���A�̉��
	if (m_pPsychokinesis_Area != nullptr)
	{
		//�I������
		m_pPsychokinesis_Area->Uninit();
		delete m_pPsychokinesis_Area;
		m_pPsychokinesis_Area = nullptr;
	}
#endif // _DEBUG
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemy::Update()
{
#ifdef _DEBUG
	//�T�C�R�L�l�V�X�G���A�̍X�V�iPos����j
	m_pPsychokinesis_Area->Update(GetPos());

	m_pPsychokinesis_Area->SetRadius(GetRadius());
#endif // _DEBUG

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy::Draw()
{
#ifdef _DEBUG
	//�T�C�R�L�l�V�X�G���A�̕`��
	m_pPsychokinesis_Area->Draw();
#endif // _DEBUG
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemy::IsUnused()
{
	//���C�t�̊m�F
	if (CMovable_Obj::CheckLife())
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// ���[�V�������f���̐ݒ菈��
//*****************************************************************************
void CEnemy::SetMotionModel()
{
}
