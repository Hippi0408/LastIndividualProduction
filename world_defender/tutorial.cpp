//=============================================================================
//
// tutorial.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "manager.h"
#include "tutorial.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "player.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "motion_parts.h"
#include "tps_camera.h"
#include "read.h"
#include "ballast_manager.h"
#include <assert.h>
#include "mesh_cylinder.h"
#include "sound.h"
#include "gauge.h"
#include "adrenaline_item.h"
#include "ufo.h"
#include "2dpolygon.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTutorial::CTutorial()
{
	m_bGameEnd = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTutorial::~CTutorial()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CTutorial::Init()
{

	//サウンド停止
	StopSound();
	//サウンド
	PlaySound(SOUND_LABEL_BGM_GAME);

	//カメラ
	m_pCamera = new CTpsCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}
	
	//ライト
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	m_LightVec = m_pLight->GetLightVec();




	m_pPlayer = new CPlayer;
	m_pPlayer->SetLight(m_LightVec);
	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}


	m_pEnmeyManager = new CEnemy_Manager;
	m_pEnmeyManager->SetLight(m_LightVec);
	if (FAILED(m_pEnmeyManager->Init()))
	{
		return -1;
	}

	//瓦礫マネージャーの生成
	m_pBallastManager = new CBallast_Manager;

	//初期化
	if (FAILED(m_pBallastManager->Init()))
	{
		assert(false);
	}

	m_pBallastManager->SetLight(m_LightVec);

	CRead cRead;
	//BG3D
	m_pMeshfieldBG = cRead.ReadMap("data/MAPTXT/map.txt", m_pBallastManager);

	m_pMesh_Cylinder = new CMesh_Cylinder;
	if (FAILED(m_pMesh_Cylinder->Init()))
	{
		return -1;
	}

	Mesh_Cylinder_Structure Mesh_Cylinder_Structure;

	Mesh_Cylinder_Structure.fRadius = 30000.0f;
	Mesh_Cylinder_Structure.fSizeYTop = 100000.0f;
	Mesh_Cylinder_Structure.nPolygonX = 30;
	Mesh_Cylinder_Structure.nPolygonY = 1;
	Mesh_Cylinder_Structure.nTextureNum = 0;
	Mesh_Cylinder_Structure.ParentPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Mesh_Cylinder_Structure.ColorMax = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	Mesh_Cylinder_Structure.ColorLowest = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	m_pMesh_Cylinder->SetMesh_Cylinder(Mesh_Cylinder_Structure);

	//入力デバイスの取得
	CInput *pInput = CInput::GetKey();

	//画面内のカーソルを消す
	pInput->SetCursorErase(true);

	//アイテム初期化
	if (FAILED(CAdrenalineItem::AllInit()))
	{
		return -1;
	}

	CAdrenalineItem::AllSetLightVec(m_LightVec);

	//UFOの生成
	m_pUfo = new CUfo;

	//UFOの初期化
	if (FAILED(m_pUfo->Init()))
	{
		return -1;
	}

	//影の設定
	m_pUfo->SetLightVec(m_LightVec);

	//細かい設定
	m_pUfo->Set3DObject(cRead.ReadXFile("data/MODEL/UFO.x"), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//初期エネミー生成
	m_pEnmeyManager->InitPopEnemy();

	//UI
	m_pUi = new C2DPolygon;

	//UIの初期化
	if (FAILED(m_pUi->Init()))
	{
		return -1;
	}

	int nIndex = CTexture::LoadTexture("data/TEXTURE/チュートリアルUI.png");
	m_pUi->SetTextIndex(nIndex);
	m_pUi->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pUi->SetDiagonalLine(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pUi->SetPolygon();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTutorial::Uninit()
{
	//サウンド
	StopSound();

	//カメラ
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	
	//ライト
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//瓦礫マネージャー
	if (m_pBallastManager != nullptr)
	{
		m_pBallastManager->Uninit();
		delete m_pBallastManager;
		m_pBallastManager = nullptr;
	}

	//メッシュフィールド
	if (m_pMeshfieldBG != nullptr)
	{
		m_pMeshfieldBG->Uninit();
		delete m_pMeshfieldBG;
		m_pMeshfieldBG = nullptr;
	}

	//Player
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pEnmeyManager != nullptr)
	{
		m_pEnmeyManager->Uninit();
		delete m_pEnmeyManager;
		m_pEnmeyManager = nullptr;
	}

	if (m_pMesh_Cylinder != nullptr)
	{
		m_pMesh_Cylinder->Uninit();
		delete m_pMesh_Cylinder;
		m_pMesh_Cylinder = nullptr;
	}

	if (m_pUfo != nullptr)
	{
		m_pUfo->Uninit();
		delete m_pUfo;
		m_pUfo = nullptr;
	}

	if (m_pUi != nullptr)
	{
		m_pUi->Uninit();
		delete m_pUi;
		m_pUi = nullptr;
	}


	CAdrenalineItem::AllUninit();

	C3DObject::UninitAllModel();

	CMotionParts::ALLUninit();

	CGauge::AllUninit();

	
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTutorial::Update()
{
	if (m_bGameEnd)
	{
		return;
	}

	m_pMesh_Cylinder->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//カメラの更新
	m_pCamera->Update();

	m_pEnmeyManager->Update();

	//ゲームエンドではなかったら更新
	if (!m_bGameEnd)
	{
		m_pPlayer->Update();
	}

	m_pBallastManager->Update();

	m_pUfo->Update();

	CInput *pInput = CInput::GetKey();

	CMotionParts::ALLUpdate();

	CAdrenalineItem::AllUpdate();

	if (pInput->Trigger(KEY_DECISION))
	{
		m_bGameEnd = true;
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_TITLE);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTutorial::Draw()
{
	//カメラの更新
	m_pCamera->SetCamera();

	m_pMesh_Cylinder->Draw();

	m_pMeshfieldBG->Draw();

	CMotionParts::ALLDraw();

	m_pBallastManager->Draw();

	m_pEnmeyManager->Draw();

	m_pUfo->Draw();

	CAdrenalineItem::AllDraw();

	//ゲージ
	CGauge::AllDraw();

	m_pPlayer->Draw();

	m_pUi->Draw();

}
