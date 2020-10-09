//*************************************************************************************************************
//
// ランキング処理 [ranking.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _RANKING_H_
#define _RANKING_H_

//-------------------------------------------------------------------------------------------------------------
// インクルードファイル
//-------------------------------------------------------------------------------------------------------------
#include "mode.h"

//-------------------------------------------------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------------------------------------------------
#define MAX_NUMRANK	(5)		// 最大ランクの数

//-------------------------------------------------------------------------------------------------------------
// クラス定義
//-------------------------------------------------------------------------------------------------------------
class C2DUi;
class CScore;

class CRanking : public CMode
{
public:
	typedef enum
	{
		RANKUI_1st,
		RANKUI_2nd,
		RANKUI_3rd,
		RANKUI_4th,
		RANKUI_5th,
		RANKUI_RANKING,
		RANKUI_MAX
	} RANKUITYPE;
	CRanking() {};					// コンストラクタ
	~CRanking() {};					// デストラクタ

	static CRanking *Create(void);	// 生成
	void Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画

private:
	C2DUi *m_pUI[RANKUI_MAX];
	static D3DXVECTOR3 m_UIPos[RANKUI_MAX];
	static D3DXVECTOR2 m_UISize[RANKUI_MAX];
	static D3DXVECTOR3 m_scorePos[MAX_NUMRANK];
	CScore *m_pScore[MAX_NUMRANK];
	static int m_nPlayerScore;
};

#endif