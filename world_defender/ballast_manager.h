//=============================================================================
//
//　瓦礫の管理者処理 [ballast_manager.h]
// Author : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _BALLAST_MANAGER_H_			//このマクロ定義がされなかったら
#define _BALLAST_MANAGER_H_			//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "object.h"
#include <map>
#include <list>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBallast;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBallast_Manager : public CObject
{
private:
	
public:
	CBallast_Manager();
	~CBallast_Manager() override;

	HRESULT Init() override;//初期化
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理

	void SetPlListNumber(int nNumber) { m_nPlListNumber = nNumber; }
	int GetPlListNumber() { return m_nPlListNumber; }

private:
	std::map<int, std::list<CBallast*>> m_BallastMapData;		//マップ上のオブジェクトをリストで管理する変数
	int m_nPlListNumber;
};

#endif
