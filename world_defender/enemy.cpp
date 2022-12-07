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

const D3DXVECTOR3 CEnemy::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -200.0f);
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
	SetLife(INIT_LIFE);

	SetPos(INIT_POS);

	SetOldPos(INIT_POS);

	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionboss.txt"));

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

	add.y -= 4.0f;

	AddPos(add);


	D3DXVECTOR3 pos, groundpos;

	pos = GetPos();

	groundpos = pGame->GetMeshfield()->Collision(pos);

	if (pos.y < groundpos.y)
	{
		if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			pos = groundpos;
			SetPos(groundpos);
		}
	}

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

	/*CPlayer* pPlayer = pGame->GetPlayer();

	pos = CMotionParts::AllCollision(pPlayer->GetPos(), GetOldPos(), pPlayer->GetMotionNum(), pPlayer->GetMotionNum1());

	if (pos != pGame->GetPlayer()->GetPos())
	{
		SetLife(0);
		CMotionParts::SetBoolDraw(true, GetMotionNum());
	}*/

	int n = GetLife();

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy::Draw()
{
}
