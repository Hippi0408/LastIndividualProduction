//=============================================================================
//
//　瓦礫の処理 [ballast.h]
// Author : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _BALLAST_H_			//このマクロ定義がされなかったら
#define _BALLAST_H_			//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "3dobject.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBallast : public C3DObject
{
private:
	
	
public:
	CBallast();
	~CBallast() override;

	HRESULT Init() override;//初期化
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理

	//瓦礫の位置のSet、Get
	void SetListNumber(int nNumber) { m_nListNumber = nNumber; }
	int GetListNumber() { return m_nListNumber; }

	//瓦礫のプレイヤーとの位置のSet、Get、Add
	void SetPositionWithPlayer(D3DXVECTOR3 PositionWithPlayer) { m_PositionWithPlayer = PositionWithPlayer; }
	D3DXVECTOR3 GetPositionWithPlayer() { return m_PositionWithPlayer; }
	void AddPositionWithPlayer(D3DXVECTOR3 PositionWithPlayer) { m_PositionWithPlayer += PositionWithPlayer; }

	//瓦礫のプレイヤーとの向きのSet、Get
	void SetFacingWithPlayer(D3DXVECTOR3 FacingWithPlayer) { m_FacingWithPlayer = FacingWithPlayer; }
	D3DXVECTOR3 GetFacingWithPlayer() { return m_FacingWithPlayer; }

	//瓦礫の親位置の移動量のSet、Get
	void SetParentPosMove(D3DXVECTOR3 ParentPosMove) { m_ParentPosMove = ParentPosMove; }
	D3DXVECTOR3 GetParentPosMove() { return m_ParentPosMove; }

	//使用状態系
	void SetUse(bool bUse) { m_bUse = bUse; }
	bool GetUse() { return m_bUse; }

	//浮遊状態系
	void SetFloating(bool bFloating) { m_bFloating = bFloating; }
	bool GetFloating() { return m_bFloating; }

	//向きのMove
	void SetMoveRot(D3DXVECTOR3 MoveRot) { m_MoveRot = MoveRot; }

private:
	D3DXVECTOR3 m_PositionWithPlayer;
	D3DXVECTOR3 m_FacingWithPlayer;
	D3DXVECTOR3 m_ParentPosMove;
	D3DXVECTOR3 m_MoveRot;
	int m_nListNumber;
	bool m_bUse;
	bool m_bFloating;
	
};

#endif
