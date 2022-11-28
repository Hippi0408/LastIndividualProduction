//=============================================================================
//
// movable_obj.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _MOVABLE_OBJ_H_			//このマクロ定義がされなかったら
#define _MOVABLE_OBJ_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMovable_Obj : public CObject
{
private:

public:
	CMovable_Obj();
	virtual ~CMovable_Obj() override;

	virtual HRESULT Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	D3DXVECTOR3 GetPos() {return m_Pos; }
	void AddPos(D3DXVECTOR3 addpos) { m_Pos += addpos; }
	void SetOldPos(D3DXVECTOR3 oldpos) { m_OldPos = oldpos; }
	D3DXVECTOR3 GetOldPos() { return m_OldPos; }
	void AddOldPos(D3DXVECTOR3 addpos) { m_OldPos += addpos; }
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }
	D3DXVECTOR3 GetRot() { return m_Rot; }
	void AddRot(D3DXVECTOR3 addrot) { m_Rot += addrot; }
	void SetOldRot(D3DXVECTOR3 oldrot) { m_OldRot = oldrot; }
	D3DXVECTOR3 GetOldRot() { return m_OldRot; }
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }
	D3DXVECTOR3 GetMove() { return m_Move; }

	void SetLight(D3DXVECTOR3 vec) { m_Light = vec; }

	int GetMotionNum() { return m_nMotionNum; }
	void SetMotionNum(int nMotionNum) { m_nMotionNum = nMotionNum; }

private:
	D3DXVECTOR3 m_Pos;			//位置
	D3DXVECTOR3 m_OldPos;		//前回の位置
	D3DXVECTOR3 m_Rot;			//向き
	D3DXVECTOR3 m_OldRot;		//前回の向き
	D3DXVECTOR3 m_Move;			//移動量

	int m_nMotionNum;			//使用するモーションモデル番号
	D3DXVECTOR3 m_Light;		//ライトの向き（必ず必要ではない）
};

#endif