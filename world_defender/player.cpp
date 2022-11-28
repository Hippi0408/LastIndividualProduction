//=============================================================================
//
// player.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "player.h"
#include "input.h"
#include "read.h"
#include "texture.h"
#include "game.h"
#include "camera.h"
#include "meshfield.h"
#include "motion_parts.h"

const D3DXVECTOR3 CPlayer::INIT_POS = D3DXVECTOR3(0.0f,0.0f,0.0f);
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CPlayer::CPlayer()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CPlayer::~CPlayer()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CPlayer::Init()
{
	m_Pos = INIT_POS;

	m_OldPos = INIT_POS;

	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_Rot =  D3DXVECTOR3(0.0f,0.0f,0.0f);

	CRead cRead;

	m_nMotionNum = cRead.ReadMotion("data/MOTION/motionplayer.txt");

	CMotionParts::SetLight(m_Light, m_nMotionNum);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPlayer::Uninit()
{

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPlayer::Update()
{
	CInput *pInput = CInput::GetKey();
	CManager *pManager = GetManager();

	CGame* pGame = (CGame*)pManager->GetGameObject();

	float rotY = pGame->GetCamera()->GetRot();

	D3DXVECTOR3 add = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�ړ�
	if (pInput->Press(DIK_W))
	{//��L�[�������ꂽ
		if (pInput->Press(DIK_A))
		{
			add.x -= sinf(rotY + D3DX_PI * 0.75f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * 0.75f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.75f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * -0.75f) * 5.0f;
		}
		else
		{
			add.x += sinf(rotY) * 5.0f;
			add.z += cosf(rotY) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_S))
	{//���L�[�������ꂽ
		if (pInput->Press(DIK_A))
		{
			add.x -= sinf(rotY + D3DX_PI * 0.25f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * 0.25f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.25f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * -0.25f) * 5.0f;
		}
		else
		{
			add.x += sinf(rotY + D3DX_PI) * 5.0f;
			add.z += cosf(rotY + D3DX_PI) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_A))
	{//���L�[�������ꂽ
		add.x += sinf(rotY + D3DX_PI * -0.5f) * 5.0f;
		add.z += cosf(rotY + D3DX_PI * -0.5f) * 5.0f;
	}
	else if (pInput->Press(DIK_D))
	{//�E�L�[�������ꂽ
		add.x += sinf(rotY + D3DX_PI * 0.5f) * 5.0f;
		add.z += cosf(rotY + D3DX_PI * 0.5f) * 5.0f;
	}

	if (pInput->Trigger(DIK_SPACE))
	{
		m_Move.y += 100;
	}

	if (pInput->Press(DIK_Z))
	{
		m_Rot += (D3DXVECTOR3(0.0f, D3DXToRadian(-10), 0.0f));
	}
	else if (pInput->Press(DIK_X))
	{
		m_Rot += (D3DXVECTOR3(0.0f, D3DXToRadian(10), 0.0f));
	}

	m_Move.y -= 4.0f;

	m_Move.y += (0.0f - m_Move.y) * 0.1f;

	//OldPos�̍X�V
	m_OldPos = m_Pos;


	m_Pos += m_Move;

	m_Pos += add;

	
	D3DXVECTOR3 pos, groundpos;

	pos = m_Pos;

	groundpos = pGame->GetMeshfield()->Collision(pos);

	if (pos.y < groundpos.y)
	{
		if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			pos = groundpos;
			m_Pos = (groundpos);
		}
	}

	if (pos.y < -100.0f)
	{
		pos.y = 0.0f;
		m_Pos = (pos);
	}

	

	if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		CMotionParts::AllSetShadowPos(groundpos, m_nMotionNum);
	}

	if (pInput->Press(KEY_MOVE) || pInput->Press(DIK_0))
	{
		CMotionParts::MoveMotionModel(m_Pos, m_Rot, m_nMotionNum,1);
	}
	else
	{
		CMotionParts::MoveMotionModel(m_Pos, m_Rot, m_nMotionNum,0);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPlayer::Draw()
{
}
