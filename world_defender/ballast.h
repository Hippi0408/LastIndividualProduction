//=============================================================================
//
//�@���I�̏��� [ballast.h]
// Author : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _BALLAST_H_			//���̃}�N����`������Ȃ�������
#define _BALLAST_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "3dobject.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBallast : public C3DObject
{
private:

public:
	CBallast();
	~CBallast() override;

	HRESULT Init() override;//������
	void Uninit() override;//�I������
	void Update() override;//�X�V����
	void Draw() override;//�`�揈��

	void SetListNumber(int nNumber) { m_nListNumber = nNumber; }
	int GetListNumber() { return m_nListNumber; }

private:
	int m_nListNumber;
};

#endif