//=============================================================================
//
// camera.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _CAMERA_H_			//���̃}�N����`������Ȃ�������
#define _CAMERA_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCamera : public CObject
{
private:
	//�J�����\����
	typedef struct
	{
		D3DXVECTOR3 posV;		//���_
		D3DXVECTOR3 posVDest;		//���_
		D3DXVECTOR3 posR;		//�����_
		D3DXVECTOR3 posRDest;		//�����_
		D3DXVECTOR3 vecU;		//������x�N�g��
		D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;		  //�r���[�}�g���b�N�X
		float fDistance;			//���_�������_�̂܂ł̋���
	}Camera;

public:
	CCamera();
	~CCamera() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetCamera();

	void SetPosV(D3DXVECTOR3 posV) { m_Camera.posV = posV; }
	void AddPosV(D3DXVECTOR3 addV) { m_Camera.posV += addV; }
	void SetPosR(D3DXVECTOR3 posR) { m_Camera.posR = posR; }
	void AddPosR(D3DXVECTOR3 addR) { m_Camera.posR += addR; }
	void SetVecU(D3DXVECTOR3 vecU) { m_Camera.vecU = vecU; }
	float GetRot();

private:
	Camera m_Camera;
};

#endif