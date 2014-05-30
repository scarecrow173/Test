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
#include "Material.h"

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

	//assert(m_IndexBuffer);
	BufferResource* resource = (BufferResource*)m_BufferResource.GetSharedObject();

	IDirect3DIndexBuffer9* indexBuffer = resource->GetIndexBuffer();
	const Matrix tmpWorld = m_Transform->GetTransform();


	GraphicsManager::GetInstance()->GetD3DDevice()->SetTransform(D3DTS_WORLD, &tmpWorld);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetIndices(indexBuffer);

	IndexData drawData = resource->GetIndexData();

	GraphicsManager::GetInstance()->GetD3DDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, 
		0,
		drawData.start,
		drawData.vertexNum,
		0, 
		drawData.face);
}
//-------------------------------------------------------------
//!	@brief		: 三角形描画
//-------------------------------------------------------------
IRenderer* TriangleRenderer::Clone()
{
	TriangleRenderer* clone = NEW TriangleRenderer();
//	clone->m_IndexBuffer	= m_IndexBuffer;
//	clone->m_IndexData		= m_IndexData;
//	clone->m_RefCounter		= m_RefCounter;

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