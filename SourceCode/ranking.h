//*************************************************************************************************************
//
// �����L���O���� [ranking.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
#ifndef _RANKING_H_
#define _RANKING_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "mode.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define MAX_NUMRANK	(5)		// �ő僉���N�̐�

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
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
	CRanking() {};					// �R���X�g���N�^
	~CRanking() {};					// �f�X�g���N�^

	static CRanking *Create(void);	// ����
	void Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

private:
	C2DUi *m_pUI[RANKUI_MAX];
	static D3DXVECTOR3 m_UIPos[RANKUI_MAX];
	static D3DXVECTOR2 m_UISize[RANKUI_MAX];
	static D3DXVECTOR3 m_scorePos[MAX_NUMRANK];
	CScore *m_pScore[MAX_NUMRANK];
	static int m_nPlayerScore;
};

#endif