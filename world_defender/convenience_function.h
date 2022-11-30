//=============================================================================
//
// convenience_function.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _CONVENIENCE_FUNCTION_H_			//このマクロ定義がされなかったら
#define _CONVENIENCE_FUNCTION_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CConvenience_Function
{
private:
	
public:
	CConvenience_Function();
	~CConvenience_Function();

	static D3DXVECTOR3 NormalizationRot(D3DXVECTOR3 In);

private:
};

#endif