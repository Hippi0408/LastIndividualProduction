//=============================================================================
//
// enemyu_boss.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_BOSS_H_			//���̃}�N����`������Ȃ�������
#define _ENEMY_BOSS_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy_Boss : public CEnemy
{
private:
	static const int INIT_LIFE = 1;
	static const D3DXVECTOR3 INIT_POS;
	static const float MOVE_INERTIA;
	static const float JUMP_INERTIA;
	static const float INIT_RADIUS;
public:
	CEnemy_Boss();
	~CEnemy_Boss() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	bool IsUnused() override;
	void SetMotionModel() override;

	//������Get
	float GetMoveInertia() override { return MOVE_INERTIA; }

	//�W�����v������Get
	float GetJumpMoveInertia() override { return JUMP_INERTIA; }

private:
	
};

#endif