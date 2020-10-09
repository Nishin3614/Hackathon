//*************************************************************************************************************
//
// テクスチャ処理[texture.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// インクルードファイル
//-------------------------------------------------------------------------------------------------------------
#include "texture.h"
#include "renderer.h"
#include <string>

//-------------------------------------------------------------------------------------------------------------
// 静的メンバ変数の初期化
//-------------------------------------------------------------------------------------------------------------
int								CTexture::m_nNumTextureMax = 0;		// 最大テクスチャ数
MyVector<LPDIRECT3DTEXTURE9>	CTexture::m_pTexture = {};			// テクスチャ情報のポインタ
MyVector<CString>				CTexture::m_pFileName = {};			// ファイル名のポインタ

//-------------------------------------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------------------------------------
CTexture::CTexture()
{
}

//-------------------------------------------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------------------------------------------
CTexture::~CTexture()
{
}

//-------------------------------------------------------------------------------------------------------------
// 読み込み
//-------------------------------------------------------------------------------------------------------------
void CTexture::Load(void)
{
	// 変数宣言
	DWORD start = timeGetTime();	// 計測スタート時間

	// テクスチャの生成
	CreateTexture();

	DWORD end = timeGetTime();		// 計測終了時間
	// 処理速度の表示
	cout << "texture.cpp == テクスチャ読み込み 処理速度 = " << (end - start) << "　[" << (end - start) * 0.001f << "sec.]\n\n";
}

//-------------------------------------------------------------------------------------------------------------
// 開放
//-------------------------------------------------------------------------------------------------------------
void CTexture::Unload(void)
{
	// テクスチャ情報の開放
	for (int nCntTexture = 0; nCntTexture < m_nNumTextureMax; nCntTexture++)
	{
		m_pTexture[nCntTexture]->Release();
		m_pTexture[nCntTexture] = nullptr;
	}
	// テクスチャ情報コンテナのクリア
	m_pTexture.clear();

	// ファイル名の開放
	for (int nCntFileName = 0; nCntFileName < m_nNumTextureMax; nCntFileName++)
	{
		m_pFileName[nCntFileName].release();
	}
	// ファイル名コンテナのクリア
	m_pFileName.clear();
}

//-------------------------------------------------------------------------------------------------------------
// テクスチャの生成
//-------------------------------------------------------------------------------------------------------------
void CTexture::CreateTexture(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;						// デバイスのポインタ
	pDevice = CManager::GetRenderer().GetDevice();		// デバイスの取得

	// 資源の調達
	GetResource();

	for (int nCntTexture = 0; nCntTexture < m_nNumTextureMax; nCntTexture++)
	{
		// 設定用テクスチャ情報
		LPDIRECT3DTEXTURE9 SetingText;
		STRING SetingStr = m_pFileName[nCntTexture].Get();
		// テクスチャの読み込み
		if (D3DXCreateTextureFromFile(pDevice, SetingStr, &SetingText) != D3D_OK)
		{
#ifdef _DEBUG
			std::string str = "テクスチャの生成に失敗しました[" + std::to_string(nCntTexture) + "]";
			MessageBox(NULL, str.c_str(), "警告！", MB_ICONWARNING);
#endif
		}
		// 要素の挿入
		m_pTexture.insert(m_pTexture.end(), SetingText);
	}
}

//-------------------------------------------------------------------------------------------------------------
// テクスチャ情報の取得
//-------------------------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTextureInfo(int nIndex)
{
	return m_pTexture[nIndex];
}

//-------------------------------------------------------------------------------------------------------------
// テクスチャ数の最大
//-------------------------------------------------------------------------------------------------------------
int CTexture::GetNumTextureMax(void)
{
	return m_nNumTextureMax;
}

//-------------------------------------------------------------------------------------------------------------
// ファイル名の取得
//-------------------------------------------------------------------------------------------------------------
void CTexture::GetFileName(const int nIndex, STRING output)
{
	STRING pName = '\0';
	pName = strstr(m_pFileName[nIndex].Get(), "TEXTURE");
	sprintf(output, "%s", pName);
}

//-------------------------------------------------------------------------------------------------------------
// ファイル名の取得
//-------------------------------------------------------------------------------------------------------------
CONST_STRING CTexture::GetFileName(const int nIndex)
{
	STRING pName = '\0';
	pName = strstr(m_pFileName[nIndex].Get(), "TEXTURE");
	return pName;
}

//-------------------------------------------------------------------------------------------------------------
// 資源の調達
//-------------------------------------------------------------------------------------------------------------
void CTexture::GetResource(void)
{
	// ファイルから初期設定を読みこむクラス宣言
	CLoadFile Load;

	// 文字列へファイルをロードする
	Load.LoadFileIntoString(CManager::GetFIleName(CManager::FILE_TEXTURE));

	// 文字列から初期設定を読み込む
	Load.SetingfromString(ReadFromLine);

	// ファイルデータの破棄
	Load.DeleteFileData();
}

//-------------------------------------------------------------------------------------------------------------
// 1行から情報を読み取る
//-------------------------------------------------------------------------------------------------------------
void CTexture::ReadFromLine(CONST_STRING cnpLine, CONST_STRING cnpEntryType, CONST_STRING cnpEntryData)
{
	if (strcmp("NUMBER", cnpEntryData) != 0)
	{// ファイル名の読み込み
		FileNameLoad(cnpLine);
	}
	else
	{// 個数の読み込み
		NumLoad(cnpLine);
	}
}

//-------------------------------------------------------------------------------------------------------------
// 個数の読み込み
//-------------------------------------------------------------------------------------------------------------
void CTexture::NumLoad(CONST_STRING cnpLine)
{
	// 変数宣言
	int nSetingNumber = 0;	// 設定用個数

	if (sscanf(cnpLine, "NUMBER = %d", &nSetingNumber) == 1)
	{
		// テクスチャ
		m_nNumTextureMax = nSetingNumber;
		// 内容量を増やす
		m_pFileName.reserve(m_nNumTextureMax);
		m_pTexture.reserve(m_nNumTextureMax);
	}
}

//-------------------------------------------------------------------------------------------------------------
// ファイル名の読み込み
//-------------------------------------------------------------------------------------------------------------
void CTexture::FileNameLoad(CONST_STRING cnpLine)
{
	// 変数宣言
	char aSetingFileName[MYLIB_STRINGSIZE];			// 設定用ファイル名
	aSetingFileName[0] = MYLIB_CHAR_UNSET;
	if (sscanf(cnpLine, "FILENAME = %s", aSetingFileName) == 1)
	{
		// 要素を尾末に挿入
		m_pFileName.push_back();
		// 尾末ポインタの取得
		CString *pBack = &m_pFileName.back();
		// 尾末要素に文字列の設定
		pBack->Set(aSetingFileName);
	}
}

