//=============================================================================
//
// tps_camera.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "tps_camera.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "convenience_function.h"

const float CTpsCamera::DISTANCE = 150.0f;
const D3DXVECTOR3 CTpsCamera::RANGE_WITH_PLAYER_V = D3DXVECTOR3(100.0f, 0.0f, -500.0f);
//const D3DXVECTOR3 CTpsCamera::RANGE_WITH_PLAYER_R = D3DXVECTOR3(0.0f, 0.0f, 300.0f);
const D3DXVECTOR3 CTpsCamera::RANGE_WITH_PLAYER_R = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTpsCamera::CTpsCamera()
{
	m_CameraVectorConversion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CameraVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPlayerDistance = 0.0f;
	m_DestPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VPos = RANGE_WITH_PLAYER_V;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTpsCamera::~CTpsCamera()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CTpsCamera::Init()
{
	m_VPos = RANGE_WITH_PLAYER_V;
	m_fPlayerDistance = D3DXVec3Length(&RANGE_WITH_PLAYER_V);
	D3DXVECTOR3 vec = RANGE_WITH_PLAYER_V - RANGE_WITH_PLAYER_R;
	D3DXVec3Normalize(&vec, &vec);
	m_CameraVec = vec;
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DestPos = RANGE_WITH_PLAYER_V;

	//親クラスのInit
	if (FAILED(CCamera::Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTpsCamera::Update()
{
	//入力デバイスの取得
	CInput* pInput = CInput::GetKey();

	D3DXVECTOR3 MouseMove;
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

	if (pInput->Trigger(DIK_P))
	{
		m_VPos += m_CameraVec * DISTANCE;

		//m_VPos.y += 50.0f;
	}
	else if (pInput->Trigger(DIK_O))
	{
		m_VPos -= m_CameraVec * DISTANCE;
		//m_VPos.y -= 50.0f;
	}



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

	//ゲームオブジェクトの取得
	CGame* pGame = (CGame*)GetManager()->GetGameObject();
	//プレイヤーオブジェクトの取得
	CPlayer* pPlayer = pGame->GetPlayer();
	D3DXMATRIX mtxRot, mtxTrans,mtxworld;		//計算用のマトリックス
	D3DXVECTOR3 PlPos = pPlayer->GetPos();

	PlPos.y += 100.0f;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxworld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxRot);

	//位置の反映
	D3DXMatrixTranslation(&mtxTrans, PlPos.x, PlPos.y, PlPos.z);
	D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans);

	D3DXVECTOR3 posV, posR,add;

	D3DXVec3TransformCoord(&posV, &m_VPos, &mtxworld);
	D3DXVec3TransformCoord(&posR, &RANGE_WITH_PLAYER_R, &mtxworld);
	D3DXVec3TransformCoord(&m_CameraVectorConversion, &m_CameraVec, &mtxworld);
	D3DXVec3Normalize(&m_CameraVectorConversion, &m_CameraVectorConversion);

	//注視点の保存
	SetPosR(posR);

	m_DestPos = posV;

	add = (m_DestPos - GetPosV()) * 1.0f;

	//視点の保存
	AddPosV(add);
}

//*****************************************************************************
// カメラのベクトルの取得
//*****************************************************************************
D3DXVECTOR3 CTpsCamera::GetCameraVec()
{
	//return D3DXVECTOR3(m_CameraVectorConversion.x, -m_CameraVectorConversion.y, m_CameraVectorConversion.z);
	return m_Rot;
}
