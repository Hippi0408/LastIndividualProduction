//=============================================================================
//
// enemyu.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_H_			//���̃}�N����`������Ȃ�������
#define _ENEMY_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "movable_obj.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy : public CMovable_Obj
{
private:
	static const int INIT_LIFE = 1;
	static const D3DXVECTOR3 INIT_POS;
	static const float MOVE_INERTIA;
public:
	CEnemy();
	~CEnemy() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//������Get
	float GetMoveInertia() override { return MOVE_INERTIA; }

private:

};

#endif