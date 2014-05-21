//=======================================================================================
//!	@file	:	WindowPolygonRenderer.cpp
//!	@brief	:	WindowPolygonRendererクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "WindowPolygonRenderer.h"
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
	,	m_Effect		(NULL)
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
WindowPolygonRenderer::~WindowPolygonRenderer()
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
void WindowPolygonRenderer::Draw()
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void WindowPolygonRenderer::CreatePolygon(const U32 divisionWidth, const U32 divisionHeight)
{
	const F32 ONE_WIDTH		= WINDOW_WIDTH / divisionWidth;
	const F32 ONE_HEIGHT	= WINDOW_HEIGHT / divisionHeight;
	const U32 POLYGON_NUM	= divisionWidth * divisionHeight;

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
			vertex[0].uv.u	= iWidth / divisionWidth;
			vertex[0].uv.v	= iHeight / divisionHeight;
			vertex[0].color	= 0.f;

			// 右上:1
			vertex[1].pos.x = (iWidth + 1) * ONE_WIDTH;
			vertex[1].pos.y = iHeight * ONE_HEIGHT;
			vertex[1].pos.z = 0.f;
			vertex[1].pos.w = 1.f;
			vertex[1].uv.u	= (iWidth + 1) / divisionWidth;
			vertex[1].uv.v	= iHeight / divisionHeight;
			vertex[1].color	= 0.f;

			// 左下:2
			vertex[2].pos.x = iWidth * ONE_WIDTH;
			vertex[2].pos.y = (iHeight + 1) * ONE_HEIGHT;
			vertex[2].pos.z = 0.f;
			vertex[2].pos.w = 1.f;
			vertex[2].uv.u	= iWidth / divisionWidth;
			vertex[2].uv.v	= (iHeight + 1) / divisionHeight;
			vertex[2].color	= 0.f;

			// 右下:3
			vertex[3].pos.x = (iWidth + 1) * ONE_WIDTH;
			vertex[3].pos.y = (iHeight + 1) * ONE_HEIGHT;
			vertex[3].pos.z = 0.f;
			vertex[3].pos.w = 1.f;
			vertex[3].uv.u	= (iWidth + 1) / divisionWidth;
			vertex[3].uv.v	= (iHeight + 1) / divisionHeight;
			vertex[3].color	= 0.f;

			m_Vertex.push_back(vertex[0]);
			m_Vertex.push_back(vertex[1]);
			m_Vertex.push_back(vertex[2]);
			m_Vertex.push_back(vertex[3]);

			const U32 count = (iWidth * (divisionHeight * 4)) + (iHeight * 4);

			m_Index.push_back(count + 0);
			m_Index.push_back(count + 1);
			m_Index.push_back(count + 2);

			m_Index.push_back(count + 3);
			m_Index.push_back(count + 2);
			m_Index.push_back(count + 1);
		}

	}

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
