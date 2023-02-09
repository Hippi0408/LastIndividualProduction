//=============================================================================
//
// time.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TIME_H_			//このマクロ定義がされなかったら
#define _TIME_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CStatGauge;
class C2DPolygon;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTime : public CObject
{
private:
	static const int INIT_TIME = 3600;
	static const D3DXVECTOR3 CRAYFISH_POS;
	static const D3DXVECTOR3 EARTH_POS;
public:
	CTime();
	~CTime() override;

	HRESULT Init() override;
	HRESULT Init(int nTimeMax);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	bool CheckTime(int nTime = 0);

	void SetTimeUpdate(bool bUpdate) { m_bUpdate = bUpdate; }
private:
	C2DPolygon* m_pCrayfish;
	C2DPolygon* m_pEarth;
	CStatGauge* m_pTimeGauge;
	bool m_bUpdate;
};

#endif