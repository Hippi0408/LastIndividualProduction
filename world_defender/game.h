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
class CBillcoard;

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

	CCamera* GetCamera() { return m_pCamera; }
	CMeshfield* GetMeshfield() { return m_pMeshfieldBG; }

private:
	CCamera* m_pCamera;
	CLight* m_pLight;
	CMeshfield* m_pMeshfieldBG;
	CPlayer* m_pPlayer;
	CBillcoard* m_pBillcoard;
};

#endif