//=============================================================================
//
// 瓦礫処理 [ballast_acquired.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "ballast_acquired.h"
#include "convenience_function.h"
#include "manager.h"
#include "game.h"
#include "meshfield.h"
#include "ballast_manager.h"

const float CBallast_Acquired::GRAVITY = -0.5f;
const float CBallast_Acquired::MOVE_ATTENUATION = 0.1f;
const float CBallast_Acquired::MOVE_MAGNIFICATION = 3.0f;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBallast_Acquired::CBallast_Acquired()
{
	m_Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBallast_Acquired::~CBallast_Acquired()
{
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBallast_Acquired::Update()
{

	D3DXVECTOR3 move = GetPosMove();

	move += (move - D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * MOVE_ATTENUATION;

	SetPosMove(move);

	if (GetParentPos().y < 0.0f)
	{
		SetPosMove(D3DXVECTOR3(0.0f,0.0f,0.0f));

		D3DXVECTOR3 pos = GetParentPos();
		SetParentPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));

		CManager* pManager = GetManager();
		CGame* pGame = (CGame*)pManager->GetGameObject();
		CMeshfield* pMeshfield = pGame->GetMeshfield();
		//マップチップの番号
		int nMap = pMeshfield->CheckPosLocation(GetParentPos());
		//上記の保存
		SetListNumber(nMap);

		CBallast_Manager* pBallast_Manager = pGame->GetBallast_Manager();

		//リストの入れ替え
		pBallast_Manager->ReplacementList(this, nMap);
	}
	else if(GetParentPos().y > 0.0f)
	{
		move.y += GRAVITY;

		SetPosMove(move);
	}

	//親クラスの更新
	CBallast::Update();
}

//*****************************************************************************
// ぶっ飛ぶベクトルの設定
//*****************************************************************************
void CBallast_Acquired::SetVec(D3DXVECTOR3 Vec)
{
	//保存
	m_Vec = Vec;

	//移動量
	D3DXVECTOR3 move = m_Vec * MOVE_MAGNIFICATION;

	SetPosMove(move);
}
