//=============================================================================
//
// 瓦礫処理 [ballast.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "ballast.h"


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CBallast::CBallast()
{
	m_nListNumber = 0;
	m_MoveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bFloating = false;
	m_ParentPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CBallast::~CBallast()
{
}

//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT CBallast::Init()
{
	//使用する
	m_bUse = true;

	//初期化
	if (FAILED(C3DObject::Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CBallast::Uninit()
{
	//親クラスの終了処理
	C3DObject::Uninit();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CBallast::Update()
{
	//各情報の取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetPosMove();
	D3DXVECTOR3 rot = GetRot();

	//子の位置の更新
	pos += move;
	SetPos(pos);

	//向きの更新
	rot += m_MoveRot;
	SetRot(rot);

	//親位置の更新
	AddParentPos(m_ParentPosMove);

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CBallast::Draw()
{
	//マトリックスの計算
	CalculationMatrix();
	//親クラスの描画処理
	C3DObject::Draw();
}

//*****************************************************************************
//	当たり判定(まとめ)
//*****************************************************************************
D3DXVECTOR3 CBallast::ConclusionCollision(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos, D3DXVECTOR3 max, D3DXVECTOR3 min)
{
	//最終的な押し出し値
	D3DXVECTOR3 Add = pos;

	//対象のPos
	D3DXVECTOR3 TargetPos = pos;
	
	//接触確認用変数
	D3DXVECTOR3 HittingTargetPosMax[SURFACE_MAX], HittingTargetPosMin[SURFACE_MAX], HittingTargetOldPosMax[SURFACE_MAX], HittingTargetOldPosMin[SURFACE_MAX];

	//モデルの位置
	D3DXVECTOR3 ModelPos = GetPos();
	D3DXVECTOR3 ModelMax = GetVtxMax();
	D3DXVECTOR3 ModelMin = GetVtxMin();

	if (!(pos.x + max.x >= ModelPos.x + ModelMin.x &&
		pos.x + min.x <= ModelPos.x + ModelMax.x &&
		pos.z + max.z >= ModelPos.z + ModelMin.z &&
		pos.z + min.z <= ModelPos.z + ModelMax.z &&
		pos.y + min.y <= ModelPos.y + ModelMax.y))
	{
		//押し出す値を返す
		return Add;
	}



	
	//側面(9時方向からの侵入)
	if (pos.x + max.x > ModelPos.x + ModelMin.x &&
		oldpos.x + max.x <= ModelPos.x + ModelMin.x)
	{
		Add.x = (ModelPos.x + ModelMin.x - max.x);
	}

	//側面(3時方向からの侵入)
	if (pos.x + min.x < ModelPos.x + ModelMax.x &&
		oldpos.x + min.x >= ModelPos.x + ModelMax.x)
	{
		Add.x = (ModelPos.x + ModelMax.x - min.x);
	}

	//側面(6時方向からの侵入)
	if (pos.z + max.z > ModelPos.z + ModelMin.z &&
		oldpos.z + max.z <= ModelPos.z + ModelMin.z)
	{
		Add.z = (ModelPos.z + ModelMin.z - max.z);
	}

	//側面(12時方向からの侵入)
	if (pos.z + min.z < ModelPos.z + ModelMax.z &&
		oldpos.z + min.z >= ModelPos.z + ModelMax.z)
	{
		Add.z = (ModelPos.z + ModelMax.z - min.z);
	}


	////下面
	//if (pos.y + max.y > ModelPos.y + ModelMin.y &&
	//	oldpos.y + max.y <= ModelPos.y + ModelMin.y)
	//{
	//	Add.y = (ModelPos.y + ModelMin.y) - (pos.y + max.y);
	//}

	//上面
	if (pos.y + min.y < ModelPos.y + ModelMax.y &&
		oldpos.y + min.y >= ModelPos.y + ModelMax.y)
	{
		Add.y = (ModelPos.y + ModelMax.y - min.y);
	}

	if (Add != D3DXVECTOR3(0.0f,0.0f,0.0f))
	{
		//D3DXVec3TransformCoord(&Add, &Add, &GetMatrixRot());
	}

	//押し出す値を返す
	return Add;


	//上面
	HittingTargetPosMax[0] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + max.z);
	HittingTargetPosMin[0] = D3DXVECTOR3(pos.x + min.x, pos.y + max.y, pos.z + min.z);
	HittingTargetOldPosMax[0] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + max.z);
	HittingTargetOldPosMin[0] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + max.y, oldpos.z + min.z);

	//底面
	HittingTargetPosMax[1] = D3DXVECTOR3(pos.x + max.x, pos.y + min.y, pos.z + max.z);
	HittingTargetPosMin[1] = D3DXVECTOR3(pos.x + min.x, pos.y + min.y, pos.z + min.z);
	HittingTargetOldPosMax[1] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + min.y, oldpos.z + max.z);
	HittingTargetOldPosMin[1] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + min.z);

	//側面(４面)
	HittingTargetPosMax[2] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + max.z);
	HittingTargetPosMin[2] = D3DXVECTOR3(pos.x + max.x, pos.y + min.y, pos.z + min.z);
	HittingTargetOldPosMax[2] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + max.z);
	HittingTargetOldPosMin[2] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + min.y, oldpos.z + min.z);

	HittingTargetPosMax[3] = D3DXVECTOR3(pos.x + min.x, pos.y + max.y, pos.z + min.z);
	HittingTargetPosMin[3] = D3DXVECTOR3(pos.x + min.x, pos.y + min.y, pos.z + max.z);
	HittingTargetOldPosMax[3] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + max.y, oldpos.z + min.z);
	HittingTargetOldPosMin[3] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + max.z);

	HittingTargetPosMax[4] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + max.z);
	HittingTargetPosMin[4] = D3DXVECTOR3(pos.x + min.x, pos.y + min.y, pos.z + max.z);
	HittingTargetOldPosMax[4] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + max.z);
	HittingTargetOldPosMin[4] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + max.z);

	HittingTargetPosMax[5] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + min.z);
	HittingTargetPosMin[5] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + min.z);
	HittingTargetOldPosMax[5] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + min.z);
	HittingTargetOldPosMin[5] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + min.z);

	for (int nCnt = 0; nCnt < SURFACE_MAX; nCnt++)
	{
		//変数宣言
		D3DXVECTOR3 Extrusion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//点と面の当たり判定
		Extrusion = ExtrusionCollision(TargetPos,HittingTargetPosMax[nCnt], HittingTargetPosMin[nCnt] ,HittingTargetOldPosMax[nCnt], HittingTargetOldPosMin[nCnt]);

		//押し出しが発生していたら
		if (Extrusion != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			//押し出す値を入れる
			Add = Extrusion;

			//For文を抜ける
			break;
		}
	}

	//押し出す値を返す
	return Add;
}

//*****************************************************************************
//	当たり判定(押し出し判定)
//*****************************************************************************
D3DXVECTOR3 CBallast::ExtrusionCollision(D3DXVECTOR3& rPos, D3DXVECTOR3& rPosMax, D3DXVECTOR3& rPosMin, D3DXVECTOR3& rOldPosMax, D3DXVECTOR3& rOldPosMin)
{
	//自分のPos、サイズの情報
	D3DXVECTOR3 ThisPos, ThisSizeMax, ThisSizeMin;

	//Pos
	ThisPos = GetParentPos();

	//SizeMax
	ThisSizeMax = GetVtxMax();

	//SizeMin
	ThisSizeMin = GetVtxMin();

	//自分のPosとサイズの加算
	D3DXVECTOR3 ThisTopPosMax, ThisTopPosMin;

	//各頂点の情報を入れる
	ThisTopPosMax = ThisPos + ThisSizeMax;
	ThisTopPosMin = ThisPos + ThisSizeMin;

	//押し出し値
	D3DXVECTOR3 Add = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (ThisTopPosMin.x < rPosMax.x &&
		ThisTopPosMin.x >= rOldPosMax.x)
	{

	}


	//押し出し値を返す
	return Add;
}

