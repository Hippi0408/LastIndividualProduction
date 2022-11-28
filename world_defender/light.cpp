//=============================================================================
//
// ���� [light.cpp]
// Author : KOZUNA HIROHITO

//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "light.h"
#include "manager.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CLight::CLight()
{
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CLight::~CLight()
{
}

//*****************************************************************************
//���C�g�̏�����
//*****************************************************************************
HRESULT CLight::Init(void)
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	D3DXVECTOR3 vecDir[LIGHT_MAX];//���C�g�̕����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&m_alight, sizeof(m_alight));

	//���C�g�̎�ނ�ݒ�
	m_alight[0].Type = D3DLIGHT_DIRECTIONAL;
	m_alight[1].Type = D3DLIGHT_DIRECTIONAL;
	m_alight[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	m_alight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_alight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_alight[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//���C�g�̈ʒu
	m_alight[0].Position = D3DXVECTOR3(100.0f, 70.0f, 0.0f);
	m_alight[1].Position = D3DXVECTOR3(100.0f, 70.0f, 0.0f);
	m_alight[2].Position = D3DXVECTOR3(-100.0f, 70.0f, 0.0f);

	D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���C�g�̕�����ݒ�
	vecDir[0] = posR - m_alight[0].Position;
	vecDir[1] = posR - m_alight[1].Position;
	vecDir[2] = posR - m_alight[2].Position;

	//���K������i�傫���P�̃x�N�g���ɂ���j�G
	D3DXVec3Normalize(&vecDir[0], &vecDir[0]);
	D3DXVec3Normalize(&vecDir[1], &vecDir[1]);
	D3DXVec3Normalize(&vecDir[2], &vecDir[2]);
	m_alight[0].Direction = vecDir[0];
	m_alight[1].Direction = vecDir[1];
	m_alight[2].Direction = vecDir[2];

	//���C�g��ݒ肷��
	pD3DDevice->SetLight(0, &m_alight[0]);
	//pD3DDevice->SetLight(1, &m_alight[1]);
	//pD3DDevice->SetLight(2, &m_alight[2]);

	//���C�g��L���ɂ���
	pD3DDevice->LightEnable(0, TRUE);
	//pD3DDevice->LightEnable(1, TRUE);
	//pD3DDevice->LightEnable(2, TRUE);
	//pD3DDevice->SetRenderState( );
	return S_OK;
}

//*****************************************************************************
//���C�g�̏I������
//*****************************************************************************
void CLight::Uninit(void)
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//���C�g�𖳌��ɂ���
	pD3DDevice->LightEnable(0, FALSE);
	pD3DDevice->LightEnable(1, FALSE);
	pD3DDevice->LightEnable(2, FALSE);
}

//*****************************************************************************
//���C�g�̍X�V����
//*****************************************************************************
void CLight::Update(void)
{
}

//*****************************************************************************
//���C�g�̕`�揈��
//*****************************************************************************
void CLight::Draw()
{
}

//*****************************************************************************
//���C�g�̃x�N�g��
//*****************************************************************************
D3DXVECTOR3 CLight::GetLightVec()
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_alight[0].Position;

	//���K��
	D3DXVec3Normalize(&vec,&vec);

	return vec;
}
