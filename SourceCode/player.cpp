//*************************************************************************************************************
//
// プレイヤー処理 [player.h]
// Author:IKUTO SEKINE
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// インクルードファイル
//-------------------------------------------------------------------------------------------------------------
#include "player.h"
#include "Scene2D.h"
#include "texture.h"

//-------------------------------------------------------------------------------------------------------------
// 生成
//-------------------------------------------------------------------------------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 & pos, D3DXVECTOR2 & size)
{
	CPlayer *pPlayer = new CPlayer;
	pPlayer->Init(pos, size);
	pPlayer->SetObjectTyoe(TYPE_PLAYER);
	return pPlayer;
}

//-------------------------------------------------------------------------------------------------------------
// 初期化
//-------------------------------------------------------------------------------------------------------------
void CPlayer::Init(D3DXVECTOR3 & pos, D3DXVECTOR2 & size)
{
	m_pScene2D = CScene2D::Create(PRIORITY::PRIORITY_PLAYER, pos, ORIGINVERTEXTYPE::ORIGINVERTEXTYPE_ROTCENTER, size);
	m_pScene2D->BindTexture(CTexture::GetTextureInfo(CTexture::NAME_PLAYER));
}

//-------------------------------------------------------------------------------------------------------------
// 終了
//-------------------------------------------------------------------------------------------------------------
void CPlayer::Uninit(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// 更新
//------------------------------------------------------------------------------------------------------------
void CPlayer::Update(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// 描画
//-------------------------------------------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	if (m_pScene2D != nullptr)
	{
		m_pScene2D->Draw();
	}
}
