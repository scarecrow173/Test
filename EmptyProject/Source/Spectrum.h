//=======================================================================================
//!	@file	:	Spectrum.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include <vector>
#include "Elements.h"

namespace AK
{
namespace Graphics
{
struct SpectrumVertex
{
	F32 x,y,z,w;
	DWORD color;
	F32 u,v;
};
//=======================================================================================
//!	@class	:	Spectrum
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Spectrum
{
public:
	Spectrum();
	virtual ~Spectrum();

	void CreateSpectrumData();
	//void UV();

	void Draw();
	void Update(F32* data, U32 size);

	std::vector<SpectrumVertex>	m_Vertex;
	std::vector<U32>			m_Index;


	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;
	LPDIRECT3DTEXTURE9			m_Texture;
	DWORD						m_FVF;

protected:

private:

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================