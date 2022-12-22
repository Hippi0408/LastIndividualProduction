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
#include "input.h"
#include "object_type_list.h"
#include "convenience_function.h"

const D3DXVECTOR3 CEnemy::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy::MOVE_INERTIA = 0.1f;
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
	//ライフの設定
	SetLife(INIT_LIFE);

	//初期の位置
	SetPos(INIT_POS);

	//１フレーム前の位置
	SetOldPos(INIT_POS);

	//移動量の初期化
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//向きの初期化
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// モーションモデルの設定処理
	SetMotionModel();

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

	//入力デバイスの取得
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
// 描画処理
//*****************************************************************************
void CEnemy::Draw()
{
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemy::IsUnused()
{
	return false;
}

//*****************************************************************************
// モーションモデルの設定処理
//*****************************************************************************
void CEnemy::SetMotionModel()
{
	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionboss.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}
