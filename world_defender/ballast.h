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

	//���I�̈ʒu��Set�AGet
	void SetListNumber(int nNumber) { m_nListNumber = nNumber; }
	int GetListNumber() { return m_nListNumber; }

	//���I�̃v���C���[�Ƃ̈ʒu��Set�AGet�AAdd
	void SetPositionWithPlayer(D3DXVECTOR3 PositionWithPlayer) { m_PositionWithPlayer = PositionWithPlayer; }
	D3DXVECTOR3 GetPositionWithPlayer() { return m_PositionWithPlayer; }
	void AddPositionWithPlayer(D3DXVECTOR3 PositionWithPlayer) { m_PositionWithPlayer += PositionWithPlayer; }

	//���I�̃v���C���[�Ƃ̌�����Set�AGet
	void SetFacingWithPlayer(D3DXVECTOR3 FacingWithPlayer) { m_FacingWithPlayer = FacingWithPlayer; }
	D3DXVECTOR3 GetFacingWithPlayer() { return m_FacingWithPlayer; }

	//���I�̐e�ʒu�̈ړ��ʂ�Set�AGet
	void SetParentPosMove(D3DXVECTOR3 ParentPosMove) { m_ParentPosMove = ParentPosMove; }
	D3DXVECTOR3 GetParentPosMove() { return m_ParentPosMove; }

	//�g�p��Ԍn
	void SetUse(bool bUse) { m_bUse = bUse; }
	bool GetUse() { return m_bUse; }

	//���V��Ԍn
	void SetFloating(bool bFloating) { m_bFloating = bFloating; }
	bool GetFloating() { return m_bFloating; }

	//������Move
	void SetMoveRot(D3DXVECTOR3 MoveRot) { m_MoveRot = MoveRot; }

private:
	D3DXVECTOR3 m_PositionWithPlayer;
	D3DXVECTOR3 m_FacingWithPlayer;
	D3DXVECTOR3 m_ParentPosMove;
	D3DXVECTOR3 m_MoveRot;
	int m_nListNumber;
	bool m_bUse;
	bool m_bFloating;
	
};

#endif
