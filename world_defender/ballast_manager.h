//=============================================================================
//
//　瓦礫の管理者処理 [ballast_manager.h]
// Author : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _BALLAST_MANAGER_H_			//このマクロ定義がされなかったら
#define _BALLAST_MANAGER_H_			//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "object.h"
#include <map>
#include <list>
#include "3dobject.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBallast;
class CMeshfield;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBallast_Manager : public CObject
{
private:
	static const float MAP_MAX;
public:
	CBallast_Manager();
	~CBallast_Manager() override;

	HRESULT Init() override;//初期化
	void Uninit() override;//終了処理
	void Update() override;//更新処理
	void Draw() override;//描画処理

	//プレイヤーの位置のSet、Get
	void SetPlListNumber(int nNumber) { m_nPlListNumber = nNumber; }
	int GetPlListNumber() { return m_nPlListNumber; }

	//瓦礫の設定
	void SetBallast(int nNumber, Object_Data Data);

	//メッシュフィールドの設定
	void MeshfieldSet(CMeshfield* pMeshfield);

	//サイコキネシスエリアにあったらそのオブジェクトのポインタを返す
	CBallast* CheckCircleCollision(D3DXVECTOR3 pos, float fRadius);

private:
	std::map<int, std::list<CBallast*>> m_BallastMapData;		//マップ上のオブジェクトをリストで管理する変数
	int m_nPlListNumber;
	CMeshfield *m_pMeshfieldCopy;								//メッシュフィールドポインタのコピー（このコピーは解放をしない）
	int m_nMeshfieldNumMax;										//メッシュのマスの数の最大

};

#endif
