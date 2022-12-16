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
	//リストの更新
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//イテレーターループ
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end(); itr++)
		{
			//イテレーターから瓦礫のポインタの代入
			CBallast* pBallast = *itr;

			//瓦礫ポインタの解放
			if (pBallast != nullptr)
			{
				//更新処理
				pBallast->Update();
			}
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
				pBallast->CalculationMatrix();
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

	//使用するモデル番号
	//pBallast->SetModelPattnNum(Data.nPattn);

	////瓦礫の位置
	//pBallast->SetPos(Data.pos);

	////瓦礫の向き
	//pBallast->SetRot(Data.rot);

	pBallast->Set3DObject(Data.nPattn, Data.pos, Data.rot);

	pBallast->SetNormal();

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

