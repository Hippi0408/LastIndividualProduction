//=============================================================================
//
// 瓦礫の管理者処理 [ballast_manager.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "ballast_manager.h"
#include "ballast.h"
#include <assert.h>
#include "game.h"
#include "manager.h"
#include "meshfield.h"
#include "convenience_function.h"
#include "enemy_manager.h"

const float CBallast_Manager::MAP_MAX = 15000.0f;
const D3DXVECTOR3 CBallast_Manager::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBallast_Manager::CBallast_Manager()
{
	m_nPlListNumber = 0;
	m_nMeshfieldNumMax = 0;
	m_pMeshfieldCopy = nullptr;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBallast_Manager::~CBallast_Manager()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CBallast_Manager::Init()
{
	m_nPlListNumber = 0;
	m_nMeshfieldNumMax = 0;
	m_pMeshfieldCopy = nullptr;

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBallast_Manager::Uninit()
{
	//リストの解放
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//イテレーターループ
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end();)
		{
			//イテレーターから瓦礫のポインタの代入
			CBallast* pBallast = *itr;
			
			//瓦礫ポインタの解放
			if (pBallast != nullptr)
			{
				//終了処理
				pBallast->Uninit();
				delete pBallast;
				pBallast = nullptr;
			}

			//次のイテレーターの代入、現在のイテレーターを破棄
			itr = m_BallastMapData[nCnt].erase(itr);
		}
	}
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBallast_Manager::Update()
{
	//エネミーとの当たり判定
	CollisionEnemy();

	//リストの更新
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//イテレーターループ
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end(); )
		{
			//イテレーターから瓦礫のポインタの代入
			CBallast* pBallast = *itr;

			//瓦礫ポインタの更新処理
			if (pBallast == nullptr)
			{
				assert(false);
			}

			//使用状態かどうか
			if (pBallast->GetUse())
			{
				D3DXVECTOR3 pos = pBallast->GetWorldPos();
				//エリア外にあるかどうか
				if (CConvenience_Function::CircleCollision(D3DXVECTOR3(0.0f,0.0f,0.0f), MAP_MAX, pos, 0.0f))
				{
					//更新処理
					pBallast->Update();

					//イテレーターを進める
					itr++;

					continue;
				}
			}
			
			
			//終了処理
			pBallast->Uninit();

			//破棄
			delete pBallast;
			pBallast = nullptr;

			//次のイテレーターの代入、現在のイテレーターを破棄
			itr = m_BallastMapData[nCnt].erase(itr);
		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBallast_Manager::Draw()
{
	//リストの更新
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//イテレーターループ
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end(); itr++)
		{
			//イテレーターから瓦礫のポインタの代入
			CBallast* pBallast = *itr;

			//瓦礫の描画
			if (pBallast != nullptr)
			{
				//描画処理
				pBallast->Draw();
			}
		}
	}
}

//*****************************************************************************
//瓦礫の設定
//*****************************************************************************
void CBallast_Manager::SetBallast(int nNumber, Object_Data Data)
{
	//瓦礫クラスの生成
	CBallast* pBallast = new CBallast;

	//初期化
	if (FAILED(pBallast->Init()))
	{
		assert(false);
	}

	//メッシュ内の位置（番号）
	pBallast->SetListNumber(nNumber);

	//使用するモデル番号、瓦礫の位置、瓦礫の向き
	pBallast->Set3DObject(Data.nPattn, Data.pos, Data.rot);

	//法線設定
	pBallast->SetNormal();

	//半径設定
	pBallast->SetRadius();

	//リストに瓦礫情報を追加
	m_BallastMapData[nNumber].push_back(pBallast);
}

//*****************************************************************************
//メッシュフィールドの設定
//*****************************************************************************
void CBallast_Manager::MeshfieldSet(CMeshfield* pMeshfield)
{
	//保存先のNullチェック
	if (m_pMeshfieldCopy != nullptr)
	{
		assert(false);
	}

	//ゲームから地面（メッシュ）の取得
	m_pMeshfieldCopy = pMeshfield;

	//メッシュのマスの数の最大の設定
	m_nMeshfieldNumMax = m_pMeshfieldCopy->GetMeshfieldNumMax();

}

//*****************************************************************************
//サイコキネシスエリアにあったらそのオブジェクトのポインタを返す
//*****************************************************************************
CBallast * CBallast_Manager::CheckCircleCollision(D3DXVECTOR3 pos, float fRadius)
{
	//リストの更新
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//イテレーターループ
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end(); itr++)
		{
			//イテレーターから瓦礫のポインタの代入
			CBallast* pBallast = *itr;

			//瓦礫NULLチェック
			if (pBallast == nullptr)
			{
				assert(false);
			}

			//浮遊状態かどうか
			if (pBallast->GetFloating())
			{
				continue;
			}

			//サイコキネシスエリアにあるかどうかpBallast->GetVtxMax().x
			if (CConvenience_Function::CircleCollision(pos,fRadius, pBallast->GetPos(), 0.0f))
			{
				return pBallast;
			}

		}
	}

	return nullptr;
}

//*****************************************************************************
//サイコキネシスエリアにあったらそのオブジェクトの色を変える
//*****************************************************************************
void CBallast_Manager::WithinRangeColor(int nMapGrid, D3DXVECTOR3 pos, float fRadius)
{
	//イテレーターループ
	for (auto itr = m_BallastMapData[nMapGrid].begin(); itr != m_BallastMapData[nMapGrid].end(); itr++)
	{
		//変数宣言
		D3DXVECTOR3 Extrusion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//イテレーターから瓦礫のポインタの代入
		CBallast* pBallast = *itr;

		//瓦礫NULLチェック
		if (pBallast == nullptr)
		{
			assert(false);
		}

		//浮遊状態かどうか
		if (pBallast->GetFloating())
		{
			pBallast->SetWithinRangeColor(false);
			continue;
		}

		//サイコキネシスエリアにあるかどうかpBallast->GetVtxMax().x
		if (CConvenience_Function::CircleCollision(pos, fRadius, pBallast->GetPos(), 0.0f))
		{
			pBallast->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f), 0.05f);
			pBallast->SetWithinRangeColor(true);
		}
		else
		{
			pBallast->SetWithinRangeColor(false);
		}

	}
}

//*****************************************************************************
//障害物の当たり判定
//*****************************************************************************
D3DXVECTOR3 CBallast_Manager::CollisionBallast(int nMapGrid, D3DXVECTOR3 pos, D3DXVECTOR3 oldpos, D3DXVECTOR3 max, D3DXVECTOR3 min)
{
	D3DXVECTOR3 Add = pos;

	//イテレーターループ
	for (auto itr = m_BallastMapData[nMapGrid].begin(); itr != m_BallastMapData[nMapGrid].end(); itr++)
	{
		//変数宣言
		D3DXVECTOR3 Extrusion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//イテレーターから瓦礫のポインタの代入
		CBallast* pBallast = *itr;

		//瓦礫NULLチェック
		if (pBallast == nullptr)
		{
			assert(false);
		}

		//浮遊状態かどうか
		if (pBallast->GetFloating())
		{
			continue;
		}

		//押し出し判定
		Extrusion = pBallast->ConclusionCollision(pos, oldpos, max, min);

		//押し出しがあったかどうか
		if (Extrusion != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			//押し出し変数に入れる
			Add = Extrusion;

			//for文を抜ける
			break;
		}

	}

	//押し出す値を返す
	return Add;
}

//*****************************************************************************
//エネミーとの当たり判定
//*****************************************************************************
void CBallast_Manager::CollisionEnemy()
{
	//マネージャーからエネミーマネージャーの取得
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();
	CEnemy_Manager* pEnemy_Manager = pGame->GetEnemy_Manager();

	//イテレーターループ
	for (auto itr = m_FloatingBallstList.begin(); itr != m_FloatingBallstList.end();)
	{
		//イテレーターから瓦礫のポインタの代入
		CBallast* pBallast = *itr;

		//瓦礫NULLチェック
		if (pBallast == nullptr)
		{
			assert(false);
		}

		//浮遊状態かどうか
		if (!pBallast->GetFloating())
		{
			continue;
		}

		//判定
		bool bHit = pEnemy_Manager->EnemyCollision(pBallast->GetWorldPos(), pBallast->GetRadius());

		if (!bHit)
		{
			//イテレーターを進める
			itr++;

			//処理を無視する
			continue;
		}

		//瓦礫の使用状態を変更
		pBallast->SetUse(false);

		//次のイテレーターの代入、現在のイテレーターを破棄
		itr = m_FloatingBallstList.erase(itr);

	}

}

//*****************************************************************************
//浮遊状態のリスト追加
//*****************************************************************************
void CBallast_Manager::SetFloatingBallst(CBallast * pBallast)
{
	//リストに瓦礫情報を追加
	m_FloatingBallstList.push_back(pBallast);
}

