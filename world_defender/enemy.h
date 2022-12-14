//=============================================================================
//
// enemyu.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_H_			//このマクロ定義がされなかったら
#define _ENEMY_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "movable_obj.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy : public CMovable_Obj
{
private:
	static const int INIT_LIFE = 1;
	static const D3DXVECTOR3 INIT_POS;
	static const float MOVE_INERTIA;
public:
	CEnemy();
	virtual ~CEnemy() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual bool IsUnused();
	virtual void SetMotionModel();

	void SetMovingDistance(float fMovingDistance) { m_fMovingDistance = fMovingDistance; }

	//慣性のGet
	float GetMoveInertia() override { return MOVE_INERTIA; }

private:
	float m_fMovingDistance;
};

#endif