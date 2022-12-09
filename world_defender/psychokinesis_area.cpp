//=============================================================================
//
// 軌跡処理 [psychokinesis_area.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "psychokinesis_area.h" 
#include "locus.h"
#include "texture.h"
#include <assert.h>
#include "convenience_function.h"

const D3DXVECTOR3 CPsychokinesis_Area::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const float CPsychokinesis_Area::HEIGHT_LOCUS = 80.0f;
const float CPsychokinesis_Area::RADIUS_INIT = 200.0f;
const float CPsychokinesis_Area::RADIUS_MOVE = D3DXToRadian(5);
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPsychokinesis_Area::CPsychokinesis_Area()
{
	m_PLPos = INIT_POS;
	m_LocusPos = INIT_POS;
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove = D3DXVECTOR3(0.0f, RADIUS_MOVE, 0.0f);
	m_fRadius = RADIUS_INIT;
	m_pLocus = nullptr;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPsychokinesis_Area::~CPsychokinesis_Area()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CPsychokinesis_Area::Init()
{
	//Numチェック
	if (m_pLocus != nullptr)
	{
		assert(false);
	}

	//軌跡情報の確保
	m_pLocus = new CLocus;

	//初期化
	if (FAILED(m_pLocus->Init()))
	{
		return -1;
	}

	//情報の一時保管用変数宣言
	LocusStructure locusstructure;
	D3DXVECTOR3 PLpos = m_PLPos;
	

	//出現する軌跡の上下のPosの設定
	D3DXVECTOR3 pos;
	pos.x = m_fRadius * cosf(m_Rot.y);
	pos.z = m_fRadius * sinf(m_Rot.y);
	pos.y = 0.0f;
	locusstructure.TopPos = PLpos + D3DXVECTOR3(pos.x, HEIGHT_LOCUS, pos.z);
	locusstructure.DownPos = PLpos + pos;

	//出現始めと終わりのカラー設定
	locusstructure.BeginningCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	locusstructure.EndCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//何枚で表示するか
	locusstructure.nPolygon = 24;

	//Posの更新フレーム数
	locusstructure.nSaveInterval = 3;

	//テクスチャの読み込み
	locusstructure.nTextureNum = CTexture::LoadTexture("data/TEXTURE/軌跡.png");

	//一時保管した情報の設定
	m_pLocus->SetLocus(locusstructure);


	return S_OK;
}

//*****************************************************************************
// 初期化(Posあり)
//*****************************************************************************
HRESULT CPsychokinesis_Area::Init(D3DXVECTOR3 Pos)
{
	//プレイヤーの位置の保管
	m_PLPos = Pos;

	//初期化
	if (FAILED(Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPsychokinesis_Area::Uninit()
{
	//軌跡の情報の解放
	if (m_pLocus != nullptr)
	{
		//終了処理
		m_pLocus->Uninit();
		delete m_pLocus;
		m_pLocus = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CPsychokinesis_Area::Update()
{
	//Rotの更新
	m_Rot += m_RotMove;

	//正規化
	m_Rot = CConvenience_Function::NormalizationRot(m_Rot);

	//出現する軌跡の上下のPosの設定
	D3DXVECTOR3 pos,posUp,posDown;
	pos.x = m_fRadius * cosf(m_Rot.y);
	pos.z = m_fRadius * sinf(m_Rot.y);
	pos.y = 0.0f;

	posUp = m_PLPos + D3DXVECTOR3(pos.x, HEIGHT_LOCUS, pos.z);
	posDown = m_PLPos + pos;

	m_pLocus->Update(posUp, posDown);
}

//*****************************************************************************
// 更新処理(オーバーロードPos更新あり)
//*****************************************************************************
void CPsychokinesis_Area::Update(D3DXVECTOR3 Pos)
{
	//プレイヤーの位置の更新
	m_PLPos = Pos;

	//更新処理
	Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPsychokinesis_Area::Draw()
{
	//描画処理
	m_pLocus->Draw();
}

