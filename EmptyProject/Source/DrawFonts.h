//=======================================================================================
//!	@file	:	DrawFonts.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <string>
#include <map>
#include "MyMath.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	DrawFonts
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class DrawFonts
{
public:
	DrawFonts(S32, S32, const std::string&);
	virtual ~DrawFonts();

	void Draw(const std::wstring&, const Matrix&);
private:
	std::map<const wchar_t, IDirect3DTexture9*>	m_FontsTexture;
	std::map<const wchar_t, GLYPHMETRICS>		m_FontsInfo;
	S32											m_FontSize;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================