//=============================================================================
//
// ���I���� [ballast.cpp]
// Author : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "ballast.h"


//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CBallast::CBallast()
{
	m_nListNumber = 0;
	m_MoveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bFloating = false;
	m_ParentPosMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CBallast::~CBallast()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CBallast::Init()
{
	//�g�p����
	m_bUse = true;

	//������
	if (FAILED(C3DObject::Init()))
	{
		return -1;
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CBallast::Uninit()
{
	//�e�N���X�̏I������
	C3DObject::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CBallast::Update()
{
	//�e���̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetPosMove();
	D3DXVECTOR3 rot = GetRot();

	//�q�̈ʒu�̍X�V
	pos += move;
	SetPos(pos);

	//�����̍X�V
	rot += m_MoveRot;
	SetRot(rot);

	//�e�ʒu�̍X�V
	AddParentPos(m_ParentPosMove);

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CBallast::Draw()
{
	//�}�g���b�N�X�̌v�Z
	CalculationMatrix();
	//�e�N���X�̕`�揈��
	C3DObject::Draw();
}

//*****************************************************************************
//	�����蔻��(�܂Ƃ�)
//*****************************************************************************
D3DXVECTOR3 CBallast::ConclusionCollision(D3DXVECTOR3 pos, D3DXVECTOR3 oldpos, D3DXVECTOR3 max, D3DXVECTOR3 min)
{
	//�ŏI�I�ȉ����o���l
	D3DXVECTOR3 Add = pos;

	//�Ώۂ�Pos
	D3DXVECTOR3 TargetPos = pos;
	
	//�ڐG�m�F�p�ϐ�
	D3DXVECTOR3 HittingTargetPosMax[SURFACE_MAX], HittingTargetPosMin[SURFACE_MAX], HittingTargetOldPosMax[SURFACE_MAX], HittingTargetOldPosMin[SURFACE_MAX];

	//���f���̈ʒu
	D3DXVECTOR3 ModelPos = GetPos();
	D3DXVECTOR3 ModelMax = GetVtxMax();
	D3DXVECTOR3 ModelMin = GetVtxMin();

	if (!(pos.x + max.x >= ModelPos.x + ModelMin.x &&
		pos.x + min.x <= ModelPos.x + ModelMax.x &&
		pos.z + max.z >= ModelPos.z + ModelMin.z &&
		pos.z + min.z <= ModelPos.z + ModelMax.z &&
		pos.y + min.y <= ModelPos.y + ModelMax.y))
	{
		//�����o���l��Ԃ�
		return Add;
	}



	
	//����(9����������̐N��)
	if (pos.x + max.x > ModelPos.x + ModelMin.x &&
		oldpos.x + max.x <= ModelPos.x + ModelMin.x)
	{
		Add.x = (ModelPos.x + ModelMin.x - max.x);
	}

	//����(3����������̐N��)
	if (pos.x + min.x < ModelPos.x + ModelMax.x &&
		oldpos.x + min.x >= ModelPos.x + ModelMax.x)
	{
		Add.x = (ModelPos.x + ModelMax.x - min.x);
	}

	//����(6����������̐N��)
	if (pos.z + max.z > ModelPos.z + ModelMin.z &&
		oldpos.z + max.z <= ModelPos.z + ModelMin.z)
	{
		Add.z = (ModelPos.z + ModelMin.z - max.z);
	}

	//����(12����������̐N��)
	if (pos.z + min.z < ModelPos.z + ModelMax.z &&
		oldpos.z + min.z >= ModelPos.z + ModelMax.z)
	{
		Add.z = (ModelPos.z + ModelMax.z - min.z);
	}


	////����
	//if (pos.y + max.y > ModelPos.y + ModelMin.y &&
	//	oldpos.y + max.y <= ModelPos.y + ModelMin.y)
	//{
	//	Add.y = (ModelPos.y + ModelMin.y) - (pos.y + max.y);
	//}

	//���
	if (pos.y + min.y < ModelPos.y + ModelMax.y &&
		oldpos.y + min.y >= ModelPos.y + ModelMax.y)
	{
		Add.y = (ModelPos.y + ModelMax.y - min.y);
	}

	if (Add != D3DXVECTOR3(0.0f,0.0f,0.0f))
	{
		//D3DXVec3TransformCoord(&Add, &Add, &GetMatrixRot());
	}

	//�����o���l��Ԃ�
	return Add;


	//���
	HittingTargetPosMax[0] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + max.z);
	HittingTargetPosMin[0] = D3DXVECTOR3(pos.x + min.x, pos.y + max.y, pos.z + min.z);
	HittingTargetOldPosMax[0] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + max.z);
	HittingTargetOldPosMin[0] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + max.y, oldpos.z + min.z);

	//���
	HittingTargetPosMax[1] = D3DXVECTOR3(pos.x + max.x, pos.y + min.y, pos.z + max.z);
	HittingTargetPosMin[1] = D3DXVECTOR3(pos.x + min.x, pos.y + min.y, pos.z + min.z);
	HittingTargetOldPosMax[1] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + min.y, oldpos.z + max.z);
	HittingTargetOldPosMin[1] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + min.z);

	//����(�S��)
	HittingTargetPosMax[2] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + max.z);
	HittingTargetPosMin[2] = D3DXVECTOR3(pos.x + max.x, pos.y + min.y, pos.z + min.z);
	HittingTargetOldPosMax[2] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + max.z);
	HittingTargetOldPosMin[2] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + min.y, oldpos.z + min.z);

	HittingTargetPosMax[3] = D3DXVECTOR3(pos.x + min.x, pos.y + max.y, pos.z + min.z);
	HittingTargetPosMin[3] = D3DXVECTOR3(pos.x + min.x, pos.y + min.y, pos.z + max.z);
	HittingTargetOldPosMax[3] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + max.y, oldpos.z + min.z);
	HittingTargetOldPosMin[3] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + max.z);

	HittingTargetPosMax[4] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + max.z);
	HittingTargetPosMin[4] = D3DXVECTOR3(pos.x + min.x, pos.y + min.y, pos.z + max.z);
	HittingTargetOldPosMax[4] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + max.z);
	HittingTargetOldPosMin[4] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + max.z);

	HittingTargetPosMax[5] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + min.z);
	HittingTargetPosMin[5] = D3DXVECTOR3(pos.x + max.x, pos.y + max.y, pos.z + min.z);
	HittingTargetOldPosMax[5] = D3DXVECTOR3(oldpos.x + max.x, oldpos.y + max.y, oldpos.z + min.z);
	HittingTargetOldPosMin[5] = D3DXVECTOR3(oldpos.x + min.x, oldpos.y + min.y, oldpos.z + min.z);

	for (int nCnt = 0; nCnt < SURFACE_MAX; nCnt++)
	{
		//�ϐ��錾
		D3DXVECTOR3 Extrusion = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�_�Ɩʂ̓����蔻��
		Extrusion = ExtrusionCollision(TargetPos,HittingTargetPosMax[nCnt], HittingTargetPosMin[nCnt] ,HittingTargetOldPosMax[nCnt], HittingTargetOldPosMin[nCnt]);

		//�����o�����������Ă�����
		if (Extrusion != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			//�����o���l������
			Add = Extrusion;

			//For���𔲂���
			break;
		}
	}

	//�����o���l��Ԃ�
	return Add;
}

//*****************************************************************************
//	�����蔻��(�����o������)
//*****************************************************************************
D3DXVECTOR3 CBallast::ExtrusionCollision(D3DXVECTOR3& rPos, D3DXVECTOR3& rPosMax, D3DXVECTOR3& rPosMin, D3DXVECTOR3& rOldPosMax, D3DXVECTOR3& rOldPosMin)
{
	//������Pos�A�T�C�Y�̏��
	D3DXVECTOR3 ThisPos, ThisSizeMax, ThisSizeMin;

	//Pos
	ThisPos = GetParentPos();

	//SizeMax
	ThisSizeMax = GetVtxMax();

	//SizeMin
	ThisSizeMin = GetVtxMin();

	//������Pos�ƃT�C�Y�̉��Z
	D3DXVECTOR3 ThisTopPosMax, ThisTopPosMin;

	//�e���_�̏�������
	ThisTopPosMax = ThisPos + ThisSizeMax;
	ThisTopPosMin = ThisPos + ThisSizeMin;

	//�����o���l
	D3DXVECTOR3 Add = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (ThisTopPosMin.x < rPosMax.x &&
		ThisTopPosMin.x >= rOldPosMax.x)
	{

	}


	//�����o���l��Ԃ�
	return Add;
}

