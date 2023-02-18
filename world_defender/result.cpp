//=============================================================================
//
// game.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main.h"
#include "result.h"
#include "input.h"
#include "texture.h"
#include "ui.h"
#include "sound.h"
#include <assert.h>
#include "camera_round.h"
#include "light.h"
#include "ballast_manager.h"
#include "read.h"
#include "mesh_cylinder.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CResult::CResult()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CResult::~CResult()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CResult::Init()
{
	//�T�E���h
	PlaySound(SOUND_LABEL_BGM_RESULT);

	
	//�J����
	m_pCameraRound = new CCamera_Round;
	if (FAILED(m_pCameraRound->Init()))
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

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CResult::Uninit()
{
	//�T�E���h
	StopSound();

	//�J����
	if (m_pCameraRound != nullptr)
	{
		m_pCameraRound->Uninit();
		delete m_pCameraRound;
		m_pCameraRound = nullptr;
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

	if (m_pMesh_Cylinder != nullptr)
	{
		m_pMesh_Cylinder->Uninit();
		delete m_pMesh_Cylinder;
		m_pMesh_Cylinder = nullptr;
	}

	C3DObject::UninitAllModel();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CResult::Update()
{
	m_pCameraRound->Update();

	m_pBallastManager->Update();

	//GetInput
	CInput *pInput = CInput::GetKey();

	//EndResult
	if (pInput->Trigger(KEY_DECISION))
	{
		CManager * pManager = GetManager();
		pManager->NextMode(TYPE_TITLE);
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CResult::Draw()
{
	//�J����
	m_pCameraRound->SetCamera();

	m_pMesh_Cylinder->Draw();

	m_pMeshfieldBG->Draw();

	m_pBallastManager->Draw();

}