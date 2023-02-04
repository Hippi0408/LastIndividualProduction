//=============================================================================
//
// ���I�̊Ǘ��ҏ��� [ballast_manager.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "ballast_manager.h"
#include "ballast.h"
#include <assert.h>
#include "game.h"
#include "manager.h"
#include "meshfield.h"
#include "convenience_function.h"
#include "enemy_manager.h"
#include "read.h"
#include "ballast_acquired.h"
#include "sound.h"

const float CBallast_Manager::MAP_MAX = 15000.0f;
const D3DXVECTOR3 CBallast_Manager::INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBallast_Manager::CBallast_Manager()
{
	m_nPlListNumber = 0;
	m_nMeshfieldNumMax = 0;
	m_pMeshfieldCopy = nullptr;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBallast_Manager::~CBallast_Manager()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CBallast_Manager::Init()
{
	m_nPlListNumber = 0;
	m_nMeshfieldNumMax = 0;
	m_pMeshfieldCopy = nullptr;

	CRead Read;
	m_nBallast_Acquired_Model = Read.ReadXFile("data/MODEL/��.x");

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CBallast_Manager::Uninit()
{
	//���X�g�̉��
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//�C�e���[�^�[���[�v
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end();)
		{
			//�C�e���[�^�[���犢�I�̃|�C���^�̑��
			CBallast* pBallast = *itr;
			
			//���I�|�C���^�̉��
			if (pBallast != nullptr)
			{
				//�I������
				pBallast->Uninit();
				delete pBallast;
				pBallast = nullptr;
			}

			//���̃C�e���[�^�[�̑���A���݂̃C�e���[�^�[��j��
			itr = m_BallastMapData[nCnt].erase(itr);
		}
	}
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBallast_Manager::Update()
{
	//�G�l�~�[�Ƃ̓����蔻��
	CollisionEnemy();

	//���X�g�̍X�V
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//�C�e���[�^�[���[�v
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end(); )
		{
			//�C�e���[�^�[���犢�I�̃|�C���^�̑��
			CBallast* pBallast = *itr;

			//���I�|�C���^�̍X�V����
			if (pBallast == nullptr)
			{
				assert(false);
			}

			//�g�p��Ԃ��ǂ���
			if (pBallast->GetUse())
			{
				D3DXVECTOR3 pos = pBallast->GetWorldPos();
				//�G���A�O�ɂ��邩�ǂ���
				if (CConvenience_Function::CircleCollision(D3DXVECTOR3(0.0f,0.0f,0.0f), MAP_MAX, pos, 0.0f))
				{
					//�X�V����
					pBallast->Update();

					//�C�e���[�^�[��i�߂�
					itr++;

					continue;
				}
			}
			
			
			//�I������
			pBallast->Uninit();

			//�j��
			delete pBallast;
			pBallast = nullptr;

			//���̃C�e���[�^�[�̑���A���݂̃C�e���[�^�[��j��
			itr = m_BallastMapData[nCnt].erase(itr);
		}
	}
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CBallast_Manager::Draw()
{
	//���X�g�̍X�V
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//�C�e���[�^�[���[�v
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end(); itr++)
		{
			//�C�e���[�^�[���犢�I�̃|�C���^�̑��
			CBallast* pBallast = *itr;

			//���I�̕`��
			if (pBallast != nullptr)
			{
				//�`�揈��
				pBallast->Draw();
			}
		}
	}
}

//*****************************************************************************
//���I�̐ݒ�
//*****************************************************************************
void CBallast_Manager::SetBallast(int nNumber, Object_Data Data)
{
	//���I�N���X�̐���
	CBallast* pBallast = new CBallast;

	//������
	if (FAILED(pBallast->Init()))
	{
		assert(false);
	}

	//���b�V�����̈ʒu�i�ԍ��j
	pBallast->SetListNumber(nNumber);

	//�g�p���郂�f���ԍ��A���I�̈ʒu�A���I�̌���
	pBallast->Set3DObject(Data.nPattn, D3DXVECTOR3(0.0f,0.0f,0.0f), Data.rot);
	pBallast->SetParentPos(Data.pos);

	//�@���ݒ�
	pBallast->SetNormal();

	//���a�ݒ�
	pBallast->SetRadius();

	//���X�g�Ɋ��I����ǉ�
	m_BallastMapData[nNumber].push_back(pBallast);
}

//*****************************************************************************
//���b�V���t�B�[���h�̐ݒ�
//*****************************************************************************
void CBallast_Manager::MeshfieldSet(CMeshfield* pMeshfield)
{
	//�ۑ����Null�`�F�b�N
	if (m_pMeshfieldCopy != nullptr)
	{
		assert(false);
	}

	//�Q�[������n�ʁi���b�V���j�̎擾
	m_pMeshfieldCopy = pMeshfield;

	//���b�V���̃}�X�̐��̍ő�̐ݒ�
	m_nMeshfieldNumMax = m_pMeshfieldCopy->GetMeshfieldNumMax();

}

//*****************************************************************************
//�T�C�R�L�l�V�X�G���A�ɂ������炻�̃I�u�W�F�N�g�̃|�C���^��Ԃ�
//*****************************************************************************
CBallast * CBallast_Manager::CheckCircleCollision(D3DXVECTOR3 pos, float fRadius)
{
	//���X�g�̍X�V
	for (int nCnt = 0; nCnt < m_nMeshfieldNumMax; nCnt++)
	{
		//�C�e���[�^�[���[�v
		for (auto itr = m_BallastMapData[nCnt].begin(); itr != m_BallastMapData[nCnt].end(); itr++)
		{
			//�C�e���[�^�[���犢�I�̃|�C���^�̑��
			CBallast* pBallast = *itr;

			//���INULL�`�F�b�N
			if (pBallast == nullptr)
			{
				assert(false);
			}

			//���V��Ԃ��ǂ���
			if (pBallast->GetFloating())
			{
				continue;
			}

			//�T�C�R�L�l�V�X�G���A�ɂ��邩�ǂ���pBallast->GetVtxMax().x
			if (CConvenience_Function::CircleCollision(pos,fRadius, pBallast->GetParentPos(), 0.0f))
			{
				return pBallast;
			}

		}
	}

	return nullptr;
}

//*****************************************************************************
//�T�C�R�L�l�V�X�G���A�ɂ������炻�̃I�u�W�F�N�g�̐F��ς���
//*****************************************************************************
void CBallast_Manager::WithinRangeColor(int nMapGrid, D3DXVECTOR3 pos, float fRadius)
{
	//�C�e���[�^�[���[�v
	for (auto itr = m_BallastMapData[nMapGrid].begin(); itr != m_BallastMapData[nMapGrid].end(); itr++)
	{
		//�ϐ��錾
		D3DXVECTOR3 Extrusion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�C�e���[�^�[���犢�I�̃|�C���^�̑��
		CBallast* pBallast = *itr;

		//���INULL�`�F�b�N
		if (pBallast == nullptr)
		{
			assert(false);
		}

		//���V��Ԃ��ǂ���
		if (pBallast->GetFloating())
		{
			pBallast->SetWithinRangeColor(false);
			continue;
		}

		//�T�C�R�L�l�V�X�G���A�ɂ��邩�ǂ���pBallast->GetVtxMax().x
		if (CConvenience_Function::CircleCollision(pos, fRadius, pBallast->GetParentPos(), 0.0f))
		{
			pBallast->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f), 0.05f);
			pBallast->SetWithinRangeColor(true);
		}
		else
		{
			pBallast->SetWithinRangeColor(false);
		}

	}
}

//*****************************************************************************
//��Q���̓����蔻��
//*****************************************************************************
D3DXVECTOR3 CBallast_Manager::CollisionBallast(int nMapGrid, D3DXVECTOR3 pos, D3DXVECTOR3 oldpos, D3DXVECTOR3 max, D3DXVECTOR3 min)
{
	D3DXVECTOR3 Add = pos;

	//�C�e���[�^�[���[�v
	for (auto itr = m_BallastMapData[nMapGrid].begin(); itr != m_BallastMapData[nMapGrid].end(); itr++)
	{
		//�ϐ��錾
		D3DXVECTOR3 Extrusion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�C�e���[�^�[���犢�I�̃|�C���^�̑��
		CBallast* pBallast = *itr;

		//���INULL�`�F�b�N
		if (pBallast == nullptr)
		{
			assert(false);
		}

		//���V��Ԃ��ǂ���
		if (pBallast->GetFloating())
		{
			continue;
		}

		//�����o������
		Extrusion = pBallast->ConclusionCollision(pos, oldpos, max, min);

		//�����o�������������ǂ���
		if (Extrusion != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			//�����o���ϐ��ɓ����
			Add = Extrusion;

			//for���𔲂���
			break;
		}

	}

	//�����o���l��Ԃ�
	return Add;
}

//*****************************************************************************
//�G�l�~�[�Ƃ̓����蔻��
//*****************************************************************************
void CBallast_Manager::CollisionEnemy()
{
	//�}�l�[�W���[����G�l�~�[�}�l�[�W���[�̎擾
	CManager *pManager = GetManager();
	CGame* pGame = (CGame*)pManager->GetGameObject();
	CEnemy_Manager* pEnemy_Manager = pGame->GetEnemy_Manager();

	//�C�e���[�^�[���[�v
	for (auto itr = m_FloatingBallstList.begin(); itr != m_FloatingBallstList.end();)
	{
		//�C�e���[�^�[���犢�I�̃|�C���^�̑��
		CBallast* pBallast = *itr;

		//���INULL�`�F�b�N
		if (pBallast == nullptr)
		{
			assert(false);
		}

		//���V��Ԃ��ǂ���
		if (!pBallast->GetFloating())
		{
			//�C�e���[�^�[��i�߂�
			itr++;

			//�����𖳎�����
			continue;
		}

		//����
		bool bHit = pEnemy_Manager->EnemyCollision(pBallast->GetWorldPos(), pBallast->GetRadius());

		if (!bHit)
		{
			//�C�e���[�^�[��i�߂�
			itr++;

			//�����𖳎�����
			continue;
		}

		//�T�E���h
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		
		D3DXVECTOR3 vec = pBallast->GetPosMove() * -1.0f;

		D3DXVec3Normalize(&vec, &vec);

		SetBallastAcquired(vec, pBallast->GetWorldPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		//���I�̎g�p��Ԃ�ύX
		pBallast->SetUse(false);

		//���̃C�e���[�^�[�̑���A���݂̃C�e���[�^�[��j��
		itr = m_FloatingBallstList.erase(itr);

	}

}

//*****************************************************************************
//���V��Ԃ̃��X�g�ǉ�
//*****************************************************************************
void CBallast_Manager::SetFloatingBallst(CBallast * pBallast)
{
	//���X�g�Ɋ��I����ǉ�
	m_FloatingBallstList.push_back(pBallast);
}

//*****************************************************************************
//��V�I���I�̐���(�����͔�΂����������x�N�g��,���Ƃ͊�{���)
//*****************************************************************************
void CBallast_Manager::SetBallastAcquired(D3DXVECTOR3 vec, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�}�b�v�`�b�v�̈ʒu
	int nNumber = 0;

	//������ԕ���
	D3DXVECTOR3 Vec = vec;

	//��V�I���I�N���X�̐���
	CBallast_Acquired* pBallastAcquired = new CBallast_Acquired;

	//������
	if (FAILED(pBallastAcquired->Init()))
	{
		assert(false);
	}
	
	//�}�b�v�`�b�v�̈ʒu�m�F
	nNumber = m_pMeshfieldCopy->CheckPosLocation(pos);

	//���b�V�����̈ʒu�i�ԍ��j
	pBallastAcquired->SetListNumber(nNumber);

	//�g�p���郂�f���ԍ��A���I�̈ʒu�A���I�̌���
	pBallastAcquired->Set3DObject(m_nBallast_Acquired_Model, D3DXVECTOR3(0.0f,0.0f,0.0f), rot);

	pBallastAcquired->SetParentPos(pos);

	//������ԕ���(�������܂߂�)
	Vec.x += (float)(rand() % 10 - 5);
	Vec.y += (float)(rand() % 10 - 5);
	Vec.z += (float)(rand() % 10 - 5);

	//�m�[�}���C�Y
	D3DXVec3Normalize(&Vec,&Vec);

	//������ԕ����̐ݒ�
	pBallastAcquired->SetVec(Vec);

	//�@���ݒ�
	pBallastAcquired->SetNormal();

	//���a�ݒ�
	pBallastAcquired->SetRadius();

	//���X�g�Ɋ��I����ǉ�
	m_BallastMapData[nNumber].push_back(pBallastAcquired);

}

//*****************************************************************************
//���X�g���̓���ւ�
//*****************************************************************************
void CBallast_Manager::ReplacementList(CBallast * pBallast, int nNext)
{
	//�Ō�ɓo�^����Ă����ԍ�
	int nLastNum = pBallast->GetListNumber();

	if (nNext == nLastNum)
	{
		return;
	}

	//�C�e���[�^�[���[�v
	for (auto itr = m_BallastMapData[nLastNum].begin(); itr != m_BallastMapData[nLastNum].end(); itr++)
	{
		//�C�e���[�^�[���犢�I�̃|�C���^�̑��
		CBallast* pballast = *itr;

		//���INULL�`�F�b�N
		if (pballast == nullptr)
		{
			assert(false);
		}

		//�w��̃|�C���^���ǂ���
		if (pBallast != pballast)
		{
			//�C�e���[�^�[��i�߂�
			itr++;

			//�����𖳎�����
			continue;
		}
	
		//���̃C�e���[�^�[�̑���A���݂̃C�e���[�^�[��j��
		itr = m_FloatingBallstList.erase(itr);
	}


	//���X�g�Ɋ��I����ǉ�
	m_BallastMapData[nNext].push_back(pBallast);
}

