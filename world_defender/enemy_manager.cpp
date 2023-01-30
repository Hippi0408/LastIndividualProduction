//=============================================================================
//
// enemy_manager.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy.h"
#include "enemy_manager.h"
#include <assert.h>
#include "convenience_function.h"

const float CEnemy_Manager::RADIUS_TYPE[] = { 40.0f ,30.0f ,20.0f ,10.0f ,0.0f };
const int CEnemy_Manager::DAMAGE_TYPE[] = { 40 ,30 ,20 ,10 ,0 };

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CEnemy_Manager::CEnemy_Manager()
{
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CEnemy_Manager::~CEnemy_Manager()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CEnemy_Manager::Init()
{
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CEnemy_Manager::Uninit()
{
	//イテレーターループ
	for (auto itr = m_EnemyList.begin(); itr != m_EnemyList.end();)
	{
		//イテレーターからエネミーのポインタの代入
		CEnemy* pEnemy = *itr;

		//エネミーポインタの解放
		if (pEnemy != nullptr)
		{
			//終了処理
			pEnemy->Uninit();
			delete pEnemy;
			pEnemy = nullptr;
		}

		//次のイテレーターの代入、現在のイテレーターを破棄
		itr = m_EnemyList.erase(itr);
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CEnemy_Manager::Update()
{
	//イテレーターループ
	for (auto itr = m_EnemyList.begin(); itr != m_EnemyList.end();)
	{
		//イテレーターからエネミーのポインタの代入
		CEnemy* pEnemy = *itr;

		//エネミーポインタの解放
		if (pEnemy == nullptr)
		{
			//次のイテレーターの代入、現在のイテレーターを破棄
			itr = m_EnemyList.erase(itr);

			//以下の処理を無視する
			continue;
		}

		//エネミーの更新処理
		pEnemy->Update();

		//終了条件処理
		if (pEnemy->IsUnused())
		{
			//終了処理
			pEnemy->Uninit();
			delete pEnemy;
			pEnemy = nullptr;

			//次のイテレーターの代入、現在のイテレーターを破棄
			itr = m_EnemyList.erase(itr);

			//以下の処理を無視する
			continue;
		}

		//イテレーターを進める
		itr++;
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CEnemy_Manager::Draw()
{
}

//*****************************************************************************
// クリエイト処理
//*****************************************************************************
void CEnemy_Manager::CreateEnemy(EnemyInitData enemyinitdata)
{
	//エネミークラスのポインタ変数
	CEnemy* pEnemy = nullptr;

	//エネミークラスの生成
	switch (enemyinitdata.type)
	{
	case ENEMY_00:
		pEnemy = new CEnemy;
		break;
	default:
		assert(false);
		break;
	}
	
	//初期化
	if (FAILED(pEnemy->Init()))
	{
		assert(false);
	}

	//エネミーの位置
	pEnemy->SetPos(enemyinitdata.pos);

	//エネミーの向き
	pEnemy->SetRot(enemyinitdata.rot);

	//エネミー移動量
	pEnemy->SetMovingDistance(enemyinitdata.fmove);

	//リストにエネミー情報を追加
	m_EnemyList.push_back(pEnemy);
}

//*****************************************************************************
// 当たり判定処理
//*****************************************************************************
bool CEnemy_Manager::EnemyCollision(D3DXVECTOR3 pos, float fRadius)
{
	//イテレーターループ
	for (auto itr = m_EnemyList.begin(); itr != m_EnemyList.end();)
	{
		//イテレーターからエネミーのポインタの代入
		CEnemy* pEnemy = *itr;

		//エネミーポインタの解放
		if (pEnemy == nullptr)
		{
			//次のイテレーターの代入、現在のイテレーターを破棄
			itr = m_EnemyList.erase(itr);

			//以下の処理を無視する
			continue;
		}

		//エネミーの体力の確認
		if (pEnemy->CheckLife())
		{
			//イテレーターを進める
			itr++;

			//以下の処理を無視する
			continue;
		}

		//エネミー位置
		D3DXVECTOR3 EnemyPos = pEnemy->GetPos();
		//エネミー半径
		float fEnemyRadius = pEnemy->GetRadius();


		//エネミーの当たり判定処理
		bool bHit = CConvenience_Function::SphereCollision(pos, fRadius, EnemyPos, fEnemyRadius);
		
		//当たっていなかったら
		if (!bHit)
		{
			//イテレーターを進める
			itr++;

			//以下の処理を無視する
			continue;
		}

		//ダメージ量の決定
		for (int nCnt = 0; nCnt < DAMAGE_TYPE_MAX; nCnt++)
		{
			if (!(RADIUS_TYPE[nCnt] <= fRadius))
			{
				//以下の処理を無視する
				continue;
			}

			//ダメージの発生
			pEnemy->AddLife(-DAMAGE_TYPE[nCnt]);

			return true;
			
		}

		//イテレーターを進める
		itr++;
	}


	return false;
}
