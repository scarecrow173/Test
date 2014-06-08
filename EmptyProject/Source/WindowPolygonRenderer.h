//=======================================================================================
//!	@file	:	WindowPolygonRenderer.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsRenderer.h"
#include "Elements.h"
namespace AK
{
namespace Graphics
{
struct WindowVertex
{
	VertexFloat4	pos;
	VertexARGB		color;				
	VertexFloat2	uv;
};
//=======================================================================================
//!	@class	:	WindowPolygonRenderer
//!	@brief	:	こいつだけ特別。自分で頂点バッファ作ったりする。
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class WindowPolygonRenderer : public AbsRenderer
{
public:
	WindowPolygonRenderer();
	virtual ~WindowPolygonRenderer();

	virtual void Draw();

	void	CreatePolygon(const U32 divisionWidth = 1, const U32 divisionHeight = 1);

	void	Resize(U32 x, U32 y, U32 width, U32 height);

private:
	void CreateVertexBuffer();
	void CreateBufferResouce(std::vector<U32>& indexSrc);


	std::vector<WindowVertex>	m_Vertex;

	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;
	U32							m_DivisionWidth;
	U32							m_DivisionHeight;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================