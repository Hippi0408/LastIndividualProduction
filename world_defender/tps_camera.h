//=============================================================================
//
// tps_camera.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _TPS_CAMERA_H_			//このマクロ定義がされなかったら
#define _TPS_CAMERA_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "camera.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTpsCamera : public CCamera
{
private:
	static const D3DXVECTOR3 RANGE_WITH_PLAYER_V;
	static const D3DXVECTOR3 RANGE_WITH_PLAYER_R;
	static const float DISTANCE;
public:
	CTpsCamera();
	~CTpsCamera() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	
private:
	D3DXVECTOR3 m_VPos;
	D3DXVECTOR3 m_Rot;
	D3DXVECTOR3 m_CameraVec;
	float m_fPlayerDistance;
	D3DXVECTOR3 m_DestPos;
};

#endif