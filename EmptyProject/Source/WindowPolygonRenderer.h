//=======================================================================================
//!	@file	:	WindowPolygonRenderer.h
//!	@author	:	���R �l�\
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
//!	@brief	:	�����������ʁB�����Œ��_�o�b�t�@������肷��B
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


private:
	void CreateVertexBuffer();
	void CreateBufferResouce(std::vector<U32>& indexSrc);


	std::vector<WindowVertex>	m_Vertex;

	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================