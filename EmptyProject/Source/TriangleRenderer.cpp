//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
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
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
TriangleRenderer::TriangleRenderer()
{
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
TriangleRenderer::~TriangleRenderer()
{
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �O�p�`�`��
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
//!	@brief		: �O�p�`�`��
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