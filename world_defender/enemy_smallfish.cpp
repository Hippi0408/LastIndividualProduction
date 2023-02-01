//=============================================================================
//
// enemyu_smallfish.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
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
#include "enemy_manager.h"

const D3DXVECTOR3 CEnemy_SmallFish::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy_SmallFish::MOVE_INERTIA = 5.0f;
const float CEnemy_SmallFish::JUMP_INERTIA = 0.1f; 
const float CEnemy_SmallFish::INIT_RADIUS = 100.0f;
const float CEnemy_SmallFish::SEARCH_RANGE = 1000.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy_SmallFish::CEnemy_SmallFish()
{
	CMovable_Obj::SetLife(INIT_LIFE);
	CMovable_Obj::SetRadius(INIT_RADIUS);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy_SmallFish::~CEnemy_SmallFish()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemy_SmallFish::Init()
{

	//親クラスの初期化
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

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
void CEnemy_SmallFish::Uninit()
{
	//親クラスの終了処理
	CEnemy::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEnemy_SmallFish::Update()
{
	//親クラスの更新処理
	CEnemy::Update();

	//自身の位置
	D3DXVECTOR3 pos = GetPos();

	//マネージャーからプレイヤーの情報の取得
	CManager* pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();
	CPlayer* pPlayer = pGame->GetPlayer();

	//プレイヤーの位置
	D3DXVECTOR3 PLpos = pPlayer->GetPos();

	//索敵範囲にいるかどうか
	if (!CConvenience_Function::CircleCollision(pos, SEARCH_RANGE, PLpos, 0.0f))
	{
		return;
	}

	//プレイヤーの方向へのベクトル
	D3DXVECTOR3 vec = CConvenience_Function::PointOrientationVectorGeneration(PLpos, pos);


	//プレイヤーに近づく
	AddPos(vec * MOVE_INERTIA);


	//エネミーマネージャーの取得
	CEnemy_Manager* pEnemy_Manager = pGame->GetEnemy_Manager();

	//当たり判定(他のエネミーとの)
	pEnemy_Manager->EnemyOnEnemyCollision(this);

	//エネミーのrot
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	rot.y = atan2f(vec.x, vec.z) + D3DX_PI;

	//rot設定
	SetRot(rot);


	//モーション
	CMotionParts::MoveMotionModel(GetMotionNum(), 0, &GetPos(), &GetRot());

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemy_SmallFish::Draw()
{
	//親クラスの描画処理
	CEnemy::Draw();
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemy_SmallFish::IsUnused()
{
	if (CMovable_Obj::CheckLife())
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// モーションモデルの設定処理
//*****************************************************************************
void CEnemy_SmallFish::SetMotionModel()
{
	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionenemy.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}
