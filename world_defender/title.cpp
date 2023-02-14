//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "manager.h"
#include "title.h"
#include "input.h"
#include "texture.h"
#include "ui.h"
#include "sound.h"
#include "2d6polygon.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTitle::CTitle()
{
	
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CTitle::Init()
{
	//サウンド
	PlaySound(SOUND_LABEL_BGM_TITLE);

	//nullptr
	m_pUi = nullptr;

	//GetUiData
	m_pUi = new CUI;

	//UiInit
	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	//GetUiPointer
	C2DPolygon *pPolygon = m_pUi->CreateUi(1);

	//SetUiData
	int nIndex = CTexture::LoadTexture("data/TEXTURE/タイトル.png");
	pPolygon[0].SetTextIndex(nIndex);
	pPolygon[0].SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pPolygon[0].SetDiagonalLine(500.0f, 500.0f);
	pPolygon[0].SetPolygon();


	m_p2D4Polygon = new C2D6Polygon;
	
	if (FAILED(m_p2D4Polygon->Init()))
	{
		return -1;
	}

	nIndex = CTexture::LoadTexture("data/TEXTURE/ゲーム.png");
	m_p2D4Polygon->SetTextIndex(nIndex);
	m_p2D4Polygon->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_p2D4Polygon->SetDiagonalLine(500.0f, 500.0f);
	m_p2D4Polygon->SetPolygon();


	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTitle::Uninit()
{
	//サウンド
	StopSound();

	//UiRelease
	if (m_pUi != nullptr)
	{
		//UiUninit
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}

	if (m_p2D4Polygon != nullptr)
	{
		//UiUninit
		m_p2D4Polygon->Uninit();
		delete m_p2D4Polygon;
		m_p2D4Polygon = nullptr;
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTitle::Update()
{
	//GetInput
	CInput *pInput = CInput::GetKey();

	//UiUpdate
	m_pUi->Update();


	if (pInput->Press(KEY_UP))
	{
		m_p2D4Polygon->AddRatio(0.02f);
	}
	else if (pInput->Press(KEY_DOWN))
	{
		m_p2D4Polygon->AddRatio(-0.02f);
	}


	m_p2D4Polygon->Update();


	

	//EndTitle
	if (pInput->Trigger(KEY_DECISION))
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_GAME);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTitle::Draw()
{
	//UiDraw
	//m_pUi->Draw();

	m_p2D4Polygon->Draw();
}