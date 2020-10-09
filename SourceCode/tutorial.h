//*************************************************************************************************************
//
// チュートリアル処理 [tutorial.h]
// Author:KOKI NISHIYAMA
//
//*************************************************************************************************************
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//-------------------------------------------------------------------------------------------------------------
// インクルードファイル
//-------------------------------------------------------------------------------------------------------------
#include "mode.h"

//-------------------------------------------------------------------------------------------------------------
// クラス定義
//-------------------------------------------------------------------------------------------------------------
class C2DUi;
class CTutorial : public CMode
{
public:
	/* 列挙型 */
	// チュートリアルUI
	typedef enum
	{
		TUTORIALUI_DISCRIPTION = 0,		// 説明
		TUTORIALUI_MAX
	} TUTORIALUI;

	/* 関数 */
	CTutorial() {};					// コンストラクタ
	~CTutorial() {};					// デストラクタ

	static CTutorial *Create(void);	// 生成
	void Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画

private:
	/* 変数 */
	C2DUi *pC2dui[TUTORIALUI_MAX];					// ２DUIポインタ
};

#endif