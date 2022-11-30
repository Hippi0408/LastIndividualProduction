//=============================================================================
//
// player.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "player.h"
#include "input.h"
#include "read.h"
#include "texture.h"
#include "game.h"
#include "camera.h"
#include "meshfield.h"
#include "motion_parts.h"

const D3DXVECTOR3 CPlayer::INIT_POS = D3DXVECTOR3(0.0f,0.0f,0.0f);
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CPlayer::CPlayer()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CPlayer::Init()
{
	SetLife(INIT_LIFE);

	SetPos(INIT_POS);

	SetOldPos(INIT_POS);

	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionplayer.txt"));

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CPlayer::Uninit()
{

}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CPlayer::Update()
{
	CInput *pInput = CInput::GetKey();
	CManager *pManager = GetManager();

	CGame* pGame = (CGame*)pManager->GetGameObject();

	float rotY = pGame->GetCamera()->GetRot();

	D3DXVECTOR3 add = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視点移動
	if (pInput->Press(DIK_W))
	{//上キーが押された
		if (pInput->Press(DIK_A))
		{
			add.x -= sinf(rotY + D3DX_PI * 0.75f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * 0.75f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.75f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * -0.75f) * 5.0f;
		}
		else
		{
			add.x += sinf(rotY) * 5.0f;
			add.z += cosf(rotY) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_S))
	{//下キーが押された
		if (pInput->Press(DIK_A))
		{
			add.x -= sinf(rotY + D3DX_PI * 0.25f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * 0.25f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			add.x -= sinf(rotY + D3DX_PI * -0.25f) * 5.0f;
			add.z -= cosf(rotY + D3DX_PI * -0.25f) * 5.0f;
		}
		else
		{
			add.x += sinf(rotY + D3DX_PI) * 5.0f;
			add.z += cosf(rotY + D3DX_PI) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_A))
	{//左キーが押された
		add.x += sinf(rotY + D3DX_PI * -0.5f) * 5.0f;
		add.z += cosf(rotY + D3DX_PI * -0.5f) * 5.0f;
	}
	else if (pInput->Press(DIK_D))
	{//右キーが押された
		add.x += sinf(rotY + D3DX_PI * 0.5f) * 5.0f;
		add.z += cosf(rotY + D3DX_PI * 0.5f) * 5.0f;
	}

	
	if (pInput->Press(DIK_Z))
	{
		AddRot(D3DXVECTOR3(0.0f, D3DXToRadian(-10), 0.0f));
	}
	else if (pInput->Press(DIK_X))
	{
		AddRot(D3DXVECTOR3(0.0f, D3DXToRadian(10), 0.0f));
	}

	//add.y -= 4.0f;

	AddPos(add);


	D3DXVECTOR3 pos, groundpos;

	pos = GetPos();

	groundpos = pGame->GetMeshfield()->Collision(pos);

	if (pos.y < groundpos.y)
	{
		if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			pos = groundpos;
			SetPos(groundpos);
		}
	}

	if (pos.y < -100.0f)
	{
		pos.y = 0.0f;
		SetPos(pos);
	}


	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, rotY + D3DX_PI, 0.0f);


	SetRot(rot);
	

	if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		CMotionParts::AllSetShadowPos(groundpos, GetMotionNum());
	}

	if (pInput->Press(KEY_MOVE) || pInput->Press(DIK_0))
	{
		CMotionParts::MoveMotionModel(GetPos(), GetRot(), GetMotionNum(),1);
	}
	else
	{
		CMotionParts::MoveMotionModel(GetPos(), GetRot(), GetMotionNum(),0);
	}


	

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPlayer::Draw()
{
}
