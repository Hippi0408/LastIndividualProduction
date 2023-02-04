//=============================================================================
//
// game.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _GAME_H_			//���̃}�N����`������Ȃ�������
#define _GAME_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CCamera;
class CLight;
class C3DPolygon;
class CMeshfield;
class CPlayer;
class CBallast_Manager;
class CEnemy_Manager;
class CMesh_Cylinder;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame : public CObject
{
private:
	
public:
	CGame();
	~CGame() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void CreateBallastManager(CMeshfield* pMeshfield);

	CCamera* GetCamera() { return m_pCamera; }
	CCamera* GetCameraRound() { return m_pCameraRound; }
	CMeshfield* GetMeshfield() { return m_pMeshfieldBG; }
	CPlayer* GetPlayer() { return m_pPlayer; }
	CBallast_Manager* GetBallast_Manager() { return m_pBallastManager; }
	CEnemy_Manager* GetEnemy_Manager() { return m_pEnmeyManager; }

	void SetRoundCamera(int nRoundCntMax);
	void SetRoundCameraPosR(D3DXVECTOR3 posV);

	void SetVibration(int nVibrationMax, int nVibration);
	bool CheckVibration();
private:
	CCamera* m_pCameraRound;
	CCamera* m_pCamera;
	CLight* m_pLight;
	CMeshfield* m_pMeshfieldBG;
	CPlayer* m_pPlayer;
	CEnemy_Manager* m_pEnmeyManager;
	CBallast_Manager* m_pBallastManager;
	CMesh_Cylinder* m_pMesh_Cylinder;
	int m_nRoundCnt;
	int m_nRoundCntMax;
	bool m_bRoundCamera;
};

#endif