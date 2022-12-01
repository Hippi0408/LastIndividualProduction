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
#include "convenience_function.h"

const D3DXVECTOR3 CPlayer::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
const float CPlayer::MOVE_INERTIA = 0.1f;
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

	m_RotLowerBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_DestRotLowerBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionplayer1.txt"));

	m_nMotionNum1 = cRead.ReadMotion("data/MOTION/motionplayer2.txt");


	CMotionParts::SettingParent(m_nMotionNum1, GetMotionNum());

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
	//親クラスの更新
	CMovable_Obj::Update();

	//入力デバイスの取得
	CInput *pInput = CInput::GetKey();

	//マネージャーからゲームオブジェクトの取得
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();

	//カメラの向き（Y軸のみ）
	float rotY = pGame->GetCamera()->GetRot();

	//移動量の一時保管
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視点移動
	if (pInput->Press(DIK_W))
	{//上キーが押された
		if (pInput->Press(DIK_A))
		{
			move.x -= sinf(rotY + D3DX_PI * 0.75f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * 0.75f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			move.x -= sinf(rotY + D3DX_PI * -0.75f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * -0.75f) * 5.0f;
		}
		else
		{
			move.x += sinf(rotY) * 5.0f;
			move.z += cosf(rotY) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_S))
	{//下キーが押された
		if (pInput->Press(DIK_A))
		{
			move.x -= sinf(rotY + D3DX_PI * 0.25f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * 0.25f) * 5.0f;
		}
		else if (pInput->Press(DIK_D))
		{
			move.x -= sinf(rotY + D3DX_PI * -0.25f) * 5.0f;
			move.z -= cosf(rotY + D3DX_PI * -0.25f) * 5.0f;
		}
		else
		{
			move.x += sinf(rotY + D3DX_PI) * 5.0f;
			move.z += cosf(rotY + D3DX_PI) * 5.0f;
		}
	}
	else if (pInput->Press(DIK_A))
	{//左キーが押された
		move.x += sinf(rotY + D3DX_PI * -0.5f) * 5.0f;
		move.z += cosf(rotY + D3DX_PI * -0.5f) * 5.0f;
	}
	else if (pInput->Press(DIK_D))
	{//右キーが押された
		move.x += sinf(rotY + D3DX_PI * 0.5f) * 5.0f;
		move.z += cosf(rotY + D3DX_PI * 0.5f) * 5.0f;
	}

	//移動量に変更があった場合移動を保管
	if (move != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		if (pInput->Press(DIK_S))
		{
			move *= 0.6f;
		}
		else if (pInput->Press(DIK_LSHIFT))
		{
			move *= 2.0f;
		}

		SetMove(move);
	}

	//床との当たり判定用変数
	D3DXVECTOR3 pos, groundpos;

	//現在のプレイヤーの位置
	pos = GetPos();

	//プレイヤーがいる床の高さ
	groundpos = pGame->GetMeshfield()->Collision(pos);

	//プレイヤーがいる床の高さがプレイヤーより上だったら
	if (pos.y < groundpos.y)
	{
		if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			pos = groundpos;
			SetPos(groundpos);
		}
	}

	//プレイヤーが既定の高さより下だったら
	if (pos.y < -100.0f)
	{
		pos.y = 0.0f;
		SetPos(pos);
	}

	//プレイヤーをカメラの見てる方向にする
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, rotY + D3DX_PI, 0.0f);

	//Rotの保管
	SetRot(rot);

	//現在は使われていない（影の判定）
	/*if (groundpos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		CMotionParts::AllSetShadowPos(groundpos, GetMotionNum());
	}*/

	//現在のプレイヤーの位置
	D3DXVECTOR3 PLpos = GetPos();

	//再生するモーション番号
	int nMotionNum = 0;

	//プレイヤーが動いていたら
	if (pInput->Press(KEY_MOVE))
	{
		if (pInput->Press(KEY_DOWN))
		{
			//後ろ歩き用のモーション番号
			nMotionNum = 3;
		}
		else if (pInput->Press(DIK_LSHIFT))
		{
			//ダッシュ用のモーション番号
			nMotionNum = 2;
		}
		else
		{
			//走る用のモーション番号
			nMotionNum = 1;
		}
	}
	
	

	//下半身のモーション設定
	CMotionParts::MoveMotionModel(GetMotionNum(), nMotionNum, &PLpos, &rot);
	//上半身のモーション設定
	CMotionParts::MoveMotionModel(m_nMotionNum1, nMotionNum);





}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CPlayer::Draw()
{
}
