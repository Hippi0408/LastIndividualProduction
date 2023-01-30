//=============================================================================
//
// enemyu_boss.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS_H_			//このマクロ定義がされなかったら
#define _ENEMY_BOSS_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy_Boss : public CEnemy
{
private:
	static const int INIT_LIFE = 1;
	static const D3DXVECTOR3 INIT_POS;
	static const float MOVE_INERTIA;
	static const float JUMP_INERTIA;
	static const float INIT_RADIUS;
public:
	CEnemy_Boss();
	~CEnemy_Boss() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	bool IsUnused() override;
	void SetMotionModel() override;

	//慣性のGet
	float GetMoveInertia() override { return MOVE_INERTIA; }

	//ジャンプ慣性のGet
	float GetJumpMoveInertia() override { return JUMP_INERTIA; }

private:
	
};

#endif