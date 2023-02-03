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
	if (m_pLife != nullptr)
	{
		if (m_pLife->ValueCheck())
		{
			CManager * pManager = GetManager();
			pManager->NextMode(TYPE_RESULT,300);
			CGame* pGame = (CGame*)pManager->GetGameObject();

			//����J�����̐ݒ�
			pGame->SetRoundCamera(300);
		}

		m_pLife->Update();

	}

	CManager *pManager = GetManager();

	CGame* pGame = (CGame*)pManager->GetGameObject();

	D3DXVECTOR3 add = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	AddPos(add);


	D3DXVECTOR3 pos, groundpos;

	pos = GetPos();

	groundpos = pGame->GetMeshfield()->Collision(pos);

	if (pos.y < -100.0f)
	{
		pos.y = 0.0f;
		SetPos(pos);
	}

	int nMotion = 0;

	//���̓f�o�C�X�̎擾
	CInput *pInput = CInput::GetKey();

	if (pInput->Press(DIK_UP))
	{
		pos.z += 50.0f;
		SetPos(pos);
	}
	else if (pInput->Press(DIK_DOWN))
	{
		pos.z += -50.0f;
		SetPos(pos);
	}
	else if (pInput->Press(DIK_RIGHT))
	{
		pos.x += 50.0f;
		SetPos(pos);
	}
	else if (pInput->Press(DIK_LEFT))
	{
		pos.x += -50.0f;
		SetPos(pos);
	}

	//����J������posR�̐ݒ�
	pGame->SetRoundCameraPosR(pos);

	CMotionParts::MoveMotionModel(GetMotionNum(), nMotion, &GetPos(), &GetRot());
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
		CMotionParts::MoveMotionModel(GetMotionNum(), 4, &GetPos(), &GetRot(), true);

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
