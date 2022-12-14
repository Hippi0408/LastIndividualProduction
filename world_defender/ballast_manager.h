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

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBallast;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBallast_Manager : public CObject
{
private:
	
public:
	CBallast_Manager();
	~CBallast_Manager() override;

	HRESULT Init() override;//������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��

	void SetPlListNumber(int nNumber) { m_nPlListNumber = nNumber; }
	int GetPlListNumber() { return m_nPlListNumber; }

private:
	std::map<int, std::list<CBallast*>> m_BallastMapData;		//�}�b�v��̃I�u�W�F�N�g�����X�g�ŊǗ�����ϐ�
	int m_nPlListNumber;
};

#endif
