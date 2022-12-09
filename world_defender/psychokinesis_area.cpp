//=============================================================================
//
// �O�Տ��� [psychokinesis_area.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "psychokinesis_area.h" 
#include "locus.h"
#include "texture.h"
#include <assert.h>
#include "convenience_function.h"

const D3DXVECTOR3 CPsychokinesis_Area::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const float CPsychokinesis_Area::HEIGHT_LOCUS = 80.0f;
const float CPsychokinesis_Area::RADIUS_INIT = 200.0f;
const float CPsychokinesis_Area::RADIUS_MOVE = D3DXToRadian(5);
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CPsychokinesis_Area::CPsychokinesis_Area()
{
	m_PLPos = INIT_POS;
	m_LocusPos = INIT_POS;
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove = D3DXVECTOR3(0.0f, RADIUS_MOVE, 0.0f);
	m_fRadius = RADIUS_INIT;
	m_pLocus = nullptr;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CPsychokinesis_Area::~CPsychokinesis_Area()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CPsychokinesis_Area::Init()
{
	//Num�`�F�b�N
	if (m_pLocus != nullptr)
	{
		assert(false);
	}

	//�O�Տ��̊m��
	m_pLocus = new CLocus;

	//������
	if (FAILED(m_pLocus->Init()))
	{
		return -1;
	}

	//���̈ꎞ�ۊǗp�ϐ��錾
	LocusStructure locusstructure;
	D3DXVECTOR3 PLpos = m_PLPos;
	

	//�o������O�Ղ̏㉺��Pos�̐ݒ�
	D3DXVECTOR3 pos;
	pos.x = m_fRadius * cosf(m_Rot.y);
	pos.z = m_fRadius * sinf(m_Rot.y);
	pos.y = 0.0f;
	locusstructure.TopPos = PLpos + D3DXVECTOR3(pos.x, HEIGHT_LOCUS, pos.z);
	locusstructure.DownPos = PLpos + pos;

	//�o���n�߂ƏI���̃J���[�ݒ�
	locusstructure.BeginningCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	locusstructure.EndCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�����ŕ\�����邩
	locusstructure.nPolygon = 24;

	//Pos�̍X�V�t���[����
	locusstructure.nSaveInterval = 3;

	//�e�N�X�`���̓ǂݍ���
	locusstructure.nTextureNum = CTexture::LoadTexture("data/TEXTURE/�O��.png");

	//�ꎞ�ۊǂ������̐ݒ�
	m_pLocus->SetLocus(locusstructure);


	return S_OK;
}

//*****************************************************************************
// ������(Pos����)
//*****************************************************************************
HRESULT CPsychokinesis_Area::Init(D3DXVECTOR3 Pos)
{
	//�v���C���[�̈ʒu�̕ۊ�
	m_PLPos = Pos;

	//������
	if (FAILED(Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPsychokinesis_Area::Uninit()
{
	//�O�Ղ̏��̉��
	if (m_pLocus != nullptr)
	{
		//�I������
		m_pLocus->Uninit();
		delete m_pLocus;
		m_pLocus = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPsychokinesis_Area::Update()
{
	//Rot�̍X�V
	m_Rot += m_RotMove;

	//���K��
	m_Rot = CConvenience_Function::NormalizationRot(m_Rot);

	//�o������O�Ղ̏㉺��Pos�̐ݒ�
	D3DXVECTOR3 pos,posUp,posDown;
	pos.x = m_fRadius * cosf(m_Rot.y);
	pos.z = m_fRadius * sinf(m_Rot.y);
	pos.y = 0.0f;

	posUp = m_PLPos + D3DXVECTOR3(pos.x, HEIGHT_LOCUS, pos.z);
	posDown = m_PLPos + pos;

	m_pLocus->Update(posUp, posDown);
}

//*****************************************************************************
// �X�V����(�I�[�o�[���[�hPos�X�V����)
//*****************************************************************************
void CPsychokinesis_Area::Update(D3DXVECTOR3 Pos)
{
	//�v���C���[�̈ʒu�̍X�V
	m_PLPos = Pos;

	//�X�V����
	Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPsychokinesis_Area::Draw()
{
	//�`�揈��
	m_pLocus->Draw();
}

