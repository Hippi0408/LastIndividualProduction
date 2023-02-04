//=============================================================================
//
// enemy_boss.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy_boss.h"
#include "read.h"
#include "game.h"
#include "meshfield.h"
#include "motion_parts.h"
#include "player.h"
#include "input.h"
#include "object_type_list.h"
#include "convenience_function.h"
#include "psychokinesis_area.h"
#include "statgauge.h"
#include "camera.h"
#include "player.h"

const D3DXVECTOR3 CEnemy_Boss::INIT_POS = D3DXVECTOR3(1000.0f, 0.0f, -0.0f);
const float CEnemy_Boss::MOVE_INERTIA = 0.1f;
const float CEnemy_Boss::JUMP_INERTIA = 0.1f;
const float CEnemy_Boss::INIT_RADIUS = 1600.0f;
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy_Boss::CEnemy_Boss()
{
	CMovable_Obj::SetLife(INIT_LIFE);
	CMovable_Obj::SetRadius(INIT_RADIUS);
	m_pLife = nullptr;
	m_bAppearanceMotion = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy_Boss::~CEnemy_Boss()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemy_Boss::Init()
{
	//マネージャーからゲームの情報取得
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();

	//周回カメラの設定
	pGame->SetRoundCamera(300);

	//カメラの振動設定
	pGame->SetVibration(300,70);

	CStatGauge::SStatGauge StatGauge;

	StatGauge.pos = D3DXVECTOR3(150.0f, 60.0f, 0.0f);
	StatGauge.rot = D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.5f);
	StatGauge.color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	StatGauge.fXSize = 60.0f;
	StatGauge.fYSize = 1200.0f;
	StatGauge.nValueMax = INIT_LIFE;
	StatGauge.nRecoveryCntMaqx = 0;
	StatGauge.nRecovery = 0;

	m_pLife = new CStatGauge;
	if (FAILED(m_pLife->Init()))
	{
		return -1;
	}
	m_pLife->CreateStatBar(StatGauge);

	//ライフの設定
	SetLife(INIT_LIFE);

	//初期の位置
	SetPos(INIT_POS);

	//１フレーム前の位置
	SetOldPos(INIT_POS);

	//移動量の初期化
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//向きの初期化
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// モーションモデルの設定処理
	SetMotionModel();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemy_Boss::Uninit()
{
	if (m_pLife != nullptr)
	{
		m_pLife->Uninit();
		delete m_pLife;
		m_pLife = nullptr;
	}

}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEnemy_Boss::Update()
{
	//ライフゲージの更新と死亡チェック
	if (m_pLife != nullptr)
	{
		//死亡チェック
		if (m_pLife->ValueCheck())
		{
			//マネージャーの情報を取得
			CManager * pManager = GetManager();

			//次のモードに移行
			pManager->NextMode(TYPE_RESULT,300);

			//マネージャーからゲームの情報を取得
			CGame* pGame = (CGame*)pManager->GetGameObject();

			//周回カメラの設定
			pGame->SetRoundCamera(400);

			//カメラの振動設定
			pGame->SetVibration(400,70);

			//死亡モーションの再生
			CMotionParts::MoveMotionModel(GetMotionNum(), 4, &GetPos(), &GetRot(), true);

			//これより下の全処理を無視する
			return;
		}

		//ライフの更新
		m_pLife->Update();

	}

	//親クラスの更新
	CMovable_Obj::Update();

	//マネージャーの取得
	CManager *pManager = GetManager();

	//マネージャーからゲームの情報取得
	CGame* pGame = (CGame*)pManager->GetGameObject();

	//地面との当たり判定用
	D3DXVECTOR3 pos, groundpos;

	//位置を取得
	pos = GetPos();

	//立っている地面の高さを取得
	groundpos = pGame->GetMeshfield()->Collision(pos);

	//現在の高さと比較
	if (pos.y < groundpos.y)
	{
		//高さの変更
		pos.y = groundpos.y;
		SetPos(pos);
	}

	//入力デバイスの取得
	CInput *pInput = CInput::GetKey();

	//移動量の一時保管
	D3DXVECTOR3 move = GetMove();

	//Move倍率
	float fMove = 50.0f;

	//視点移動
	if (pInput->Press(DIK_UP))
	{//上キーが押された
		if (pInput->Press(DIK_LEFT))
		{
			move.x = -sinf(D3DX_PI * 0.75f) * fMove;
			move.z = -cosf(D3DX_PI * 0.75f) * fMove;
		}
		else if (pInput->Press(DIK_RIGHT))
		{
			move.x = -sinf(D3DX_PI * -0.75f) * fMove;
			move.z = -cosf(D3DX_PI * -0.75f) * fMove;
		}
		else
		{
			move.x = sinf(0.0f) * fMove;
			move.z = cosf(0.0f) * fMove;
		}
	}
	else if (pInput->Press(DIK_DOWN))
	{//下キーが押された
		if (pInput->Press(DIK_LEFT))
		{
			move.x = -sinf(D3DX_PI * 0.25f) * fMove;
			move.z = -cosf(D3DX_PI * 0.25f) * fMove;
		}
		else if (pInput->Press(DIK_RIGHT))
		{
			move.x = -sinf(D3DX_PI * -0.25f) * fMove;
			move.z = -cosf(D3DX_PI * -0.25f) * fMove;
		}
		else
		{
			move.x = sinf(D3DX_PI) * fMove;
			move.z = cosf(D3DX_PI) * fMove;
		}
	}
	else if (pInput->Press(DIK_LEFT))
	{//左キーが押された
		move.x = sinf(D3DX_PI * -0.5f) * fMove;
		move.z = cosf(D3DX_PI * -0.5f) * fMove;
	}
	else if (pInput->Press(DIK_RIGHT))
	{//右キーが押された
		move.x = sinf(D3DX_PI * 0.5f) * fMove;
		move.z = cosf(D3DX_PI * 0.5f) * fMove;
	}

	//移動量を保管
	SetMove(move);

	//周回カメラのposRの設定
	pGame->SetRoundCameraPosR(pos);

	//モーションの再生
	if (pGame->CheckVibration() && !m_bAppearanceMotion)
	{//登場シーン用
		m_bAppearanceMotion = true;
		CMotionParts::MoveMotionModel(GetMotionNum(), 3, &GetPos(), &GetRot());
	}
	else if (pInput->Press(KEY_MOVE))
	{//移動用
		CMotionParts::MoveMotionModel(GetMotionNum(), 1, &GetPos(), &GetRot());
	}
	else
	{//ニュートラルモーション用
		CMotionParts::MoveMotionModel(GetMotionNum(), 0, &GetPos(), &GetRot());
	}

	//動いていなかったら以下の処理を無視する
	if (!pInput->Press(DIK_UP) &&
		!pInput->Press(DIK_DOWN) &&
		!pInput->Press(DIK_LEFT) &&
		!pInput->Press(DIK_RIGHT))
	{
		return;
	}

	//ボスとプレイヤーとの距離保存用変数
	float fPointDistance = 0.0f;

	//ボスとプレイヤーとの距離
	fPointDistance = CConvenience_Function::PointDistance(GetPos(),pGame->GetPlayer()->GetPos());

	//実際に起こす振動量
	int nVibration = 0;

	//ボスが歩くことによる振動
	for (int nCnt = 1; nCnt <= MOVE_VIBRATION; nCnt++)
	{
		//一定距離離れている場合は振動をなくす
		if (fPointDistance < INIT_RADIUS * nCnt)
		{
			nVibration = MOVE_VIBRATION * nCnt;
		}
	}

	//振動量が0のとき
	if (nVibration == 0)
	{
		return;
	}
	
	//カメラの振動設定
	pGame->SetVibration(10, nVibration);

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemy_Boss::Draw()
{
}

//*****************************************************************************
// 終了条件処理
//*****************************************************************************
bool CEnemy_Boss::IsUnused()
{

	if (CMovable_Obj::CheckLife())
	{
		

		return true;
	}


	return false;
}

//*****************************************************************************
// モーションモデルの設定処理
//*****************************************************************************
void CEnemy_Boss::SetMotionModel()
{
	CRead cRead;

	SetMotionNum(cRead.ReadMotion("data/MOTION/motionboss.txt"));

	CMotionParts::AllSetObject_Type_List(GetMotionNum(), OBJ_ENEMY);
}

//*****************************************************************************
// HPの減少
//*****************************************************************************
void CEnemy_Boss::AddLife(int nAdd)
{
	CMovable_Obj::AddLife(nAdd);

	m_pLife->SetStatGauge(nAdd);
}
