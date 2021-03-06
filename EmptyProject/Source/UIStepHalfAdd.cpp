//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "UIStepHalfAdd.h"
#include "GraphicsManager.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
UIStepHalfAdd::UIStepHalfAdd()
{
	m_DrawStep = 10000;
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
UIStepHalfAdd::~UIStepHalfAdd()
{
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool UIStepHalfAdd::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIStepHalfAdd::Draw()
{
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			//アルファテストの無効化
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);			//アルファブレンディングの有効化
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );			//Zバッファへの書き込みを無効にする。
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_BLENDOP,  D3DBLENDOP_ADD );		//ブレンディングオプション加算
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//SRCの設定
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);			//DESTの設定

	GraphicsManager::GetInstance()->GetSprite()->Begin(0);

	for (auto it = m_Renderer.begin(); it != m_Renderer.end(); ++it)
	{
		if ((*it)->IsActive())
			(*it)->Draw();
	}
	GraphicsManager::GetInstance()->GetSprite()->End();
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
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