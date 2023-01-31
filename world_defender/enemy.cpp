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

#ifdef _DEBUG
#include "psychokinesis_area.h"
#endif // _DEBUG

const D3DXVECTOR3 CEnemy::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f); 
const float CEnemy::MOVE_INERTIA = 0.1f; 
const float CEnemy::JUMP_INERTIA = 0.1f;
const float CEnemy::INIT_RADIUS = 1600.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy::CEnemy()
{
	CMovable_Obj::SetLife(INIT_LIFE);
	CMovable_Obj::SetRadius(INIT_RADIUS);
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



#ifdef _DEBUG
	//サイコキネシスエリアの情報の確保
	m_pPsychokinesis_Area = new CPsychokinesis_Area;

	//初期化
	if (FAILED(m_pPsychokinesis_Area->Init()))
	{
		return -1;
	}

#endif // _DEBUG

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemy::Uninit()
{

#ifdef _DEBUG
	//サイコキネシスエリアの解放
	if (m_pPsychokinesis_Area != nullptr)
	{
		//終了処理
		m_pPsychokinesis_Area->Uninit();
		delete m_pPsychokinesis_Area;
		m_pPsychokinesis_Area = nullptr;
	}
#endif // _DEBUG
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEnemy::Update()
{
#ifdef _DEBUG
	//サイコキネシスエリアの更新（Posあり）
	m_pPsychokinesis_Area->Update(GetPos());

	m_pPsychokinesis_Area->SetRadius(GetRadius());
#endif // _DEBUG

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemy::Draw()
{
#ifdef _DEBUG
	//サイコキネシスエリアの描画
	m_pPsychokinesis_Area->Draw();
#endif // _DEBUG
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemy::IsUnused()
{
	//ライフの確認
	if (CMovable_Obj::CheckLife())
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// モーションモデルの設定処理
//*****************************************************************************
void CEnemy::SetMotionModel()
{
}
