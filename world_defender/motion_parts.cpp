//=============================================================================
//
// motion_parts.cpp
// Author : kozuna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "motion_parts.h"
#include "manager.h"
#include <assert.h>
#include "convenience_function.h"

const D3DXVECTOR3 CMotionParts::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
CMotionParts *CMotionParts::m_pMotionPartsTop = nullptr;
CMotionParts *CMotionParts::m_pMotionPartsCurrent = nullptr;
int CMotionParts::m_nModelMax = 0;
int CMotionParts::m_nMotionPlayMotonNum[MAX_MOTION_ALL] = {};
int CMotionParts::m_nMotionDestMotonNum[MAX_MOTION_ALL] = {};
int CMotionParts::m_nMotionRegistrationNum[MAX_MOTION_ALL] = {};
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CMotionParts::CMotionParts()
{
	m_nFrame = 0;
	m_nKey = 0;
	m_pRarent = nullptr;
	m_bDraw = false;

	if (m_pMotionPartsTop == nullptr)
	{
		m_pMotionPartsTop = this;
	}

	m_pNextMotionParts = nullptr;

	m_pLastTimeMotionParts = GetCurrentMotionParts();

	if (m_pLastTimeMotionParts != nullptr)
	{
		m_pLastTimeMotionParts->SetNextMotionParts(this);

	}
	SetCurrentMotionParts(this);

	m_nModelObjNum = m_nModelMax;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CMotionParts::~CMotionParts()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CMotionParts::Init()
{
	if (FAILED(C3DObject::Init()))
	{
		return -1;
	}
	m_nDestFrame = 0;
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CMotionParts::Uninit()
{
	if (m_pMotionPartsTop == this)
	{
		m_pMotionPartsTop = m_pNextMotionParts;
	}

	if (m_pMotionPartsCurrent == this)
	{
		m_pMotionPartsCurrent = m_pLastTimeMotionParts;
	}

	if (m_pLastTimeMotionParts != nullptr)
	{
		m_pLastTimeMotionParts->SetNextMotionParts(m_pNextMotionParts);
	}

	if (m_pNextMotionParts != nullptr)
	{
		m_pNextMotionParts->SetLastTimeMotionParts(m_pLastTimeMotionParts);
	}

	for (int nMotion = 0; nMotion < m_nMotionRegistrationNum[m_nModelObjNum]; nMotion++)
	{
		if (m_MotionKey[nMotion].pKey != nullptr)
		{
			delete[] m_MotionKey[nMotion].pKey;
			m_MotionKey[nMotion].pKey = nullptr;
		}
	}


	C3DObject::Uninit();

	delete this;
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CMotionParts::Update()
{
	// 目的のフレーム
	m_nDestFrame = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey].nFrame;

	// フレームの加算
	m_nFrame++;
	// 目的のフレーム　＜　現在のフレーム
	if (m_nDestFrame < m_nFrame)
	{
		// 次の位置までの計算
		NextMotionPosition();
		//キー数の確認
		KeyCheck();
		
		m_nFrame = 0;
	}

	// posの加算
	AddPosMove(m_PosMove);
	// rotの加算
	AddRot(m_RotMove);

	D3DXVECTOR3 rot = GetRot();

	//正規化
	rot = CConvenience_Function::NormalizationRot(rot);

	SetRot(rot);


}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CMotionParts::Draw()
{
	D3DXMATRIX mtxRarent;
	D3DXMATRIX mtx;
	CManager *pManager = GetManager();

	LPDIRECT3DDEVICE9 pD3DDevice = nullptr;

	pD3DDevice = pManager->GetDeviceManager();
	// 親が存在する場合
	if (m_pRarent != nullptr)
	{
		mtxRarent = m_pRarent->GetMatrix();
	}
	else
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxRarent);
	}
	
	//自身のマトリックスの計算
	CalculationMatrix();
	mtx = GetMatrix();

	//モデルのマトリックス　＊　親のワールドマトリックス
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRarent);

	SetMatrix(mtx);

	C3DObject::Draw();
}

//*****************************************************************************
//	終了条件処理
//*****************************************************************************
bool CMotionParts::IsUnused()
{
	return false;
}

//*****************************************************************************
//	モーション番号指定でセットする
//*****************************************************************************
void CMotionParts::SetMotion(int nMotionNum)
{
	m_nFrame = 0;
	m_nKey = 0;
	D3DXVECTOR3 pos = m_MotionKey[nMotionNum].pKey[m_nKey].pos;
	D3DXVECTOR3 rot = m_MotionKey[nMotionNum].pKey[m_nKey].rot;

	// 目的のフレーム
	m_nDestFrame = m_MotionKey[nMotionNum].pKey[m_nKey].nFrame;

	m_PosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetParentPos(pos);
	SetRot(rot);
}

//*****************************************************************************
// モーションの移動量などのクリア
//*****************************************************************************
void CMotionParts::ClearMotionMove()
{
	m_nFrame = 0;
	m_nKey = 0;
	m_PosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// 目的のフレーム
	m_nDestFrame = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey].nFrame;

}

//*****************************************************************************
//実際の動きの登録
//*****************************************************************************
void CMotionParts::SetMotionData(KEY_SET KeyData)
{
	m_MotionKey[m_nMotionRegistrationNum[m_nModelObjNum]].bLoop = KeyData.bLoop;
	m_MotionKey[m_nMotionRegistrationNum[m_nModelObjNum]].nKeyMax = KeyData.nKeyMax;
	m_MotionKey[m_nMotionRegistrationNum[m_nModelObjNum]].pKey = KeyData.pKey;
	m_MotionKey[m_nMotionRegistrationNum[m_nModelObjNum]].nNextMotionNum = KeyData.nNextMotionNum;
}

//*****************************************************************************
// キー数の確認
//*****************************************************************************
void CMotionParts::KeyCheck()
{
	//キーのカウントを進める
	m_nKey++;

	//目的のキー数
	int nDestKey = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].nKeyMax;

	//キーが規定より多い場合リセット
	if (m_nKey >= nDestKey)
	{
		m_nKey = 0;

		//今のモーション番号
		int nNowMotionNum = m_nMotionPlayMotonNum[m_nModelObjNum];

		//次に再生するモーション番号（例外の場合再生してた番号にする）
		int nNextMotionNum = nNowMotionNum;

		//ループする場合無視
		if (!m_MotionKey[nNowMotionNum].bLoop)
		{
			//次に再生するモーション番号
			nNextMotionNum = m_MotionKey[nNowMotionNum].nNextMotionNum;

			//現在のパーツがパーツ番号が０かどうか
			if (m_nPartsNum == 0)
			{
				m_nMotionPlayMotonNum[m_nModelObjNum] = 0;

				ClearMotionMove();


				AllNextMotionPosition(m_nModelObjNum);

				

				//SetMotion(nNextMotionNum);

				//MoveMotionModel(m_nModelObjNum, nNextMotionNum);

				////次に再生するモーション番号
				//nNextMotionNum = m_MotionKey[nNowMotionNum].nNextMotionNum;

				//m_nMotionPlayMotonNum[m_nModelObjNum] = nNextMotionNum;
			}
			else
			{
				ClearMotionMove();
			}
		}
	}
}

//*****************************************************************************
// 次の位置までの計算
//*****************************************************************************
void CMotionParts::NextMotionPosition()
{
	D3DXVECTOR3 nowPos, nextPos,nowRot, nextRot;
	int nFrameRatio;
	//目的のキー数
	int nDestKey = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].nKeyMax;
	
	//現在のKEYが目的を超えたら
	if (m_nKey >= nDestKey - 1)
	{
		//今の位置
		nowPos = GetPosMove();
		//次の位置
		nextPos = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[0].pos;
		//今の向き
		nowRot = GetRot();
		//次の向き
		nextRot = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[0].rot;
		//全体フレーム数に対しての割合
		nFrameRatio = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[0].nFrame;
	}
	else
	{
		//今の位置
		nowPos = GetPosMove();
		//次の位置
		nextPos = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey + 1].pos;
		//今の向き
		nowRot = GetRot();
		
		//全体フレーム数に対しての割合
		nFrameRatio = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey + 1].nFrame;

		//次の向き
		nextRot = m_MotionKey[m_nMotionPlayMotonNum[m_nModelObjNum]].pKey[m_nKey + 1].rot;
	}
	
	//1フレームあたりの動く向き
	D3DXVECTOR3 rotMove;
	//1フレームあたりの動く位置
	D3DXVECTOR3 posMove;
	
	//目的の位置　ー　現在の位置
	D3DXVECTOR3 pos = nextPos - nowPos;

	//目的の向き　ー　現在の向き
	D3DXVECTOR3 rot = nextRot - nowRot;

	//正規化
	rot = CConvenience_Function::NormalizationRot(rot);

	//割合計算
	//位置
	posMove = pos / nFrameRatio;
	m_PosMove = posMove;
	//向き
	rotMove = CConvenience_Function::NormalizationRot(rot / nFrameRatio) ;

	//正規化
	rotMove = CConvenience_Function::NormalizationRot(rotMove);

	m_RotMove = rotMove;
}

//*****************************************************************************
//全部のパーツ次の位置までの計算
//*****************************************************************************
void CMotionParts::AllNextMotionPosition(int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetModelObjNum() == nMotionNum)
		{
			pMotionParts->ClearMotionMove();
			pMotionParts->NextMotionPosition();
		}

		pMotionParts = pMotionParts->GetNextMotionParts();
	}

}

//*****************************************************************************
// 引数との一致があるかどうか
//*****************************************************************************
bool CMotionParts::GetMotionParts(int nMotionNum, int nPartsNum)
{
	if (m_nModelObjNum == nMotionNum
		&& m_nPartsNum == nPartsNum)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// 引数との一致があるかどうか
//*****************************************************************************
bool CMotionParts::GetMotionParts(int nMotionNum)
{
	if (m_nModelObjNum == nMotionNum)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// ALL終了処理
//*****************************************************************************
void CMotionParts::ALLUninit()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		CMotionParts* pMotionPartsNext = pMotionParts->GetNextMotionParts();
		pMotionParts->Uninit();
		pMotionParts = pMotionPartsNext;
	}
}

//*****************************************************************************
// ALL更新処理
//*****************************************************************************
void CMotionParts::ALLUpdate()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		pMotionParts->Update();

		if (pMotionParts->IsUnused())
		{
			CMotionParts* pMotionPartsBreak = pMotionParts;
			pMotionParts = pMotionPartsBreak->GetNextMotionParts();
			pMotionPartsBreak->Uninit();
		}
		else
		{
			pMotionParts = pMotionParts->GetNextMotionParts();
		}
	}
}

//*****************************************************************************
// ALL描画処理
//*****************************************************************************
void CMotionParts::ALLDraw()
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetBoolDraw())
		{
			pMotionParts = pMotionParts->GetNextMotionParts();
			continue;
		}
		pMotionParts->Draw();
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
// 動くOBJの生成
//*****************************************************************************
int CMotionParts::CreateMotionObj(MotionData* pMotionData, int nPartsMax)
{
	for (int nCnt = 0; nCnt < nPartsMax; nCnt++)
	{
		CMotionParts* pMotionParts = new CMotionParts;

		if (FAILED(pMotionParts->Init()))
		{
			assert(false);
		}

		pMotionParts->SetPartsNum(nCnt);//一つのモーションの中の番号
		//pMotionParts->SetModelPattnNum(pMotionData[nCnt].nModelPattern);//使用するモデルのインデックス
		//pMotionParts->SetPos(pMotionData[nCnt].pos);//モデルの位置
		//pMotionParts->SetRot(pMotionData[nCnt].rot);//モデルの向き

		pMotionParts->Set3DObject(pMotionData[nCnt].nModelPattern, pMotionData[nCnt].pos, pMotionData[nCnt].rot);
		
		if (pMotionData[nCnt].nParentNum >= 0)
		{
			//親の設定
			pMotionParts->SetMotionRarent(GetMotionPartsPointer(m_nModelMax, pMotionData[nCnt].nParentNum));
		}
		
		pMotionParts->SetNormal();
	}

	int nModelNum = m_nModelMax;

	//動く物体の登録完了
	SettingCompletion();

	return nModelNum;

}

//*****************************************************************************
// 条件に合うポインタを返す
//*****************************************************************************
CMotionParts * CMotionParts::GetMotionPartsPointer(int nMotionNum, int nPartsNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum, nPartsNum))
		{
			return pMotionParts;
		}

		pMotionParts = pMotionParts->GetNextMotionParts();
	}

	return nullptr;
}

//*****************************************************************************
//モーションモデルの移動
//*****************************************************************************
void CMotionParts::MoveMotionModel(int nModelNum, int nMotionNum, D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	CMotionParts* pMotionParts = CMotionParts::GetMotionPartsPointer(nModelNum, 0);

	if (pMotionParts->GetMotionData().bLoop)
	{
		if (m_nMotionPlayMotonNum[nModelNum] != nMotionNum)
		{
			m_nMotionPlayMotonNum[nModelNum] = nMotionNum;
			//全体の次までの位置の計算
			AllNextMotionPosition(nModelNum);
		}
	}

	if (pos == rot)
	{
		return;
	}

	if (pos != nullptr)
	{
		GetMotionPartsPointer(nModelNum, 0)->SetParentPos(*pos);
	}

	if (rot != nullptr)
	{
		GetMotionPartsPointer(nModelNum, 0)->SetParentRot(*rot);
	}
}

//*****************************************************************************
//モーションモデルの描画の有無
//*****************************************************************************
void CMotionParts::SetBoolDraw(bool bDraw, int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum))
		{
			pMotionParts->SetBoolDraw(bDraw);
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
//モーションモデルのライトベクトル
//*****************************************************************************
void CMotionParts::SetLight(D3DXVECTOR3 vec, int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum))
		{
			pMotionParts->SetLightVec(vec);
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
//影の設定
//*****************************************************************************
void CMotionParts::AllSetShadowPos(D3DXVECTOR3 pos, int nMotionNum)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if (pMotionParts->GetMotionParts(nMotionNum))
		{
			D3DXVECTOR3 ShadowPos = pMotionParts->GetWorldPos();
			ShadowPos.y = pos.y;
			pMotionParts->SetShadowPos(ShadowPos);
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}
}

//*****************************************************************************
//モーションの登録
//*****************************************************************************
void CMotionParts::SetMotionFileData(const MotionMoveData MotionMoveData, int nMotionNum)
{
	CMotionParts* pMotionParts = nullptr;//一時保管場所
	int nPartsNum = 0;//カウンター
	pMotionParts = GetMotionPartsPointer(nMotionNum, nPartsNum);//条件に合うポインタの獲得
	while (pMotionParts != nullptr)
	{
		//一時保管場所
		KEY_SET KeySet;

		KeySet.pKey = new KEY[MotionMoveData.nKeyMax];

		for (int nCnt = 0; nCnt < MotionMoveData.nKeyMax; nCnt++)
		{
			//フレーム
			KeySet.pKey[nCnt].nFrame = MotionMoveData.pMotionKeyData[nCnt].nFrame;
			//Pos
			KeySet.pKey[nCnt].pos = MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData[nPartsNum].pos;
			//Rot
			KeySet.pKey[nCnt].rot = MotionMoveData.pMotionKeyData[nCnt].pMotionPartsData[nPartsNum].rot;
		}

		//ループ設定
		KeySet.bLoop = MotionMoveData.bLoop;
		//キーの最大
		KeySet.nKeyMax = MotionMoveData.nKeyMax;
		//次に再生するモーション番号
		KeySet.nNextMotionNum = MotionMoveData.nNextMotionNum;

		//登録
		pMotionParts->SetMotionData(KeySet);

		nPartsNum++;//カウンターを進める
		pMotionParts = GetMotionPartsPointer(nMotionNum, nPartsNum);//条件に合うポインタの獲得
	}
	
	//モーションの登録完了数
	m_nMotionRegistrationNum[nMotionNum]++;
}

//*****************************************************************************
//当たり判定（自分のモデル番号、自分の位置）
//*****************************************************************************
D3DXVECTOR3 CMotionParts::AllCollision(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos, int nMotionNum, int nIgnored1, int nIgnored2, int nIgnored3, int nIgnored4)
{
	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		int nNum = pMotionParts->GetModelObjNum();
		if (nNum != nMotionNum 
			&& nNum != nIgnored1
			&& nNum != nIgnored2
			&& nNum != nIgnored3
			&& nNum != nIgnored4
			)
		{
			//D3DXVECTOR3 Add = pMotionParts->Collision(pos, oldpos);
			/*if (Add != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				return Add;
			}*/

			if (pMotionParts->NormalCollision(pos))
			{
				return pos * -1.0f;
			}
			
		}
		pMotionParts = pMotionParts->GetNextMotionParts();
	}

	return pos;
}

//*****************************************************************************
//親を後天的に設定する（子供番号、親番号）
//*****************************************************************************
void CMotionParts::SettingParent(int nChildren, int nParent)
{
	if (nChildren == nParent)
	{
		return;
	}

	CMotionParts* pMotionPartsChildren = nullptr;
	CMotionParts* pMotionPartsParent = nullptr;

	CMotionParts* pMotionParts = m_pMotionPartsTop;

	while (pMotionParts != nullptr)
	{
		if(pMotionParts->GetMotionParts(nChildren,0))
		{
			pMotionPartsChildren = pMotionParts;
		}

		if (pMotionParts->GetMotionParts(nParent, 0))
		{
			pMotionPartsParent = pMotionParts;
		}

		pMotionParts = pMotionParts->GetNextMotionParts();
	}

	if (pMotionPartsChildren == nullptr || pMotionPartsParent == nullptr)
	{
		return;
	}

	if (pMotionPartsChildren->GetMotionRarent() == nullptr)
	{
		pMotionPartsChildren->SetMotionRarent(pMotionPartsParent);
	}


}