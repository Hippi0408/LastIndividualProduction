//=============================================================================
//
// convenience_function.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "convenience_function.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CConvenience_Function::CConvenience_Function()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CConvenience_Function::~CConvenience_Function()
{
}

//*****************************************************************************
// Rotの正規化
//*****************************************************************************
D3DXVECTOR3 CConvenience_Function::NormalizationRot(D3DXVECTOR3 In)
{
	D3DXVECTOR3 rot = In;

	if (rot.x > D3DX_PI)
	{
		rot.x -= D3DX_PI * 2.0f;
	}
	else if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2.0f;
	}

	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}

	if (rot.z > D3DX_PI)
	{
		rot.z -= D3DX_PI * 2.0f;
	}
	else if (rot.z < -D3DX_PI)
	{
		rot.z += D3DX_PI * 2.0f;
	}

	return rot;
}

//*****************************************************************************
// 円同士の当たり判定
//*****************************************************************************
bool CConvenience_Function::CircleCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//位置の保存
	D3DXVECTOR3 Pos1 = pos1;
	D3DXVECTOR3 Pos2 = pos2;

	//２この物体の半径同士の和
	float fDiff = fRadius1 + fRadius2;

	//計算用変数
	float fCalculationX, fCalculationZ;

	//Xの差分
	fCalculationX = Pos1.x - Pos2.x;
	//Yの差分
	fCalculationZ = Pos1.z - Pos2.z;

	//現在の２点の距離
	float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationZ * fCalculationZ);

	//２この物体の半径同士の和より現在の２点の距離が小さいかどうか
	if (fDiff >= fLength)
	{
		//当たった
		return true;
	}

	//当たってない
	return false;
}

//*****************************************************************************
// 球同士の当たり判定
//*****************************************************************************
bool CConvenience_Function::SphereCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//位置の保存
	D3DXVECTOR3 Pos1 = pos1;
	D3DXVECTOR3 Pos2 = pos2;

	//２この物体の半径同士の和
	float fDiff = fRadius1 + fRadius2;

	//計算用変数
	D3DXVECTOR3 Distance;

	//2点との距離
	Distance = Pos1 - Pos2;

	//現在の２点の距離
	float fLength = sqrtf(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);

	//２この物体の半径同士の和より現在の２点の距離が小さいかどうか
	if (fDiff >= fLength)
	{
		//当たった
		return true;
	}

	//当たってない
	return false;
}
