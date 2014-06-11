//=======================================================================================
//!	@file	:	Spectrum.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include <vector>
#include "Elements.h"
#include "SafeArray.h"

namespace AK
{
namespace Graphics
{
struct SpectrumVertex
{
	float x, y, z;	
	float w;		
	DWORD color;	
	float u, v;
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

	void Draw();
	void Update(const F32* data, const U32 size);

	std::vector<SpectrumVertex>	m_Vertex;
	std::vector<U32>			m_Index;


	LPDIRECT3DVERTEXBUFFER9		m_VertexBuffer;
	LPDIRECT3DINDEXBUFFER9		m_IndexBuffer;
	LPD3DXEFFECT				m_Effect;
	LPDIRECT3DTEXTURE9			m_Texture;
	DWORD						m_FVF;
	SafeArray<F32, 64>			m_PeakData;
	SafeArray<F32, 64>			m_Coefficient;

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