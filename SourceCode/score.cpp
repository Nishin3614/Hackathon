//=============================================================================
//
// �X�R�A���� [ score.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#include "score.h"
#include "NumericString.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FILENAME_RANKING	("data/TEXT/Ranking.txt")	// �����L���O�̃e�L�X�g�t�@�C��

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
float CScore::m_fPlayerScore					= 0;
float CScore::m_fDefaultScore[MAX_NUM_SCORE]	= {};
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CScore::Init(void)
{
	// ����
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CScore::Uninit(void)
{
	if (m_pNumStrInt)
	{
		m_pNumStrInt->Uninit();
		delete m_pNumStrInt;
		m_pNumStrInt = nullptr;
	}

	if (m_pNumStrFloat)
	{
		m_pNumStrFloat->Uninit();
		delete m_pNumStrFloat;
		m_pNumStrFloat = nullptr;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CScore::Update(void)
{
	if (m_pNumStrInt)
		m_pNumStrInt->Update();
	if (m_pNumStrFloat)
		m_pNumStrFloat->Update();
}

//=============================================================================
// �`��
//=============================================================================
void CScore::Draw(void)
{
	if (m_pNumStrInt)
		m_pNumStrInt->Draw();
	if (m_pNumStrFloat)
		m_pNumStrFloat->Draw();
}

//=============================================================================
// ����
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 & pos, D3DXVECTOR2 & size, float fValue)
{
	// �����̒l���擾
	int IntValue = (int)fValue;
	// �����̒l���擾
	int FloatValue = (int)(fValue - (float)IntValue) * 100;

	// �������m��
	CScore *pScore = new CScore;
	// ������
	pScore->Init();
	// �i���o�[�̐���
	pScore->m_pNumStrInt = CNumericString::Create(pos, MYLIB_D3DXCOR_SET, size, 0.0f, IntValue);
	pScore->m_pNumStrInt->BindTexture(CTexture::GetTextureInfo(CTexture::NAME_NUMBER));
	// �i���o�[�̐���
	pScore->m_pNumStrFloat = CNumericString::Create(pos, MYLIB_D3DXCOR_SET, size, 0.0f, FloatValue);
	pScore->m_pNumStrFloat->BindTexture(CTexture::GetTextureInfo(CTexture::NAME_NUMBER));
	// �l��Ԃ�
	return pScore;
}

//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CScore::SetScore(const float fScore)
{
	// �����̒l���擾
	int IntValue = (int)fScore;
	// �����̒l���擾
	int FloatValue = (int)(fScore - (float)IntValue) * 100;
	// ������ύX
	m_pNumStrInt->m_nValue = IntValue;
	m_pNumStrFloat->m_nValue = FloatValue;
}

//=============================================================================
// �X�R�A�̃��[�h
//=============================================================================
HRESULT CScore::Load(void)
{
	// �ϐ��錾
	FILE *pFile = nullptr;

	char cHeadText[64];
	char cReadText[64];
	char cDieText[64];
	int nCntScore = 0;

	// �t�@�C�����J��
	pFile = fopen(FILENAME_RANKING, "r");

	// nullcheck
	if (pFile)
	{
		printf("==================================================\n");
		printf("�����L���O�t�@�C���̓ǂݍ��݊J�n\n");

		// �X�N���v�g������܂ŌJ��Ԃ�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}
		// �X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// �G���h�X�N���v�g������܂ŌJ��Ԃ�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				// ���s
				if (strcmp(cHeadText, "\n") == 0)
				{
				}
				// �X�R�A��������
				else if (strcmp(cHeadText, "PLAYERSCORE") == 0)
				{
					// ���f���^�C�v���̎擾
					sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_fPlayerScore);
				}
				// �X�R�A��������
				else if (strcmp(cHeadText, "SCORE") == 0)
				{
					// ���f���^�C�v���̎擾
					sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_fDefaultScore[nCntScore]);
					// �X�R�A�ԍ��̉��Z
					nCntScore++;
				}
			}
			// �t�@�C�������
			fclose(pFile);
		}

		printf("�����L���O�t�@�C���̓ǂݍ��ݏI��\n");
		printf("==================================================\n");
	}
	// �t�@�C�����J���Ȃ������Ƃ�
	else
	{
		printf("�����L���O�t�@�C�����J���܂���ł����B\n");
		printf("==================================================\n");
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �X�R�A�̃Z�[�u
//=============================================================================
HRESULT CScore::SaveScore(void)
{
	// �Œ�X�R�A���v���C���[�̂��̂ɏ�������
	m_fDefaultScore[5] = m_fPlayerScore;

	// �����L���O�̓���ւ�
	for (int nCount = 0; nCount < MAX_NUM_SCORE - 1; nCount++)
	{
		for (int nCount2 = nCount + 1; nCount2 < MAX_NUM_SCORE; nCount2++)
		{
			// �X�R�A�������Ă���
			if (m_fDefaultScore[nCount] < m_fDefaultScore[nCount2])
			{
				// ���ʂ̓���ւ�
				float fData = m_fDefaultScore[nCount2];
				m_fDefaultScore[nCount2] = m_fDefaultScore[nCount];
				m_fDefaultScore[nCount] = fData;
			}
		}
	}

	// �ϐ��錾
	FILE *pFile;

	// �e�L�X�g�t�@�C�������₷������R�����g
	char cComment0[8] = "\n";

	// �������ݗp�̕ϐ�
	char cWriteText[64];

	// �ʒu�E��]�̎擾�p
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	// �t�@�C�����J��
	pFile = fopen(FILENAME_RANKING, "w");

	// nullcheck
	if (pFile)
	{
		int nCntScore = 0;

		// �R�����g�ݒ�
		strcpy(cWriteText, "SCRIPT\n");
		fputs(cWriteText, pFile);															// SCRIPT
		fputs(cComment0, pFile);															// \n

		// �R�����g�ݒ�
		sprintf(cWriteText, "PLAYERSCORE : %.3f\n",
			m_fPlayerScore);
		fputs(cWriteText, pFile);														// PLAYERSCORE = m_fPlayerScore

		for (int nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
		{
			// �R�����g�ݒ�
			sprintf(cWriteText, "SCORE : %.3f\n",
				m_fDefaultScore[nCntScore]);
			fputs(cWriteText, pFile);														// SCORE = m_fDefaultScore
		}

		fputs(cComment0, pFile);															// \n

		// �R�����g�ݒ�
		strcpy(cWriteText, "END_SCRIPT\n");
		fputs(cWriteText, pFile);															// END_SCRIPT

		// �t�@�C�������
		fclose(pFile);
	}
	// �t�@�C�����J���Ȃ�������
	else
	{
		// �R���\�[���ɕ\��
		printf("�����L���O�t�@�C�����J���܂���ł����B\n");
		// ���s
		return E_FAIL;
	}

	// ����
	return S_OK;
}