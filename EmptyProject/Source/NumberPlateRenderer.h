//=======================================================================================
//!	@file	:	NumberPlateRenderer.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsRenderer.h"

namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	NumberPlateRenderer
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class NumberPlateRenderer : public AbsRenderer
{
public:
	NumberPlateRenderer();
	virtual ~NumberPlateRenderer();

	virtual void Draw();
	void	SetNumber(const U32 _value){ m_DisplayNumber = _value; }
	U32		GetNumber() const { return m_DisplayNumber; }
private:
	U32 CalcDigit(U32 _rawNumber);
	RECT CalcRectFromNumber(U32 _rawNumber);

	DWORD							m_Color;
	D3DRENDERSTATETYPE				m_RenderState;
	RECT							m_Rect;

	U32								m_DisplayNumber;
	U32								m_DisplayDigit;
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================