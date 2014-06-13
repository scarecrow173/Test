//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "UITextureRenderer.h"
#include "GraphicsManager.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
UITextureRenderer::UITextureRenderer(TextureAnimationController* info)
	:	m_TextureRect	(info)
{
	m_Color = 0x8FFFFFFF;
	m_RenderState = (D3DRENDERSTATETYPE)0;
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
UITextureRenderer::~UITextureRenderer()
{
	SAFE_DELETE(m_TextureRect);
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UITextureRenderer::Draw()
{
	m_TextureRect->Update(1.f/60.f);
	GraphicsManager::GetInstance()->GetSprite()->SetTransform(&m_Transform->GetTransform());
	GraphicsManager::GetInstance()->GetSprite()->Draw(GetTexture()->GetTexture(), &m_TextureRect->GetRect(), NULL, NULL, m_Color);
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================
