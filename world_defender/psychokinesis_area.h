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
class CMesh_Cylinder;

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
	static const float SIZE_TOP;
public:
	CPsychokinesis_Area();
	~CPsychokinesis_Area() override;

	HRESULT Init() override;//初期化
	HRESULT Init(D3DXVECTOR3 Pos) ;//初期化(Posあり)
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Update(D3DXVECTOR3 Pos);//Pos更新処理
	void Draw() override;//描画処理

	float GetRadius() { return m_fRadius; }
	float GetSizeTop() { return m_fSizeTop; }
	
private:
	D3DXVECTOR3 m_PLPos;
	CMesh_Cylinder* m_pMesh_Cylinder;
	float m_fRadius;
	float m_fSizeTop;
};

#endif
