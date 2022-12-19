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
#include "tps_camera.h"
#include "meshfield.h"
#include "motion_parts.h"
#include "convenience_function.h"
#include "psychokinesis_area.h"
#include "object_type_list.h"
#include "psychokinesis.h"

const D3DXVECTOR3 CPlayer::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const float CPlayer::MOVE_INERTIA = 0.1f;
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
	SetLife(INIT_LIFE);

	SetPos(INIT_POS);

	SetOldPos(INIT_POS);

	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_RotLowerBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_DestRotLowerBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionplayer1.txt"));

	m_nMotionNum1 = cRead.ReadMotion("data/MOTION/motionplayer2.txt");


	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_PLAYER);
	CMotionParts::AllSetObject_Type_List(m_nMotionNum1, OBJ_PLAYER);

	CMotionParts::SettingParent(m_nMotionNum1, GetMotionNum());


	//�T�C�R�L�l�V�X�G���A�̏��̊m��
	m_pPsychokinesis_Area = new CPsychokinesis_Area;

	//������
	if (FAILED(m_pPsychokinesis_Area->Init()))
	{
		return -1;
	}

	//�T�C�R�L�l�V�X�̏��̊m��
	m_pPsychokinesis = new CPsychokinesis;

	//������
	if (FAILED(m_pPsychokinesis->Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CPlayer::Uninit()
{
	//�T�C�R�L�l�V�X�G���A�̉��
	if (m_pPsychokinesis_Area != nullptr)
	{
		//�I������
		m_pPsychokinesis_Area->Uninit();
		delete m_pPsychokinesis_Area;
		m_pPsychokinesis_Area = nullptr;
	}

	//�T�C�R�L�l�V�X�̉��
	if (m_pPsychokinesis != nullptr)
	{
		//�I������
		m_pPsychokinesis->Uninit();
		delete m_pPsychokinesis;
		m_pPsychokinesis = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPlayer::Update()
{
	//�e�N���X�̍X�V
	CMovable_Obj::Update();

	//���̓f�o�C�X�̎擾
	CInput *pInput = CInput::GetKey();

	//�}�l�[�W���[����Q�[���I�u�W�F�N�g�̎擾
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();

	CTpsCamera* pTpsCamera = (CTpsCamera*)pGame->GetCamera();

	//�J�����̌����iY���̂݁j
	float rotY = pTpsCamera->GetRot();

	//�ړ��ʂ̈ꎞ�ۊ�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�ړ�
	if (pInput->Press(DIK_W))
	{//��L�[�������ꂽ
		if (pInput->Press(DIK_A))
		{
			move.x -= sinf(rotY + D3DX_PI * 0.75f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * 0.75f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			move.x -= sinf(rotY + D3DX_PI * -0.75f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * -0.75f) * 5.0f;
		}
		else
		{
			move.x += sinf(rotY) * 5.0f;
			move.z += cosf(rotY) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_S))
	{//���L�[�������ꂽ
		if (pInput->Press(DIK_A))
		{
			move.x -= sinf(rotY + D3DX_PI * 0.25f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * 0.25f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			move.x -= sinf(rotY + D3DX_PI * -0.25f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * -0.25f) * 5.0f;
		}
		else
		{
			move.x += sinf(rotY + D3DX_PI) * 5.0f;
			move.z += cosf(rotY + D3DX_PI) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_A))
	{//���L�[�������ꂽ
		move.x += sinf(rotY + D3DX_PI * -0.5f) * 5.0f;
		move.z += cosf(rotY + D3DX_PI * -0.5f) * 5.0f;
	}
	else if (pInput->Press(DIK_D))
	{//�E�L�[�������ꂽ
		move.x += sinf(rotY + D3DX_PI * 0.5f) * 5.0f;
		move.z += cosf(rotY + D3DX_PI * 0.5f) * 5.0f;
	}

	//�ړ��ʂɕύX���������ꍇ�ړ���ۊ�
	if (move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		if (pInput->Press(DIK_S))
		{
			move *= 0.6f;
		}
		else if (pInput->Press(DIK_LSHIFT))
		{
			move *= 2.0f;
		}

		SetMove(move);
	}

	//���Ƃ̓����蔻��p�ϐ�
	D3DXVECTOR3 pos, groundpos;

	//���݂̃v���C���[�̈ʒu
	pos = GetPos();

	//�v���C���[�����鏰�̍���
	groundpos = pGame->GetMeshfield()->Collision(pos);

	//�v���C���[�����鏰�̍������v���C���[���ゾ������
	if (pos.y < groundpos.y)
	{
		if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			pos = groundpos;
			SetPos(groundpos);
		}
	}

	//�v���C���[������̍�����艺��������
	if (pos.y < -100.0f)
	{
		pos.y = 0.0f;
		SetPos(pos);
	}

	//�v���C���[���J�����̌��Ă�����ɂ���
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, rotY + D3DX_PI, 0.0f);

	//Rot�̕ۊ�
	SetRot(rot);

	//���݂͎g���Ă��Ȃ��i�e�̔���j
	/*if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		CMotionParts::AllSetShadowPos(groundpos, GetMotionNum());
	}*/

	//���݂̃v���C���[�̈ʒu
	D3DXVECTOR3 PLpos = GetPos();

	//�Đ����郂�[�V�����ԍ�
	int nMotionNumUp = 0;
	int nMotionNumDown = 0;

	//�v���C���[�������Ă�����
	if (pInput->Press(KEY_MOVE))
	{
		if (pInput->Press(KEY_DOWN))
		{
			//�������p�̃��[�V�����ԍ�
			nMotionNumUp = 3;
		}
		else if (pInput->Press(DIK_LSHIFT))
		{
			//�_�b�V���p�̃��[�V�����ԍ�
			nMotionNumUp = 2;
		}
		else
		{
			//����p�̃��[�V�����ԍ�
			nMotionNumUp = 1;
		}

		nMotionNumDown = nMotionNumUp;
	}

	if (pInput->Press(MOUSE_INPUT_LEFT))
	{
		//�U�����[�V����
		nMotionNumDown = 7;
		if (!pInput->Press(KEY_MOVE))
		{
			//�U�����[�V����
			nMotionNumUp = 7;
		}
	}




	//�����g�̃��[�V�����ݒ�
	CMotionParts::MoveMotionModel(GetMotionNum(), nMotionNumUp, &PLpos, &rot);
	//�㔼�g�̃��[�V�����ݒ�
	CMotionParts::MoveMotionModel(m_nMotionNum1, nMotionNumDown);






	if (pInput->Press(DIK_0))
	{
		nMotionNumUp = 4;
		nMotionNumDown = 4;
		//�����g�̃��[�V�����ݒ�
		CMotionParts::MoveMotionModel(GetMotionNum(), nMotionNumUp, &PLpos, &rot);
		//�㔼�g�̃��[�V�����ݒ�
		CMotionParts::MoveMotionModel(m_nMotionNum1, nMotionNumDown);
	}


	//���݂̃v���C���[�̈ʒu�̎擾
	PLpos = GetPos();

	//PLpos.y += 1.0f;

	//�T�C�R�L�l�V�X�G���A�̍X�V�iPos����j
	m_pPsychokinesis_Area->Update(PLpos);

	//�T�C�R�L�l�V�X�̍X�V
	m_pPsychokinesis->Update(PLpos, rot, pTpsCamera->GetCameraVec(), m_pPsychokinesis_Area->GetRadius(), m_pPsychokinesis_Area->GetSizeTop());
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPlayer::Draw()
{
	//�T�C�R�L�l�V�X�G���A�̕`��
	m_pPsychokinesis_Area->Draw();
}
