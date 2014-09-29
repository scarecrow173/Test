//=======================================================================================
//!	@file	:	MaterialPool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include "DrawFonts.h"

namespace AK
{
namespace Graphics
{
enum UIType
{
	Origin,
	Copy,
};
//=======================================================================================
//!	@class	:	MaterialPool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class UIElement
{
public:
	UIElement(U32 _id, UIType _type = Origin);
	virtual ~UIElement();

	UIElement* Copy();

	void	SetElementName(const std::wstring& _elementName);
	void	SetColor(const DWORD _color);
	void	SetTransform(Matrix& _transform);
	void	SetReletiveTransform(Matrix& _transform);

	Matrix	GetTransform()			const;
	Matrix	GetReletiveTransform()	const;
	DWORD	GetColor()				const;
	U32		GetID()					const;
	UIType	GetType()				const;
private:
	U32				m_ElementId;
	UIType			m_Type;
	DrawFonts*		m_ElemntFont;
	std::wstring	m_ElementName;
	Matrix			m_reletiveTransform;
};

//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================