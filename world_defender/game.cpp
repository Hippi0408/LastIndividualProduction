//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
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
#include "billboard.h"
#include "motion_parts.h"
#include "tps_camera.h"
#include "read.h"
#include "ballast_manager.h"
#include <assert.h>

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CGame::Init()
{
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

	
	CRead cRead;

	m_pPlayer = new CPlayer;
	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}
	m_pPlayer->SetLight(m_pLight->GetLightVec());

	m_pEnmey = new CEnemy;
	if (FAILED(m_pEnmey->Init()))
	{
		return -1;
	}

	//BG3D
	m_pMeshfieldBG = cRead.ReadMap("data/MAPTXT/map.txt");
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CGame::Uninit()
{
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

	if (m_pEnmey != nullptr)
	{
		m_pEnmey->Uninit();
		delete m_pEnmey;
		m_pEnmey = nullptr;
	}

	C3DObject::UninitAllModel();

	CMotionParts::ALLUninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CGame::Update()
{
	m_pCamera->Update();
	m_pEnmey->Update();
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

	if (pInput->Trigger(KEY_DECISION) || m_pEnmey->CheckLife())
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_RESULT);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CGame::Draw()
{
	//�J����
	m_pCamera->SetCamera();

	m_pMeshfieldBG->Draw();

	CMotionParts::ALLDraw();

	m_pBallastManager->Draw();

	m_pPlayer->Draw();

}

//*****************************************************************************
// ���I�}�l�[�W���[�̐�������
//*****************************************************************************
void CGame::CreateBallastManager(CMeshfield * pMeshfield)
{
	//���I�}�l�[�W���[�̐�������
	m_pBallastManager = new CBallast_Manager;

	//������
	if (FAILED(m_pBallastManager->Init()))
	{
		assert(false);
	}

	//���b�V���t�B�[���h�̏�񂩂�K�v�Ȑ��l�̎擾
	m_pBallastManager->MeshfieldSet(pMeshfield);

}
