// ===================================================================
//
// �X�R�A���� [ score.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"

// ===================================================================
// �}�N����`
// ===================================================================
#define MAX_SCORE_DIGIT	(5)	// �ő包��
#define MAX_NUM_SCORE	(6)	// �X�R�A�̍ő吔

// ===================================================================
// �N���X��`
// ===================================================================
class CNumericString;

class CScore
{
public:
	CScore();
	~CScore();

	HRESULT Init(void);							// ������
	void Uninit(void);							// �I��
	void Update(void);							// �X�V
	void Draw(void);							// �`��

	static CScore *Create(D3DXVECTOR3 & pos, D3DXVECTOR2 & size, float fValue);		// ����

	static void SetPlayerScore(const float fScore) { m_fPlayerScore = fScore; } // �X�R�A�̐ݒ�
	void SetScore(const float fScore);			// �X�R�A�̐ݒ�

	static float & GetPlayerScore(void)			{ return m_fPlayerScore; }			// �v���C���[�X�R�A�̎擾
	static float * GetDefaultScore(void)		{ return m_fDefaultScore; }			// �f�t�H���g�X�R�A�̎擾
	static float & GetDefaultScore(int nRank)	{ return m_fDefaultScore[nRank]; }	// �f�t�H���g�X�R�A�̌ʎ擾

	static HRESULT Load(void);					// �X�R�A�̃��[�h
	static HRESULT SaveScore(void);					// �X�R�A�̃Z�[�u

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static float m_fPlayerScore;					// �v���C���[�̃X�R�A
	static float m_fDefaultScore[MAX_NUM_SCORE];	// �f�t�H���g�̃X�R�A
	CNumericString * m_pNumStrInt;					// �����i���o�[�̃|�C���^
	CNumericString * m_pNumStrFloat;				// �����i���o�[�̃|�C���^
};

#endif