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

const D3DXVECTOR3 CEnemy::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy::MOVE_INERTIA = 0.1f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy::CEnemy()
{
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
void CEnemy::Uninit()
{

}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemy::Update()
{
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
		nMotion = 1;
	}
	else if (pInput->Press(DIK_DOWN))
	{
		nMotion = 2;
	}
	else if (pInput->Press(DIK_RIGHT))
	{
		nMotion = 3;
	}
	else if (pInput->Press(DIK_LEFT))
	{
		nMotion = 4;
	}


	CMotionParts::MoveMotionModel(GetMotionNum(), nMotion, &GetPos(), &GetRot());

	D3DXVECTOR3 Plpos;

	Plpos = pGame->GetPlayer()->GetPos();
	pos = GetPos();

	Plpos.y += 0.0f;

	bool bCollision = CConvenience_Function::SphereCollision(pos,0.0f, Plpos,100.0f);

	if (bCollision)
	{
		SetLife(0);
		CMotionParts::SetBoolDraw(true, GetMotionNum());
	}

	int n = GetLife();

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy::Draw()
{
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemy::IsUnused()
{
	return false;
}

//*****************************************************************************
// ���[�V�������f���̐ݒ菈��
//*****************************************************************************
void CEnemy::SetMotionModel()
{
	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionboss.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}
