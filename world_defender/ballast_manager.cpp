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

const float CBallast_Manager::MAP_MAX = 10000.0f;
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
	pBallast->Set3DObject(Data.nPattn, Data.pos, Data.rot);

	//�@���ݒ�
	pBallast->SetNormal();

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
			if (CConvenience_Function::CircleCollision(pos,fRadius, pBallast->GetPos(), 0.0f))
			{
				return pBallast;
			}

		}
	}

	return nullptr;
}

