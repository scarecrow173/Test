//=======================================================================================
//!	@file	:	DrawFonts.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "MyMath.h"
#include "AbsShaderObject.h"

#include <string>
#include <unordered_map>

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
class DrawFonts : public AbsShaderObject
{
public:
	DrawFonts(S32, S32, const std::string&);
	virtual ~DrawFonts();

	
	virtual void	Draw();
	virtual bool	Initilize();

	//void Draw(const std::wstring&, const Matrix&);

	void	SetDrawString(const std::wstring&);
	void	SetWorld(const Matrix&);
	Matrix	GetWorld() const;
	void	SetColor(const DWORD color);
	DWORD	GetColor() const;
private:
	std::unordered_map<const wchar_t, IDirect3DTexture9*>	m_FontsTexture;
	std::unordered_map<const wchar_t, GLYPHMETRICS>			m_FontsInfo;
	S32														m_FontSize;
	std::wstring											m_DrawString;
	Matrix													m_World;
	DWORD													m_Color;

	D3DXHANDLE												m_hWorld;
	D3DXHANDLE												m_hView;
	D3DXHANDLE												m_hProjection;


};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================