//=============================================================================
//
// όΝ [directmouse.h]
// Author1 : ϊ±l
// Author2 : KOZUNA HIROHITO
// Tv : }EXΆ¬πs€
//
//=============================================================================

//***************************************************************************
// CN[h
//***************************************************************************
#include <assert.h>
#include <stdio.h>

#include "inputmouse.h"

//=============================================================================
// RXgN^
// Author : ϊ±l
// Tv : CX^XΆ¬Ιs€
//=============================================================================
CInputMouse::CInputMouse()
{
	memset(&m_aKeyState, 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(&m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}

//=============================================================================
// fXgN^
// Author : ϊ±l
// Tv : CX^XIΉΙs€
//=============================================================================
CInputMouse::~CInputMouse()
{

}

//=============================================================================
// ϊ»
// Author1 : ϊ±l
// Author2 : KOZUNA HIROHITO
// Tv : }EXΜANZX πlΎΕ«½κAπp±·ι
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{

	// όΝfoCXi}EXjΜΆ¬
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//f[^tH[}bgπέθ
	if (FAILED(m_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// ¦²[hπέθ
	if (FAILED(m_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// EBhEnhΜi[
	m_hWnd = hWnd;

	// DeviceΦΜANZX πlΎ
	m_pDevMouse->Acquire();

	return S_OK;
}

//=============================================================================
// IΉ
// Author : KOZUNA HIROHITO
// Tv : }EXΜANZX ππϊ΅AfoCXππϊ·ι
//=============================================================================
void CInputMouse::Uninit(void)
{
	//όΝfoCXiL[{[hjΜϊό
	if (m_pDevMouse != nullptr)
	{
		m_pDevMouse->Unacquire();		//L[{[hΦΜANZX πϊό
		m_pDevMouse->Release();
		m_pDevMouse = nullptr;
	}
}

//=============================================================================
// XV
// Author1 : ϊ±l
// Author2 : KOZUNA HIROHITO
// Tv : }EXόΝ³κ½ξρπΫΆ·ι
//=============================================================================
void CInputMouse::Update(void)
{
	// ΟιΎ
	DIMOUSESTATE2 aKeyState;		// }EXόΝξρ
	int nCntKey;

	// όΝfoCX©ηf[^πζΎ
	if (SUCCEEDED(m_pDevMouse->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{
		for (nCntKey = 0; nCntKey < MAX_MOUSE_KEY; nCntKey++)
		{
			// }EXgK[ξρπΫΆ
			m_aKeyStateTrigger.rgbButtons[nCntKey] = ~m_aKeyState.rgbButtons[nCntKey] & aKeyState.rgbButtons[nCntKey];

			// }EX[XξρπΫΆ
			m_aKeyStateRelease.rgbButtons[nCntKey] = m_aKeyState.rgbButtons[nCntKey] & ~aKeyState.rgbButtons[nCntKey];

			// }EXvXξρπΫΆ
			m_aKeyState = aKeyState;
		}
	}
	else
	{
		// }EXΦΜANZX πlΎ
		m_pDevMouse->Acquire();
	}
}

//=============================================================================
//  }EXvXξρΜζΎ
// Author1 : ϊ±l
// Author2 : KOZUNA HIROHITO
// Tv : ψΜL[ΜξρπΤ·
//=============================================================================
bool CInputMouse::GetPress(MOUSE_KEY eKey)
{
	return (m_aKeyState.rgbButtons[eKey] & 0x80) ? true : false;
}

//=============================================================================
// }EXgK[ξρΜζΎ
// Author1 : ϊ±l
// Author2 : KOZUNA HIROHITO
// Tv : ψΜL[ΜξρπΤ·
//=============================================================================
bool CInputMouse::GetTrigger(MOUSE_KEY eKey)
{
	return (m_aKeyStateTrigger.rgbButtons[eKey] & 0x80) ? true : false;
}

//=============================================================================
// }EX[XξρΜζΎ
// Author1 : ϊ±l
// Author2 : KOZUNA HIROHITO
// Tv : ψΜL[ΜξρπΤ·
//=============================================================================
bool CInputMouse::GetRelease(MOUSE_KEY eKey)
{
	return (m_aKeyStateRelease.rgbButtons[eKey] & 0x80) ? true : false;
}

//=============================================================================
// SL[vXΜξρΜζΎ
// Author : KOZUNA HIROHITO
// Tv : ψΜL[ΜξρπΤ·
//=============================================================================
bool CInputMouse::GetPressAll()
{
	for (int nCnt = 0; nCnt < MAX_MOUSE_KEY; nCnt++)
	{
		if (GetPress((MOUSE_KEY)nCnt))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// SL[vXΜξρΜζΎ
// Author : KOZUNA HIROHITO
// Tv : ψΜL[ΜξρπΤ·
//=============================================================================
bool CInputMouse::GetTriggerAll()
{
	for (int nCnt = 0; nCnt < MAX_MOUSE_KEY; nCnt++)
	{
		if (GetTrigger((MOUSE_KEY)nCnt))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// SL[vXΜξρΜζΎ
// Author : KOZUNA HIROHITO
// Tv : ψΜL[ΜξρπΤ·
//=============================================================================
bool CInputMouse::GetReleaseAll()
{
	for (int nCnt = 0; nCnt < MAX_MOUSE_KEY; nCnt++)
	{
		if (GetRelease((MOUSE_KEY)nCnt))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// }EXJ[\ΜΚuΜζΎ
// Author1 : ϊ±l
// Author2 : KOZUNA HIROHITO
// Tv : }EXJ[\ΜΚuπζΎ΅AlπΤ·
//=============================================================================
D3DXVECTOR3 CInputMouse::GetMouseCursor(void)
{
	// XN[ΐWγΜ}EXJ[\ΜΚuΜζΎ
	GetCursorPos(&m_Pos);

	// EBhEγΜ}EXJ[\ΜΚuΜζΎ
	ScreenToClient(m_hWnd, &m_Pos);

	return D3DXVECTOR3((float)m_Pos.x, (float)m_Pos.y, 0.0f);
}

//=============================================================================
// }EXzC[ΜΪ?ΚζΎ
// Author : ϊ±l
// Tv : }EXzC[ΜΪ?ΚΜlπΤ·
//=============================================================================
int CInputMouse::GetMouseWheel(void)
{
	return (int)m_aKeyState.lZ;
}

//=============================================================================
// }EXΜΪ?ΚζΎ
// Author : ϊ±l
// Tv : }EXΜΪ?ΚΜlπΤ·
//=============================================================================
D3DXVECTOR3 CInputMouse::GetMouseMove(void)
{
	return D3DXVECTOR3((float)(m_aKeyState.lX), (float)(m_aKeyState.lY), (float)(m_aKeyState.lZ));
}
