//=============================================================================
//
// tps_camera.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "tps_camera.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "convenience_function.h"

const float CTpsCamera::DISTANCE = 400.0f;
const D3DXVECTOR3 CTpsCamera::RANGE_WITH_PLAYER_V = D3DXVECTOR3(100.0f, 0.0f, -300.0f);
//const D3DXVECTOR3 CTpsCamera::RANGE_WITH_PLAYER_R = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
const D3DXVECTOR3 CTpsCamera::RANGE_WITH_PLAYER_R = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CTpsCamera::CTpsCamera()
{
	m_CameraVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPlayerDistance = 0.0f;
	m_DestPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTpsCamera::~CTpsCamera()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CTpsCamera::Init()
{
	m_fPlayerDistance = D3DXVec3Length(&RANGE_WITH_PLAYER_V);
	m_CameraVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DestPos = RANGE_WITH_PLAYER_V;

	//�e�N���X��Init
	if (FAILED(CCamera::Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CTpsCamera::Uninit()
{
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CTpsCamera::Update()
{
	//���̓f�o�C�X�̎擾
	CInput* pInput = CInput::GetKey();

	D3DXVECTOR3 MouseMove;
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

	MouseMove = pInput->GetMouseMove();

	MouseMove = D3DXVECTOR3(MouseMove.y, MouseMove.x, 0.0f);

	if(D3DXVec3Length(&MouseMove) > 1.0f)
	{
		D3DXVec3Normalize(&MouseMove,&MouseMove);

		rot = MouseMove * (D3DX_PI / 180.0f);

		rot.x *= 2.0f;
		rot.y *= 3.0f;
		rot.z *= 3.0f;
	}

	m_Rot += rot;

	if (m_Rot.x  > D3DXToRadian(30))
	{
		m_Rot.x = D3DXToRadian(30);
	}
	else if (m_Rot.x  < D3DXToRadian(-30))
	{
		m_Rot.x = D3DXToRadian(-30);
	}

	rot = CConvenience_Function::NormalizationRot(m_Rot);
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;

	//�Q�[���I�u�W�F�N�g�̎擾
	CGame* pGame = (CGame*)GetManager()->GetGameObject();
	//�v���C���[�I�u�W�F�N�g�̎擾
	CPlayer* pPlayer = pGame->GetPlayer();
	D3DXMATRIX mtxRot, mtxTrans,mtxworld;		//�v�Z�p�̃}�g���b�N�X
	D3DXVECTOR3 PlPos = pPlayer->GetPos();

	PlPos.y += 100.0f;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxworld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, PlPos.x, PlPos.y, PlPos.z);
	D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans);

	D3DXVECTOR3 posV, posR,add;

	D3DXVec3TransformCoord(&posV, &RANGE_WITH_PLAYER_V, &mtxworld);
	D3DXVec3TransformCoord(&posR, &RANGE_WITH_PLAYER_R, &mtxworld);
	
	//�����_�̕ۑ�
	SetPosR(posR);

	m_DestPos = posV;

	add = (m_DestPos - GetPosV()) * 1.0f;

	//���_�̕ۑ�
	AddPosV(add);

	

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CTpsCamera::Draw()
{
}