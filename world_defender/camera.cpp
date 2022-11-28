//=============================================================================
//
// camera.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "camera.h"
#include "manager.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCamera::CCamera()
{
	ZeroMemory(&m_Camera, sizeof(m_Camera));
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCamera::~CCamera()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CCamera::Init()
{

	m_Camera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	float fData = m_Camera.posV.x - m_Camera.posR.x;
	float fData1 = m_Camera.posV.z - m_Camera.posR.z;

	//m_Camera.fDistance = ThreeSquareTheorem(fData, fData1);

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CCamera::Uninit()
{
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CCamera::Update()
{
	
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCamera::Draw()
{
}

//*****************************************************************************
// �J�����̃Z�b�g
//*****************************************************************************
void CCamera::SetCamera()
{
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Camera.mtxView);

	D3DXMatrixLookAtLH(&m_Camera.mtxView, &m_Camera.posV, &m_Camera.posR, &m_Camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_Camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_Camera.mtxProjection,
		D3DXToRadian(45.0f),//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//�A�X�y�N�g��
		10.0f,//�ǂ�����ǂ��܂ŃJ�����ŕ\�����邩
		50000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_Camera.mtxProjection);
}

float CCamera::GetRot()
{
	D3DXVECTOR3 vec = m_Camera.posR - m_Camera.posV;

	float fAngle = atan2f(vec.x, vec.z);

	return fAngle;
}
