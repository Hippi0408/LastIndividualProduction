//=============================================================================
//
// enemy_manager.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "enemy.h"
#include "enemy_manager.h"
#include <assert.h>

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CEnemy_Manager::CEnemy_Manager()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CEnemy_Manager::~CEnemy_Manager()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CEnemy_Manager::Init()
{
	
	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CEnemy_Manager::Uninit()
{
	//�C�e���[�^�[���[�v
	for (auto itr = m_EnemyList.begin(); itr != m_EnemyList.end();)
	{
		//�C�e���[�^�[����G�l�~�[�̃|�C���^�̑��
		CEnemy* pEnemy = *itr;

		//�G�l�~�[�|�C���^�̉��
		if (pEnemy != nullptr)
		{
			//�I������
			pEnemy->Uninit();
			delete pEnemy;
			pEnemy = nullptr;
		}

		//���̃C�e���[�^�[�̑���A���݂̃C�e���[�^�[��j��
		itr = m_EnemyList.erase(itr);
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CEnemy_Manager::Update()
{
	//�C�e���[�^�[���[�v
	for (auto itr = m_EnemyList.begin(); itr != m_EnemyList.end();)
	{
		//�C�e���[�^�[����G�l�~�[�̃|�C���^�̑��
		CEnemy* pEnemy = *itr;

		//�G�l�~�[�|�C���^�̉��
		if (pEnemy == nullptr)
		{
			//���̃C�e���[�^�[�̑���A���݂̃C�e���[�^�[��j��
			itr = m_EnemyList.erase(itr);

			//�ȉ��̏����𖳎�����
			continue;
		}

		//�G�l�~�[�̍X�V����
		pEnemy->Update();

		//�I����������
		if (pEnemy->IsUnused())
		{
			//�I������
			pEnemy->Uninit();
			delete pEnemy;
			pEnemy = nullptr;

			//���̃C�e���[�^�[�̑���A���݂̃C�e���[�^�[��j��
			itr = m_EnemyList.erase(itr);

			//�ȉ��̏����𖳎�����
			continue;
		}

		//�C�e���[�^�[��i�߂�
		itr++;
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CEnemy_Manager::Draw()
{
}

//*****************************************************************************
// �N���G�C�g����
//*****************************************************************************
void CEnemy_Manager::CreateEnemy(EnemyInitData enemyinitdata)
{
	//�G�l�~�[�N���X�̃|�C���^�ϐ�
	CEnemy* pEnemy = nullptr;

	//�G�l�~�[�N���X�̐���
	switch (enemyinitdata.type)
	{
	case ENEMY_00:
		pEnemy = new CEnemy;
		break;
	default:
		assert(false);
		break;
	}
	
	//������
	if (FAILED(pEnemy->Init()))
	{
		assert(false);
	}

	//�G�l�~�[�̈ʒu
	pEnemy->SetPos(enemyinitdata.pos);

	//�G�l�~�[�̌���
	pEnemy->SetRot(enemyinitdata.rot);

	//�G�l�~�[�ړ���
	pEnemy->SetMovingDistance(enemyinitdata.fmove);

	//���X�g�ɃG�l�~�[����ǉ�
	m_EnemyList.push_back(pEnemy);
}
