//=============================================================================
//
// tutorial.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
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

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CTutorial::CTutorial()
{
	m_bGameEnd = false;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTutorial::~CTutorial()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CTutorial::Init()
{

	//�T�E���h��~
	StopSound();
	//�T�E���h
	PlaySound(SOUND_LABEL_BGM_GAME);

	//�J����
	m_pCamera = new CTpsCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}
	
	//���C�g
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


	EnemyInitData EnemyInitData;

	EnemyInitData.fmove = 10.0f;
	EnemyInitData.pos = D3DXVECTOR3(0.0f, 0.0f, 9000.0f);
	EnemyInitData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EnemyInitData.type = ENEMY_01;

	m_pEnmeyManager->CreateEnemy(EnemyInitData);

	EnemyInitData.pos = D3DXVECTOR3(500.0f, 0.0f, 1600.0f);

	m_pEnmeyManager->CreateEnemy(EnemyInitData);

	EnemyInitData.pos = D3DXVECTOR3(500.0f, 0.0f, 1500.0f);
	m_pEnmeyManager->CreateEnemy(EnemyInitData);

	//���I�}�l�[�W���[�̐���
	m_pBallastManager = new CBallast_Manager;

	//������
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

	//���̓f�o�C�X�̎擾
	CInput *pInput = CInput::GetKey();

	//��ʓ��̃J�[�\��������
	pInput->SetCursorErase(true);

	//�A�C�e��������
	if (FAILED(CAdrenalineItem::AllInit()))
	{
		return -1;
	}

	CAdrenalineItem::AllSetLightVec(m_LightVec);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CTutorial::Uninit()
{
	//�T�E���h
	StopSound();

	//�J����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	
	//���C�g
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//���I�}�l�[�W���[
	if (m_pBallastManager != nullptr)
	{
		m_pBallastManager->Uninit();
		delete m_pBallastManager;
		m_pBallastManager = nullptr;
	}

	//���b�V���t�B�[���h
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

	CAdrenalineItem::AllUninit();

	C3DObject::UninitAllModel();

	CMotionParts::ALLUninit();

	CGauge::AllUninit();

	
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CTutorial::Update()
{
	if (m_bGameEnd)
	{
		return;
	}

	m_pMesh_Cylinder->Update(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�J�����̍X�V
	m_pCamera->Update();

	m_pEnmeyManager->Update();

	//�Q�[���G���h�ł͂Ȃ�������X�V
	if (!m_bGameEnd)
	{
		m_pPlayer->Update();
	}

	m_pBallastManager->Update();

	CInput *pInput = CInput::GetKey();

	CMotionParts::ALLUpdate();

	CAdrenalineItem::AllUpdate();

	if (pInput->Trigger(KEY_DECISION))
	{
		m_bGameEnd = true;
		//��ʓ��̃J�[�\���̕���
		pInput->SetCursorErase(false);
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_TITLE);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CTutorial::Draw()
{
	//�J�����̍X�V
	m_pCamera->SetCamera();

	m_pMesh_Cylinder->Draw();

	m_pMeshfieldBG->Draw();

	CMotionParts::ALLDraw();

	m_pBallastManager->Draw();

	m_pEnmeyManager->Draw();

	CAdrenalineItem::AllDraw();

	//�Q�[�W
	CGauge::AllDraw();

	m_pPlayer->Draw();

}