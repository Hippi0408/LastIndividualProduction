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
#include "enemy_boss.h"
#include "enemy_smallfish.h"
#include "enemy_manager.h"
#include <assert.h>
#include "convenience_function.h"
#include "read.h"
#include "motion_parts.h"

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
	CRead Read;

	m_nEnemySmasllfish = Read.ReadMotion("data/MOTION/motionenemy.txt");

	CMotionParts::UnUpdateDraw(m_nEnemySmasllfish);

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
		pEnemy->Draw();

		
		//イテレーターを進める
		itr++;
	}

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
	case ENEMY_01:
		pEnemy = new CEnemy_SmallFish;
		pEnemy->SetMotionNum(CMotionParts::CopyMotionModel(m_nEnemySmasllfish));
		break;
	case ENEMY_02:
		pEnemy = new CEnemy_Boss;
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

		//当たり判定の中心を半径分上昇させる
		EnemyPos.y += fEnemyRadius;

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

//*****************************************************************************
// プレイヤーとのの当たり判定処理
//*****************************************************************************
bool CEnemy_Manager::PlayerCollision(D3DXVECTOR3 pos, float fRadius)
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

		
		//判定
		bool bHit = CConvenience_Function::CircleCollision(pEnemy->GetPos(), pEnemy->GetRadius(), pos, fRadius);

		//上記の結果がtrue
		if (bHit)
		{
			//処理を抜ける
			return true;
		}

		//イテレーターを進める
		itr++;

		//以下の処理を無視する
		continue;
	}

	return false;
}

//*****************************************************************************
// エネミー同士の当たり判定処理(押し戻し)
//*****************************************************************************
void CEnemy_Manager::EnemyOnEnemyCollision(CEnemy * pTargetEnemy)
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

		//対象エネミーと同じではないか
		if (pEnemy == pTargetEnemy)
		{
			//イテレーターを進める
			itr++;

			//以下の処理を無視する
			continue;
		}

		//判定
		bool bHit = CConvenience_Function::CircleCollision(pEnemy->GetPos(), pEnemy->GetRadius(), pTargetEnemy->GetPos(), pTargetEnemy->GetRadius());

		//上記の結果がfalse
		if (!bHit)
		{
			//イテレーターを進める
			itr++;

			//以下の処理を無視する
			continue;
		}
		
		//位置の保存
		D3DXVECTOR3 Pos1 = pEnemy->GetPos();
		D3DXVECTOR3 Pos2 = pTargetEnemy->GetPos();

		//２この物体の半径同士の和
		float fDiff = pEnemy->GetRadius() + pTargetEnemy->GetRadius();

		//計算用変数
		float fCalculationX, fCalculationZ;

		//Xの差分
		fCalculationX = Pos1.x - Pos2.x;
		//Yの差分
		fCalculationZ = Pos1.z - Pos2.z;

		//現在の２点の距離
		float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationZ * fCalculationZ);

		//押し出す長さ
		float fAddLength = fDiff - fLength;

		//最終的な押し出し値
		D3DXVECTOR3 Add = CConvenience_Function::PointOrientationVectorGeneration(Pos2, Pos1);

		//長さを掛ける
		Add *= fAddLength;
		
		//押し出し
		pTargetEnemy->AddPos(Add);

		//処理を抜ける
		return;
	}



}
