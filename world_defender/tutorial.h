//=============================================================================
//
// tutorial.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TUTORIAL_H_			//���̃}�N����`������Ȃ�������
#define _TUTORIAL_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CCamera;
class CLight;
class C2DPolygon;
class CMeshfield;
class CPlayer;
class CBallast_Manager;
class CEnemy_Manager;
class CMesh_Cylinder;
class CUfo;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutorial : public CObject
{
private:

public:
	CTutorial();
	~CTutorial() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	CCamera* GetCamera() { return m_pCamera; }
	CMeshfield* GetMeshfield() { return m_pMeshfieldBG; }
	CPlayer* GetPlayer() { return m_pPlayer; }
	CBallast_Manager* GetBallast_Manager() { return m_pBallastManager; }
	CEnemy_Manager* GetEnemy_Manager() { return m_pEnmeyManager; }

	void GameEnd() { m_bGameEnd = true; }
private:
	CCamera* m_pCamera;
	CLight* m_pLight;
	CMeshfield* m_pMeshfieldBG;
	CPlayer* m_pPlayer;
	CEnemy_Manager* m_pEnmeyManager;
	CBallast_Manager* m_pBallastManager;
	CMesh_Cylinder* m_pMesh_Cylinder;
	CUfo* m_pUfo;
	C2DPolygon* m_pUi;
	D3DXVECTOR3 m_LightVec;
	bool m_bGameEnd;
};

#endif