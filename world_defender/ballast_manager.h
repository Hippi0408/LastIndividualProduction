//=============================================================================
//
//�@���I�̊Ǘ��ҏ��� [ballast_manager.h]
// Author : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _BALLAST_MANAGER_H_			//���̃}�N����`������Ȃ�������
#define _BALLAST_MANAGER_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "object.h"
#include <map>
#include <list>
#include "3dobject.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBallast;
class CMeshfield;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBallast_Manager : public CObject
{
private:
	static const float MAP_MAX;
public:
	CBallast_Manager();
	~CBallast_Manager() override;

	HRESULT Init() override;//������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��

	//�v���C���[�̈ʒu��Set�AGet
	void SetPlListNumber(int nNumber) { m_nPlListNumber = nNumber; }
	int GetPlListNumber() { return m_nPlListNumber; }

	//���I�̐ݒ�
	void SetBallast(int nNumber, Object_Data Data);

	//���b�V���t�B�[���h�̐ݒ�
	void MeshfieldSet(CMeshfield* pMeshfield);

	//�T�C�R�L�l�V�X�G���A�ɂ������炻�̃I�u�W�F�N�g�̃|�C���^��Ԃ�
	CBallast* CheckCircleCollision(D3DXVECTOR3 pos, float fRadius);

private:
	std::map<int, std::list<CBallast*>> m_BallastMapData;		//�}�b�v��̃I�u�W�F�N�g�����X�g�ŊǗ�����ϐ�
	int m_nPlListNumber;
	CMeshfield *m_pMeshfieldCopy;								//���b�V���t�B�[���h�|�C���^�̃R�s�[�i���̃R�s�[�͉�������Ȃ��j
	int m_nMeshfieldNumMax;										//���b�V���̃}�X�̐��̍ő�

};

#endif
