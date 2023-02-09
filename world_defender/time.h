//=============================================================================
//
// time.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TIME_H_			//���̃}�N����`������Ȃ�������
#define _TIME_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CStatGauge;
class C2DPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTime : public CObject
{
private:
	static const int INIT_TIME = 3600;
	static const D3DXVECTOR3 CRAYFISH_POS;
	static const D3DXVECTOR3 EARTH_POS;
public:
	CTime();
	~CTime() override;

	HRESULT Init() override;
	HRESULT Init(int nTimeMax);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	bool CheckTime(int nTime = 0);

	void SetTimeUpdate(bool bUpdate) { m_bUpdate = bUpdate; }
private:
	C2DPolygon* m_pCrayfish;
	C2DPolygon* m_pEarth;
	CStatGauge* m_pTimeGauge;
	bool m_bUpdate;
};

#endif