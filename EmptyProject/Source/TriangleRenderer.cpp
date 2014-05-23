//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "TriangleRenderer.h"
#include "GraphicsManager.h"

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
TriangleRenderer::TriangleRenderer()
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
TriangleRenderer::~TriangleRenderer()
{
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 三角形描画
//-------------------------------------------------------------
void TriangleRenderer::Draw()
{
	if (!m_IsActive)
		return;

	assert(m_IndexBuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetTransform(D3DTS_WORLD, &m_World);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetIndices(m_IndexBuffer);
	//	TODO:各種引数をちゃんと設定
	GraphicsManager::GetInstance()->GetD3DDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, 
		0,
		m_IndexData.start,
		m_Index.size(),
		0, 
		m_IndexData.face);
}
//-------------------------------------------------------------
//!	@brief		: 三角形描画
//-------------------------------------------------------------
IRenderer* TriangleRenderer::Clone()
{
	TriangleRenderer* clone = NEW TriangleRenderer();
	clone->m_IndexBuffer	= m_IndexBuffer;
	clone->m_IndexData		= m_IndexData;
	clone->m_RefCounter		= m_RefCounter;

	return clone;
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