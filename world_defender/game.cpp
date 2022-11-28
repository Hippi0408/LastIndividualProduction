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
#include "billboard.h"
#include "motion_parts.h"

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
	m_pCamera = new CCamera;
	if (FAILED(m_pCamera->Init()))
	{
		return -1;
	}

	m_pCamera->SetPosV(D3DXVECTOR3(0.0f, 200.0f, -1000.0f));
	m_pCamera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCamera->SetVecU(D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//���C�g
	m_pLight = new CLight;
	if (FAILED(m_pLight->Init()))
	{
		return -1;
	}

	//BG3D
	m_pMeshfieldBG = new CMeshfield;
	if (FAILED(m_pMeshfieldBG->Init()))
	{
		return -1;
	}

	MeshfieldStructure MeshData;
	ZeroMemory(&MeshData, sizeof(MeshData));
	MeshData.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MeshData.rot = D3DXVECTOR3(D3DXToRadian(0), 0.0f, 0.0f);
	MeshData.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	MeshData.fRadiusX = 100.0f;
	MeshData.fRadiusZ = 100.0f;
	MeshData.nMeshX = 20;
	MeshData.nMeshZ = 20;
	MeshData.nTextIndex = CTexture::LoadTexture("data/TEXTURE/�Q�[��.png");
	m_pMeshfieldBG->SetMeshfield(MeshData);



	//Player
	m_pPlayer = new CPlayer;
	if (FAILED(m_pPlayer->Init()))
	{
		return -1;
	}
	m_pPlayer->SetLight(m_pLight->GetLightVec());

	m_pBillcoard = new CBillcoard;
	if (FAILED(m_pBillcoard->Init()))
	{
		return -1;
	}
	int nIndex = CTexture::LoadTexture("data/TEXTURE/�Q�[��.png");
	m_pBillcoard->SetPos(D3DXVECTOR3(0.0f, 100.0f, 0.0f));
	m_pBillcoard->SetRot(D3DXVECTOR3(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0)));
	m_pBillcoard->SetTextIndex(nIndex);
	m_pBillcoard->SetDiagonalLine(50.0f, 50.0f);
	m_pBillcoard->SetPolygon();
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


	//���b�V���t�B�[���h
	if (m_pMeshfieldBG != nullptr)
	{
		m_pMeshfieldBG->Uninit();
		delete m_pMeshfieldBG;
		m_pMeshfieldBG = nullptr;
	}

	//�r���{�[�h
	if (m_pBillcoard != nullptr)
	{
		m_pBillcoard->Uninit();
		delete m_pBillcoard;
		m_pBillcoard = nullptr;
	}

	//Player
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	C3DObject::UninitAllModel();

	CMotionParts::ALLUninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CGame::Update()
{
	m_pPlayer->Update();
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

	m_pPlayer->Draw();

	CMotionParts::ALLDraw();

	m_pBillcoard->Draw();

}
