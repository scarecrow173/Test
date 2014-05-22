//=======================================================================================
//!	@file	:	WindowPolygonRenderer.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IRenderer.h"
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
class WindowPolygonRenderer : public IRenderer
{
public:
	WindowPolygonRenderer();
	virtual ~WindowPolygonRenderer();

	virtual void Draw();
	virtual IRenderer* Clone();

	void	CreatePolygon(const U32 divisionWidth = 1, const U32 divisionHeight = 1);


private:

	std::vector<WindowVertex>	m_Vertex;

	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;
	LPD3DXEFFECT				m_Effect;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================