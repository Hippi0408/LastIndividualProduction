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
#include "ballast_manager.h"
#include "enemy_manager.h"
#include "adrenaline_gauge.h"

const D3DXVECTOR3 CPlayer::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
const float CPlayer::PLAYER_GRAVITY = 2.0f;
const float CPlayer::MOVE_NORMAL = 5.0f;
const float CPlayer::MOVE_BACK = MOVE_NORMAL * 0.6;
const float CPlayer::MOVE_DASH = MOVE_NORMAL * 2.0f;
const float CPlayer::MOVE_INERTIA = 0.1f;
const float CPlayer::JUMP_INERTIA = 0.01f;
const float CPlayer::JUMP_POWER = 60.0f;
const float CPlayer::INIT_RADIUS = 60.0f;
const float CPlayer::KNOCK_BACK = 100.0f;
const D3DXVECTOR3 CPlayer::PLAYER_SIZE_MAX = D3DXVECTOR3(15.0f, 100.0f, 15.0f);
const D3DXVECTOR3 CPlayer::PLAYER_SIZE_MIN = D3DXVECTOR3(-15.0f, 0.0f, -15.0f);

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
	m_nMapGrid = 0;

	SetLife(INIT_LIFE);

	SetPos(INIT_POS);

	SetOldPos(INIT_POS);

	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_CameraVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_RotLowerBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_DestRotLowerBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_bJump = false;

	m_bHit = false;

	m_nInvincibleTime = 0;

	SetRadius(INIT_RADIUS);

	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionplayer1.txt"));

	m_nMotionNum1 = cRead.ReadMotion("data/MOTION/motionplayer2.txt");


	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_PLAYER);
	CMotionParts::AllSetObject_Type_List(m_nMotionNum1, OBJ_PLAYER);

	CMotionParts::SettingParent(m_nMotionNum1, GetMotionNum());

	CMotionParts::SetLight(GetLight(), GetMotionNum());
	CMotionParts::SetLight(GetLight(), m_nMotionNum1);


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

	//�A�h���i�����Q�[�W
	m_pAdrenaline_Gauge = new CAdrenaline_Gauge;
	if (FAILED(m_pAdrenaline_Gauge->Init()))
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

	//�A�h���i�����Q�[�W�̉��
	if (m_pAdrenaline_Gauge != nullptr)
	{
		//�I������
		m_pAdrenaline_Gauge->Uninit();
		delete m_pAdrenaline_Gauge;
		m_pAdrenaline_Gauge = nullptr;
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CPlayer::Update()
{
	//���̓f�o�C�X�̎擾
	CInput *pInput = CInput::GetKey();

	//�e�N���X�̍X�V
	CMovable_Obj::Update();

	// �����蔻��n����
	Collision();

	//�_���[�W���͓����Ȃ�
	if (!m_bHit)
	{
		//�ړ��̏����̍X�V
		Move();
	}

	// ���[�V��������
	Motion();

	//���G���Ԃ̍X�V
	if (m_bHit)
	{
		if (m_nInvincibleTime > 0)
		{
			m_nInvincibleTime--;
		}
		else
		{
			m_nInvincibleTime = 0;

			m_bHit = false;
		}
	}

	//���݂̃v���C���[�̈ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();

	//�T�C�R�L�l�V�X�G���A�̍X�V�iPos����j
	m_pPsychokinesis_Area->Update(pos);

	//�T�C�R�L�l�V�X�̍X�V
	m_pPsychokinesis->Update(m_nMapGrid, pos, GetRot(), m_CameraVec, m_pPsychokinesis_Area->GetRadius(), m_pPsychokinesis_Area->GetSizeTop());

	//�A�h���i�����Q�[�W�X�V����
	m_pAdrenaline_Gauge->Update();


	if (pInput->Trigger(DIK_T))
	{
		m_pAdrenaline_Gauge->AddGauge(10);
	}


	
	CMotionParts::AllSetShadowPos(D3DXVECTOR3(pos.x, 2.0f, pos.z), GetMotionNum());
	CMotionParts::AllSetShadowPos(D3DXVECTOR3(pos.x,2.0f, pos.z), m_nMotionNum1);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CPlayer::Draw()
{
	//�T�C�R�L�l�V�X�G���A�̕`��
	m_pPsychokinesis_Area->Draw();

	//�A�h���i�����Q�[�W�`�揈��
	m_pAdrenaline_Gauge->Draw();
}

//*****************************************************************************
// �ړ�����
//*****************************************************************************
void CPlayer::Move()
{
	//���̓f�o�C�X�̎擾
	CInput *pInput = CInput::GetKey();

	//�}�l�[�W���[����Q�[���I�u�W�F�N�g�̎擾
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();

	//�J�����̏��
	CTpsCamera* pTpsCamera = (CTpsCamera*)pGame->GetCamera();

	//�J�����̃x�N�g���̕ۑ�
	m_CameraVec = pTpsCamera->GetCameraVec();

	//�J�����̌����iY���̂݁j
	float rotY = pTpsCamera->GetRot();

	//�ړ��ʂ̈ꎞ�ۊ�
	D3DXVECTOR3 move = GetMove();

	//Move�{��
	float fMove = MOVE_NORMAL;

	if (pInput->Press(DIK_S))
	{
		fMove = MOVE_BACK;
	}
	else if (pInput->Press(DIK_LSHIFT))
	{
		fMove = MOVE_DASH;
	}


	//���_�ړ�
	if (pInput->Press(KEY_UP))
	{//��L�[�������ꂽ
		if (pInput->Press(KEY_LEFT))
		{
			move.x = -sinf(rotY + D3DX_PI * 0.75f) * fMove;
			move.z = -cosf(rotY + D3DX_PI * 0.75f) * fMove;
		}
		else if (pInput->Press(KEY_RIGHT))
		{
			move.x = -sinf(rotY + D3DX_PI * -0.75f) * fMove;
			move.z = -cosf(rotY + D3DX_PI * -0.75f) * fMove;
		}
		else
		{
			move.x = sinf(rotY) * fMove;
			move.z = cosf(rotY) * fMove;
		}
	}
	else if (pInput->Press(KEY_DOWN))
	{//���L�[�������ꂽ
		if (pInput->Press(KEY_LEFT))
		{
			move.x = -sinf(rotY + D3DX_PI * 0.25f) * fMove;
			move.z = -cosf(rotY + D3DX_PI * 0.25f) * fMove;
		}
		else if (pInput->Press(KEY_RIGHT))
		{
			move.x = -sinf(rotY + D3DX_PI * -0.25f) * fMove;
			move.z = -cosf(rotY + D3DX_PI * -0.25f) * fMove;
		}
		else
		{
			move.x = sinf(rotY + D3DX_PI) * fMove;
			move.z = cosf(rotY + D3DX_PI) * fMove;
		}
	}
	else if (pInput->Press(KEY_LEFT))
	{//���L�[�������ꂽ
		move.x = sinf(rotY + D3DX_PI * -0.5f) * fMove;
		move.z = cosf(rotY + D3DX_PI * -0.5f) * fMove;
	}
	else if (pInput->Press(KEY_RIGHT))
	{//�E�L�[�������ꂽ
		move.x = sinf(rotY + D3DX_PI * 0.5f) * fMove;
		move.z = cosf(rotY + D3DX_PI * 0.5f) * fMove;
	}

	//�W�����v
	if (pInput->Trigger(DIK_SPACE) && !m_bJump)
	{
		m_bJump = true;
		move.y += JUMP_POWER;
	}
	else if (m_bJump)
	{
		
	}
	

	//�ړ��ʂ�ۊ�
	SetMove(move);

	
}

//*****************************************************************************
// �����蔻��n����
//*****************************************************************************
void CPlayer::Collision()
{
	//�}�l�[�W���[����Q�[���I�u�W�F�N�g�̎擾
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();

	//���݂̃v���C���[�̈ʒu
	D3DXVECTOR3 pos = GetPos();
	
	//-------------------------------------------------------
	// �������蔻��
	//-------------------------------------------------------

	//���Ƃ̓����蔻��p�ϐ�
	D3DXVECTOR3 groundpos;

	//�v���C���[�����鏰�̍���
	groundpos = pGame->GetMeshfield()->Collision(pos);

	//�v���C���[�����鏰�̍������v���C���[���ゾ������
	if (pos.y <= groundpos.y)
	{
		m_bJump = false;
		pos = D3DXVECTOR3(pos.x, groundpos.y, pos.z);
		SetPos(pos);

		D3DXVECTOR3 move = GetMove();
		SetMove(D3DXVECTOR3(move.x, 0.0f, move.z));

	}
	else
	{
		D3DXVECTOR3 move = GetMove();
		move.y -= PLAYER_GRAVITY;
		SetMove(move);
	}

	//�v���C���[������̍�����艺��������
	if (pos.y < -100.0f)
	{
		pos.y = 0.0f;
		SetPos(pos);
	}


	//-------------------------------------------------------
	// ���I�Ƃ̓����蔻��
	//-------------------------------------------------------


	//�}�b�v��̂ǂ��ɋ��邩
	m_nMapGrid = pGame->GetMeshfield()->CheckPosLocation(pos);

	//�}�b�v�̉��s�Ƀ��b�V����
	int nDepthGrid = pGame->GetMeshfield()->GetMeshZ();

	//�����蔻����`�F�b�N���郁�b�V��
	int aMapGrid[CHECK_RANGE];

	//�v���C���[�̂��郁�b�V��
	int nPlMapGrid = m_nMapGrid - nDepthGrid;

	//�v���C���[�̂��郁�b�V���������W�ӏ��̊���o��
	for (int nCnt = 0; nCnt < CHECK_RANGE_X; nCnt++)
	{
		aMapGrid[nCnt * CHECK_RANGE_X] = nPlMapGrid + nDepthGrid * nCnt - 1;
		aMapGrid[nCnt * CHECK_RANGE_X + 1] = nPlMapGrid + nDepthGrid * nCnt;
		aMapGrid[nCnt * CHECK_RANGE_X + 2] = nPlMapGrid + nDepthGrid * nCnt + 1;
	}

	//���I�Ƃ̓����蔻��
	D3DXVECTOR3 Add = GetPos();

	//�w��͈͂̊��I�̓����蔻��
	for (int nCnt = 0; nCnt < CHECK_RANGE; nCnt++)
	{
		//���I�̓����蔻��
		Add = pGame->GetBallast_Manager()->CollisionBallast(aMapGrid[nCnt], GetPos(), GetOldPos(), PLAYER_SIZE_MAX, PLAYER_SIZE_MIN);

		if (Add != GetPos())
		{
			m_bJump = false;
			D3DXVECTOR3 move = GetMove();
			SetMove(D3DXVECTOR3(move.x, 0.0f, move.z));
			break;
		}

	}

	//���I�Ƃ̓����蔻��
	SetPos(Add);


	if (m_bHit)
	{
		return;
	}


	//-------------------------------------------------------
	// �G�l�~�[�Ƃ̓����蔻��
	//-------------------------------------------------------

	//�G�l�~�[�}�l�[�W���[�̎擾
	CEnemy_Manager* pEnemyManager = pGame->GetEnemy_Manager();

	D3DXVECTOR3 KnockBack = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//����
	m_bHit = pEnemyManager->PlayerCollision(GetPos(),GetRadius(),&KnockBack);

	//�m�b�N�o�b�N�̔���
	if (!m_bHit)
	{
		return;
	}

	//-------------------------------------------------------
	//�m�b�N�o�b�N
	//-------------------------------------------------------

	//�����x�N�g���Ƀm�b�N�o�b�N�p�ړ��ʂ��|����
	KnockBack *= KNOCK_BACK;

	//�ړ��ʂ̐ݒ�
	SetMove(KnockBack);

	//���G���Ԃ̔���
	m_nInvincibleTime = INVINCIBLE_TIME;
}

//*****************************************************************************
// ���[�V��������
//*****************************************************************************
void CPlayer::Motion()
{
	//���̓f�o�C�X�̎擾
	CInput *pInput = CInput::GetKey();

	//�}�l�[�W���[����J�����̎擾
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();
	CTpsCamera* pTpsCamera = (CTpsCamera*)pGame->GetCamera();

	//�J�����̌����iY���̂݁j
	float rotY = pTpsCamera->GetRot();

	//�v���C���[���J�����̌��Ă�����ɂ���
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, rotY + D3DX_PI, 0.0f);

	//Rot�̕ۊ�
	SetRot(rot);

	//���݂̃v���C���[�̈ʒu
	D3DXVECTOR3 PLpos = GetPos();

	//�Đ����郂�[�V�����ԍ�
	int nMotionNumUp = 0;
	int nMotionNumDown = 0;

	if (m_bHit)
	{
		if (m_nInvincibleTime >= INVINCIBLE_TIME)
		{
			//�_�E���p�̃��[�V�����ԍ�
			nMotionNumUp = 4;
			nMotionNumDown = nMotionNumUp;
		}
	}
	else if (m_bJump)
	{
		//�W�����v���p�̃��[�V�����ԍ�
		nMotionNumUp = 6;
		nMotionNumDown = nMotionNumUp;
	}
	else if (pInput->Press(KEY_MOVE))
	{//�v���C���[�������Ă�����
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

	if (pInput->Press(MOUSE_INPUT_LEFT) && !m_bHit)
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
}
