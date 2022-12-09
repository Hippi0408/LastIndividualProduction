//=============================================================================
//
// player.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _PLAYER_H_			//このマクロ定義がされなかったら
#define _PLAYER_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "movable_obj.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CShadow;
class CLocus;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CMovable_Obj
{
private:
	static const int INIT_LIFE = 100;
	static const D3DXVECTOR3 INIT_POS;
	static const float MOVE_INERTIA;
public:
	CPlayer();
	~CPlayer() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	int GetMotionNum1() { return m_nMotionNum1; }

	//慣性のGet
	float GetMoveInertia() override { return MOVE_INERTIA; }


private:
	int m_nMotionNum1;
	D3DXVECTOR3 m_RotLowerBody;
	D3DXVECTOR3 m_DestRotLowerBody;
	CLocus* m_pLocus;

};

#endif