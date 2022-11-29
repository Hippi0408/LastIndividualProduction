//=============================================================================
//
// enemy.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy.h"
#include "read.h"
#include "game.h"
#include "meshfield.h"
#include "motion_parts.h"
#include "player.h"

const D3DXVECTOR3 CEnemy::INIT_POS = D3DXVECTOR3(400.0f, 0.0f, -200.0f);
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy::CEnemy()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy::~CEnemy()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemy::Init()
{
	SetLife(INIT_LIFE);

	SetPos(INIT_POS);

	SetOldPos(INIT_POS);

	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionenemy.txt"));

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemy::Uninit()
{

}

//*****************************************************************************
// 更新処理
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


	CMotionParts::MoveMotionModel(GetPos(), GetRot(), GetMotionNum(), 0);

	pos = CMotionParts::AllCollision(pGame->GetPlayer()->GetMotionNum(), pGame->GetPlayer()->GetPos(), GetOldPos());

	if (pos != pGame->GetPlayer()->GetPos())
	{
		SetLife(0);
		CMotionParts::SetBoolDraw(true, GetMotionNum());
	}

	int n = GetLife();

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemy::Draw()
{
}
