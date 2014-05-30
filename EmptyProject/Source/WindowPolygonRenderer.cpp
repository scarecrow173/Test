//=======================================================================================
//!	@file	:	WindowPolygonRenderer.cpp
//!	@brief	:	WindowPolygonRendererクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "WindowPolygonRenderer.h"
#include "GraphicsManager.h"
#include "Colors.h"
using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
WindowPolygonRenderer::WindowPolygonRenderer()
	:	m_VertexBuffer	(NULL)
{
	
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
WindowPolygonRenderer::~WindowPolygonRenderer()
{
	SAFE_RELEASE(m_VertexBuffer);

}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void WindowPolygonRenderer::Draw()
{
	LPDIRECT3DVERTEXBUFFER9 oldBuf;
	UINT oldNum = 0;
	UINT oldStride = 0;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetStreamSource(0, &oldBuf, &oldNum, &oldStride);
	LPDIRECT3DINDEXBUFFER9 oldIndexBuf;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetIndices(&oldIndexBuf);

	LPDIRECT3DVERTEXDECLARATION9 olddel;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetVertexDeclaration(&olddel);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetVertexDeclaration(NULL);

	BufferResource* resource			= (BufferResource*)m_BufferResource.GetSharedObject();
	IDirect3DIndexBuffer9* indexBuffer	= resource->GetIndexBuffer();

	GraphicsManager::GetInstance()->GetD3DDevice()->SetStreamSource(0, m_VertexBuffer, 0, sizeof(WindowVertex));
	GraphicsManager::GetInstance()->GetD3DDevice()->SetFVF(FVF);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetIndices(indexBuffer);
	
	IndexData drawData = resource->GetIndexData();

	GraphicsManager::GetInstance()->GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, drawData.start, drawData.vertexNum, 0, drawData.face);


	GraphicsManager::GetInstance()->GetD3DDevice()->SetFVF(NULL);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetStreamSource(0, oldBuf, oldNum, oldStride);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetIndices(oldIndexBuf);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetVertexDeclaration(olddel);


	SAFE_RELEASE(oldBuf);
	SAFE_RELEASE(oldIndexBuf);
	SAFE_RELEASE(olddel);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
IRenderer* WindowPolygonRenderer::Clone()
{
	return NULL;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void WindowPolygonRenderer::CreatePolygon(const U32 divisionWidth, const U32 divisionHeight)
{
	const F32 ONE_WIDTH		= (F32)(WINDOW_WIDTH / divisionWidth);
	const F32 ONE_HEIGHT	= (F32)(WINDOW_HEIGHT / divisionHeight);

	
	std::vector<U32> indexArray;

	for (U32 iWidth = 0; iWidth < divisionWidth; ++iWidth)
	{
		for (U32 iHeight = 0; iHeight < divisionHeight; ++iHeight)
		{
			WindowVertex vertex[4];
			// 左上:0
			vertex[0].pos.x = iWidth * ONE_WIDTH;
			vertex[0].pos.y = iHeight * ONE_HEIGHT;
			vertex[0].pos.z = 0.f;
			vertex[0].pos.w = 1.f;
			vertex[0].uv.u	= (F32)(iWidth / divisionWidth);
			vertex[0].uv.v	= (F32)(iHeight / divisionHeight);
			vertex[0].color	= 0;

			// 右上:1
			vertex[1].pos.x = (iWidth + 1) * ONE_WIDTH;
			vertex[1].pos.y = iHeight * ONE_HEIGHT;
			vertex[1].pos.z = 0.f;
			vertex[1].pos.w = 1.f;
			vertex[1].uv.u	= (F32)((iWidth + 1) / divisionWidth);
			vertex[1].uv.v	= (F32)(iHeight / divisionHeight);
			vertex[1].color	= 0;

			// 左下:2
			vertex[2].pos.x = iWidth * ONE_WIDTH;
			vertex[2].pos.y = (iHeight + 1) * ONE_HEIGHT;
			vertex[2].pos.z = 0.f;
			vertex[2].pos.w = 1.f;
			vertex[2].uv.u	= (F32)(iWidth / divisionWidth);
			vertex[2].uv.v	= (F32)((iHeight + 1) / divisionHeight);
			vertex[2].color	= 0;

			// 右下:3
			vertex[3].pos.x = (iWidth + 1) * ONE_WIDTH;
			vertex[3].pos.y = (iHeight + 1) * ONE_HEIGHT;
			vertex[3].pos.z = 0.f;
			vertex[3].pos.w = 1.f;
			vertex[3].uv.u	= (F32)((iWidth + 1) / divisionWidth);
			vertex[3].uv.v	= (F32)((iHeight + 1) / divisionHeight);
			vertex[3].color	= 0;

			m_Vertex.push_back(vertex[0]);
			m_Vertex.push_back(vertex[1]);
			m_Vertex.push_back(vertex[2]);
			m_Vertex.push_back(vertex[3]);

			const U32 count = (iWidth * (divisionHeight * 4)) + (iHeight * 4);

			indexArray.push_back(count + 0);
			indexArray.push_back(count + 1);
			indexArray.push_back(count + 2);

			indexArray.push_back(count + 3);
			indexArray.push_back(count + 2);
			indexArray.push_back(count + 1);
		}

	}


	CreateVertexBuffer();
	CreateBufferResouce(indexArray);
}

//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void WindowPolygonRenderer::CreateVertexBuffer()
{
	if (FAILED(GraphicsManager::GetInstance()->GetD3DDevice()->CreateVertexBuffer(
		(UINT)(sizeof(WindowVertex) * m_Vertex.size()), 
		D3DUSAGE_WRITEONLY, 
		FVF, 
		D3DPOOL_MANAGED,
		&m_VertexBuffer,
		0)))
	return;
		WindowVertex* data;


	m_VertexBuffer->Lock(0, NULL, (void**)&data, 0);
	memcpy(data, &m_Vertex[0], sizeof(WindowVertex) * m_Vertex.size());
	m_VertexBuffer->Unlock();
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void WindowPolygonRenderer::CreateBufferResouce(std::vector<U32>& indexSrc)
{
	IndexData indexData;
	indexData.start		= 0;
	indexData.vertexNum	= (U32)indexSrc.size();
	indexData.face		= (U32)indexSrc.size() / 3;


	BufferResource* newResouce = NEW BufferResource();
	newResouce->AddIndex(indexSrc);
	newResouce->ReCreateIndexBuffer();
	newResouce->UpdateIndexData(indexData);

	m_BufferResource = RefCountedObjectPtr(newResouce);
}
//===============================================================
//	End of File
//===============================================================
