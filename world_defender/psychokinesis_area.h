//=============================================================================
//
//　サイコキネシスエリア処理 [psychokinesis_area.h]
// Author : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _PSYCHOKINESIS_AREA_H_			//このマクロ定義がされなかったら
#define _PSYCHOKINESIS_AREA_H_			//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CLocus;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPsychokinesis_Area : public CObject
{
private:
	static const D3DXVECTOR3 INIT_POS;
	static const float HEIGHT_LOCUS; 
	static const float RADIUS_INIT;
	static const float RADIUS_MOVE;
public:
	CPsychokinesis_Area();
	~CPsychokinesis_Area() override;

	HRESULT Init() override;//初期化
	HRESULT Init(D3DXVECTOR3 Pos) ;//初期化(Posあり)
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Update(D3DXVECTOR3 Pos);//Pos更新処理
	void Draw() override;//描画処理
	
private:
	D3DXVECTOR3 m_PLPos;
	D3DXVECTOR3 m_Rot;
	D3DXVECTOR3 m_RotMove;
	D3DXVECTOR3 m_LocusPos;
	CLocus* m_pLocus;
	float m_fRadius;
};

#endif
