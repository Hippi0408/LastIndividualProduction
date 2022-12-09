//=============================================================================
//
// player.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _PLAYER_H_			//���̃}�N����`������Ȃ�������
#define _PLAYER_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "movable_obj.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CShadow;
class CLocus;

//*****************************************************************************
// �N���X��`
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

	//������Get
	float GetMoveInertia() override { return MOVE_INERTIA; }


private:
	int m_nMotionNum1;
	D3DXVECTOR3 m_RotLowerBody;
	D3DXVECTOR3 m_DestRotLowerBody;
	CLocus* m_pLocus;

};

#endif