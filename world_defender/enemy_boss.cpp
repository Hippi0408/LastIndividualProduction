//=============================================================================
//
// enemy_boss.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy_boss.h"
#include "read.h"
#include "game.h"
#include "meshfield.h"
#include "motion_parts.h"
#include "player.h"
#include "input.h"
#include "object_type_list.h"
#include "convenience_function.h"
#include "psychokinesis_area.h"
#include "statgauge.h"
#include "camera.h"
#include "player.h"

const D3DXVECTOR3 CEnemy_Boss::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy_Boss::MOVE_INERTIA = 0.1f;
const float CEnemy_Boss::JUMP_INERTIA = 0.1f;
const float CEnemy_Boss::INIT_RADIUS = 1600.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy_Boss::CEnemy_Boss()
{
	CMovable_Obj::SetLife(INIT_LIFE);
	CMovable_Obj::SetRadius(INIT_RADIUS);
	m_pLife = nullptr;
	m_bAppearanceMotion = false;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy_Boss::~CEnemy_Boss()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemy_Boss::Init()
{
	//�}�l�[�W���[����Q�[���̏��擾
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();

	//����J�����̐ݒ�
	pGame->SetRoundCamera(300);

	//�J�����̐U���ݒ�
	pGame->SetVibration(300,70);

	CStatGauge::SStatGauge StatGauge;

	StatGauge.pos = D3DXVECTOR3(150.0f, 60.0f, 0.0f);
	StatGauge.rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f);
	StatGauge.color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	StatGauge.fXSize = 60.0f;
	StatGauge.fYSize = 1200.0f;
	StatGauge.nValueMax = INIT_LIFE;
	StatGauge.nRecoveryCntMaqx = 0;
	StatGauge.nRecovery = 0;

	m_pLife = new CStatGauge;
	if (FAILED(m_pLife->Init()))
	{
		return -1;
	}
	m_pLife->CreateStatBar(StatGauge);

	//���C�t�̐ݒ�
	SetLife(INIT_LIFE);

	//�����̈ʒu
	SetPos(INIT_POS);

	//�P�t���[���O�̈ʒu
	SetOldPos(INIT_POS);

	//�ړ��ʂ̏�����
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�����̏�����
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���[�V�������f���̐ݒ菈��
	SetMotionModel();

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEnemy_Boss::Uninit()
{
	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		delete m_pLife;
		m_pLife = nullptr;
	}

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemy_Boss::Update()
{
	//���C�t�Q�[�W�̍X�V�Ǝ��S�`�F�b�N
	if (m_pLife != nullptr)
	{
		//���S�`�F�b�N
		if (m_pLife->ValueCheck())
		{
			//�}�l�[�W���[�̏����擾
			CManager * pManager = GetManager();

			//���̃��[�h�Ɉڍs
			pManager->NextMode(TYPE_RESULT,300);

			//�}�l�[�W���[����Q�[���̏����擾
			CGame* pGame = (CGame*)pManager->GetGameObject();

			//����J�����̐ݒ�
			pGame->SetRoundCamera(400);

			//�J�����̐U���ݒ�
			pGame->SetVibration(400,70);

			//���S���[�V�����̍Đ�
			CMotionParts::MoveMotionModel(GetMotionNum(), 4, &GetPos(), &GetRot(), true);

			//�����艺�̑S�����𖳎�����
			return;
		}

		//���C�t�̍X�V
		m_pLife->Update();

	}

	//�e�N���X�̍X�V
	CMovable_Obj::Update();

	//�}�l�[�W���[�̎擾
	CManager *pManager = GetManager();

	//�}�l�[�W���[����Q�[���̏��擾
	CGame* pGame = (CGame*)pManager->GetGameObject();

	//�n�ʂƂ̓����蔻��p
	D3DXVECTOR3 pos, groundpos;

	//�ʒu���擾
	pos = GetPos();

	//�����Ă���n�ʂ̍������擾
	groundpos = pGame->GetMeshfield()->Collision(pos);

	//���݂̍����Ɣ�r
	if (pos.y < groundpos.y)
	{
		//�����̕ύX
		pos.y = groundpos.y;
		SetPos(pos);
	}

	//���̓f�o�C�X�̎擾
	CInput *pInput = CInput::GetKey();

	//�ړ��ʂ̈ꎞ�ۊ�
	D3DXVECTOR3 move = GetMove();

	//Move�{��
	float fMove = 50.0f;

	//���_�ړ�
	if (pInput->Press(DIK_UP))
	{//��L�[�������ꂽ
		if (pInput->Press(DIK_LEFT))
		{
			move.x = -sinf(D3DX_PI * 0.75f) * fMove;
			move.z = -cosf(D3DX_PI * 0.75f) * fMove;
		}
		else if (pInput->Press(DIK_RIGHT))
		{
			move.x = -sinf(D3DX_PI * -0.75f) * fMove;
			move.z = -cosf(D3DX_PI * -0.75f) * fMove;
		}
		else
		{
			move.x = sinf(0.0f) * fMove;
			move.z = cosf(0.0f) * fMove;
		}
	}
	else if (pInput->Press(DIK_DOWN))
	{//���L�[�������ꂽ
		if (pInput->Press(DIK_LEFT))
		{
			move.x = -sinf(D3DX_PI * 0.25f) * fMove;
			move.z = -cosf(D3DX_PI * 0.25f) * fMove;
		}
		else if (pInput->Press(DIK_RIGHT))
		{
			move.x = -sinf(D3DX_PI * -0.25f) * fMove;
			move.z = -cosf(D3DX_PI * -0.25f) * fMove;
		}
		else
		{
			move.x = sinf(D3DX_PI) * fMove;
			move.z = cosf(D3DX_PI) * fMove;
		}
	}
	else if (pInput->Press(DIK_LEFT))
	{//���L�[�������ꂽ
		move.x = sinf(D3DX_PI * -0.5f) * fMove;
		move.z = cosf(D3DX_PI * -0.5f) * fMove;
	}
	else if (pInput->Press(DIK_RIGHT))
	{//�E�L�[�������ꂽ
		move.x = sinf(D3DX_PI * 0.5f) * fMove;
		move.z = cosf(D3DX_PI * 0.5f) * fMove;
	}

	//�ړ��ʂ�ۊ�
	SetMove(move);

	//����J������posR�̐ݒ�
	pGame->SetRoundCameraPosR(pos);

	//���[�V�����̍Đ�
	if (pGame->CheckVibration() && !m_bAppearanceMotion)
	{//�o��V�[���p
		m_bAppearanceMotion = true;
		CMotionParts::MoveMotionModel(GetMotionNum(), 3, &GetPos(), &GetRot());
	}
	else if (pInput->Press(KEY_MOVE))
	{//�ړ��p
		CMotionParts::MoveMotionModel(GetMotionNum(), 1, &GetPos(), &GetRot());
	}
	else
	{//�j���[�g�������[�V�����p
		CMotionParts::MoveMotionModel(GetMotionNum(), 0, &GetPos(), &GetRot());
	}

	//�����Ă��Ȃ�������ȉ��̏����𖳎�����
	if (!pInput->Press(DIK_UP) &&
		!pInput->Press(DIK_DOWN) &&
		!pInput->Press(DIK_LEFT) &&
		!pInput->Press(DIK_RIGHT))
	{
		return;
	}

	//�{�X�ƃv���C���[�Ƃ̋����ۑ��p�ϐ�
	float fPointDistance = 0.0f;

	//�{�X�ƃv���C���[�Ƃ̋���
	fPointDistance = CConvenience_Function::PointDistance(GetPos(),pGame->GetPlayer()->GetPos());

	//���ۂɋN�����U����
	int nVibration = 0;

	//�{�X���������Ƃɂ��U��
	for (int nCnt = 1; nCnt <= MOVE_VIBRATION; nCnt++)
	{
		//��苗������Ă���ꍇ�͐U�����Ȃ���
		if (fPointDistance < INIT_RADIUS * nCnt)
		{
			nVibration = MOVE_VIBRATION * nCnt;
		}
	}

	//�U���ʂ�0�̂Ƃ�
	if (nVibration == 0)
	{
		return;
	}
	
	//�J�����̐U���ݒ�
	pGame->SetVibration(10, nVibration);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy_Boss::Draw()
{
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemy_Boss::IsUnused()
{

	if (CMovable_Obj::CheckLife())
	{
		

		return true;
	}


	return false;
}

//*****************************************************************************
// ���[�V�������f���̐ݒ菈��
//*****************************************************************************
void CEnemy_Boss::SetMotionModel()
{
	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionboss.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}

//*****************************************************************************
// HP�̌���
//*****************************************************************************
void CEnemy_Boss::AddLife(int nAdd)
{
	CMovable_Obj::AddLife(nAdd);

	m_pLife->SetStatGauge(nAdd);
}
