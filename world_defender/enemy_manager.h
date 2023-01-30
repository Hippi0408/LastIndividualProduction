//=============================================================================
//
// enemyu_manager.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_			//このマクロ定義がされなかったら
#define _ENEMY_MANAGER_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"
#include <list>

//*****************************************************************************
// 列挙型宣言
//*****************************************************************************
enum ENEMY_TYPE
{
	ENEMY_00 = 0,
	ENEMY_01,
	ENEMY_02,
	ENEMY_03,
	ENEMY_04,
	ENEMY_MAX
};


//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 rot;									//向き
	float fmove;										//移動量
	ENEMY_TYPE type;									//エネミーの種類
}EnemyInitData;

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEnemy;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemy_Manager : public CObject
{
private:
	static const int DAMAGE_TYPE_MAX = 5;
	static const float RADIUS_TYPE[DAMAGE_TYPE_MAX];
	static const int DAMAGE_TYPE[DAMAGE_TYPE_MAX];
public:
	CEnemy_Manager();
	~CEnemy_Manager() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void CreateEnemy(EnemyInitData enemyinitdata);

	bool EnemyCollision(D3DXVECTOR3 pos,float fRadius);
private:

	//エネミーのリスト
	std::list<CEnemy*> m_EnemyList;
};

#endif