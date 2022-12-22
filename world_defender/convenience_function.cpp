//=============================================================================
//
// convenience_function.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// ƒCƒ“ƒNƒ‹[ƒh
//*****************************************************************************
#include "convenience_function.h"

//*****************************************************************************
// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//*****************************************************************************
CConvenience_Function::CConvenience_Function()
{

}

//*****************************************************************************
// ƒfƒXƒgƒ‰ƒNƒ^
//*****************************************************************************
CConvenience_Function::~CConvenience_Function()
{
}

//*****************************************************************************
// Rot‚Ì³‹K‰»
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
// ‰~“¯Žm‚Ì“–‚½‚è”»’è
//*****************************************************************************
bool CConvenience_Function::CircleCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//ˆÊ’u‚Ì•Û‘¶
	D3DXVECTOR3 Pos1 = pos1;
	D3DXVECTOR3 Pos2 = pos2;

	//‚Q‚±‚Ì•¨‘Ì‚Ì”¼Œa“¯Žm‚Ì˜a
	float fDiff = fRadius1 + fRadius2;

	//ŒvŽZ—p•Ï”
	float fCalculationX, fCalculationZ;

	//X‚Ì·•ª
	fCalculationX = Pos1.x - Pos2.x;
	//Y‚Ì·•ª
	fCalculationZ = Pos1.z - Pos2.z;

	//Œ»Ý‚Ì‚Q“_‚Ì‹——£
	float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationZ * fCalculationZ);

	//‚Q‚±‚Ì•¨‘Ì‚Ì”¼Œa“¯Žm‚Ì˜a‚æ‚èŒ»Ý‚Ì‚Q“_‚Ì‹——£‚ª¬‚³‚¢‚©‚Ç‚¤‚©
	if (fDiff >= fLength)
	{
		//“–‚½‚Á‚½
		return true;
	}

	//“–‚½‚Á‚Ä‚È‚¢
	return false;
}

//*****************************************************************************
// ‹…“¯Žm‚Ì“–‚½‚è”»’è
//*****************************************************************************
bool CConvenience_Function::SphereCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//ˆÊ’u‚Ì•Û‘¶
	D3DXVECTOR3 Pos1 = pos1;
	D3DXVECTOR3 Pos2 = pos2;

	//‚Q‚±‚Ì•¨‘Ì‚Ì”¼Œa“¯Žm‚Ì˜a
	float fDiff = fRadius1 + fRadius2;

	//ŒvŽZ—p•Ï”
	D3DXVECTOR3 Distance;

	//2“_‚Æ‚Ì‹——£
	Distance = Pos1 - Pos2;

	//Œ»Ý‚Ì‚Q“_‚Ì‹——£
	float fLength = sqrtf(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);

	//‚Q‚±‚Ì•¨‘Ì‚Ì”¼Œa“¯Žm‚Ì˜a‚æ‚èŒ»Ý‚Ì‚Q“_‚Ì‹——£‚ª¬‚³‚¢‚©‚Ç‚¤‚©
	if (fDiff >= fLength)
	{
		//“–‚½‚Á‚½
		return true;
	}

	//“–‚½‚Á‚Ä‚È‚¢
	return false;
}
