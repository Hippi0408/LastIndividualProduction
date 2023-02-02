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
#include "game.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "player.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "billboard.h"
#include "motion_parts.h"
#include "tps_camera.h"
#include "read.h"
#include "ballast_manager.h"
#include <assert.h>
#include "mesh_cylinder.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CGame::CGame()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CGame::Init()
{
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

	
	CRead cRead;

	m_pPlayer = new CPlayer;
	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}
	m_pPlayer->SetLight(m_pLight->GetLightVec());

	m_pEnmeyManager = new CEnemy_Manager;
	if (FAILED(m_pEnmeyManager->Init()))
	{
		return -1;
	}
	EnemyInitData EnemyInitData;

	EnemyInitData.fmove = 10.0f;
	EnemyInitData.pos = D3DXVECTOR3(3000.0f,0.0f, 500.0f);
	EnemyInitData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EnemyInitData.type = ENEMY_02;

	m_pEnmeyManager->CreateEnemy(EnemyInitData);

	/*EnemyInitData.pos = D3DXVECTOR3(500.0f, 0.0f, -500.0f);
	m_pEnmeyManager->CreateEnemy(EnemyInitData);*/

	//BG3D
	m_pMeshfieldBG = cRead.ReadMap("data/MAPTXT/map.txt");

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
	Mesh_Cylinder_Structure.ParentPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	Mesh_Cylinder_Structure.ColorMax = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	Mesh_Cylinder_Structure.ColorLowest = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	m_pMesh_Cylinder->SetMesh_Cylinder(Mesh_Cylinder_Structure);



	//入力デバイスの取得
	CInput *pInput = CInput::GetKey();

	//画面内のカーソルを消す
	pInput->SetCursorErase(true);


	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CGame::Uninit()
{
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

	C3DObject::UninitAllModel();

	CMotionParts::ALLUninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CGame::Update()
{
	m_pMesh_Cylinder->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCamera->Update();
	m_pEnmeyManager->Update();
	m_pPlayer->Update();
	m_pBallastManager->Update();
	CInput *pInput = CInput::GetKey();

	if (pInput->Press(DIK_UP))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	}
	else if (pInput->Press(DIK_DOWN))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	}

	if (pInput->Press(DIK_LEFT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(DIK_RIGHT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	}


	if (pInput->Press(DIK_RSHIFT))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	}
	else if (pInput->Press(DIK_RCONTROL))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
		m_pCamera->AddPosR(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	}

	if (pInput->Press(DIK_I))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	}
	else if (pInput->Press(DIK_K))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, -5.0f, 0.0f));
	}


	if (pInput->Press(DIK_T))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	}
	else if (pInput->Press(DIK_G))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	}

	if (pInput->Press(DIK_F))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(DIK_H))
	{
		m_pCamera->AddPosV(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		//m_pCamera->AddPosR(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	}

	CMotionParts::ALLUpdate();

	if (pInput->Trigger(KEY_DECISION))
	{
		//画面内のカーソルの復活
		pInput->SetCursorErase(false);
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CGame::Draw()
{
	//カメラ
	m_pCamera->SetCamera();

	m_pMesh_Cylinder->Draw();

	m_pMeshfieldBG->Draw();

	CMotionParts::ALLDraw();

	m_pBallastManager->Draw();

	m_pPlayer->Draw();

	m_pEnmeyManager->Draw();

}

//*****************************************************************************
// 瓦礫マネージャーの生成処理
//*****************************************************************************
void CGame::CreateBallastManager(CMeshfield * pMeshfield)
{
	//瓦礫マネージャーの生成処理
	m_pBallastManager = new CBallast_Manager;

	//初期化
	if (FAILED(m_pBallastManager->Init()))
	{
		assert(false);
	}

	//メッシュフィールドの情報から必要な数値の取得
	m_pBallastManager->MeshfieldSet(pMeshfield);

}
