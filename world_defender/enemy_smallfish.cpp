//=============================================================================
//
// enemyu_smallfish.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy_smallfish.h"
#include "read.h"
#include "game.h"
#include "meshfield.h"
#include "motion_parts.h"
#include "player.h"
#include "input.h"
#include "object_type_list.h"
#include "convenience_function.h"
#include "psychokinesis_area.h"

const D3DXVECTOR3 CEnemy_SmallFish::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy_SmallFish::MOVE_INERTIA = 0.1f;
const float CEnemy_SmallFish::JUMP_INERTIA = 0.1f;
const float CEnemy_SmallFish::INIT_RADIUS = 1600.0f;
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy_SmallFish::CEnemy_SmallFish()
{
	CMovable_Obj::SetLife(INIT_LIFE);
	CMovable_Obj::SetRadius(INIT_RADIUS);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy_SmallFish::~CEnemy_SmallFish()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemy_SmallFish::Init()
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
void CEnemy_SmallFish::Uninit()
{
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemy_SmallFish::Update()
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


	CMotionParts::MoveMotionModel(GetMotionNum(), nMotion, &GetPos(), &GetRot());

	D3DXVECTOR3 Plpos;

	Plpos = pGame->GetPlayer()->GetPos();
	pos = GetPos();

	Plpos.y += 0.0f;

	bool bCollision = CConvenience_Function::SphereCollision(pos, 0.0f, Plpos, 100.0f);

	if (bCollision)
	{
		SetLife(0);
		CMotionParts::SetBoolDraw(true, GetMotionNum());
	}

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy_SmallFish::Draw()
{
}

//*****************************************************************************
// �I����������
//*****************************************************************************
bool CEnemy_SmallFish::IsUnused()
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
void CEnemy_SmallFish::SetMotionModel()
{
	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionenemy.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}
