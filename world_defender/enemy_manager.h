//=============================================================================
//
// enemyu_manager.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_			//���̃}�N����`������Ȃ�������
#define _ENEMY_MANAGER_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include <list>

//*****************************************************************************
// �񋓌^�錾
//*****************************************************************************
enum ENEMY_TYPE
{
	ENEMY_00 = 0,
	ENEMY_01,
	ENEMY_02,
	ENEMY_03,
	ENEMY_04,
	ENEMY_MAX
};


//*****************************************************************************
// �\���̐錾
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 rot;									//����
	float fmove;										//�ړ���
	ENEMY_TYPE type;									//�G�l�~�[�̎��
}EnemyInitData;

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEnemy;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemy_Manager : public CObject
{
private:
	static const int DAMAGE_TYPE_MAX = 5;
	static const float RADIUS_TYPE[DAMAGE_TYPE_MAX];
	static const int DAMAGE_TYPE[DAMAGE_TYPE_MAX];
public:
	CEnemy_Manager();
	~CEnemy_Manager() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void CreateEnemy(EnemyInitData enemyinitdata);

	bool EnemyCollision(D3DXVECTOR3 pos, float fRadius);
	void EnemyOnEnemyCollision(CEnemy* pTargetEnemy);
private:

	//�G�l�~�[�̃��X�g
	std::list<CEnemy*> m_EnemyList;

	int m_nEnemySmasllfish;
};

#endif