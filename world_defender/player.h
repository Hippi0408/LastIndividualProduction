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
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CShadow;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CObject
{
private:
	static const D3DXVECTOR3 INIT_POS;
public:
	CPlayer();
	~CPlayer() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLight(D3DXVECTOR3 vec) { m_Light = vec; }

private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Rot;
	D3DXVECTOR3 m_Move;
	D3DXVECTOR3 m_OldPos;
	int m_nMotionNum;
	D3DXVECTOR3 m_Light;
};

#endif