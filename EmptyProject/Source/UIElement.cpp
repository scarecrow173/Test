//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	SampleÉNÉâÉXÇÃÉÅÉìÉoä÷êîêÈåæ
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "UIElement.h"
#include "EventTracker.h"
#include "GraphicsManager.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: ÉRÉìÉXÉgÉâÉNÉ^
//-------------------------------------------------------------
UIElement::UIElement(U32 _id, UIType _type)
	:	m_ElemntFont	(nullptr)
	,	m_ElementId		(_id)
	,	m_Type			(_type)
	,	m_ElementName	(L"NULL")
{
	m_ElemntFont = NEW DrawFonts(32, 32, "ÇlÇr ÇoÉSÉVÉbÉN");
	m_ElemntFont->SetColor(0xFF000000);
	m_ElemntFont->Initilize();
	
	m_ElemntFont->SetDrawString(m_ElementName);
	
	Matrix initPosition;
	D3DXMatrixIdentity(&initPosition);
	m_ElemntFont->SetWorld(initPosition);
	m_reletiveTransform = initPosition;

	
	GraphicsManager::GetInstance()->AddShaderObject(m_ElemntFont);
}
//-------------------------------------------------------------
//!	@brief		: ÉfÉXÉgÉâÉNÉ^
//-------------------------------------------------------------
UIElement::~UIElement()
{
	SAFE_DELETE(m_ElemntFont);
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
UIElement* UIElement::Copy()
{
	UIElement* ret = NEW UIElement(m_ElementId, m_Type);
	ret->SetTransform(GetTransform());
	ret->SetReletiveTransform(GetReletiveTransform());
	ret->SetElementName(m_ElementName);
	ret->SetColor(GetColor());
	return ret;
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetElementName(std::wstring& _elementName)
{
	m_ElementName = _elementName;
	m_ElemntFont->SetDrawString(m_ElementName);
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetColor(const DWORD _color)
{
	m_ElemntFont->SetColor(_color);
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetTransform(Matrix& _transform)
{
	m_ElemntFont->SetWorld(_transform);
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetReletiveTransform(Matrix& _transform)
{
	m_reletiveTransform = _transform;
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Matrix UIElement::GetTransform() const
{
	return m_ElemntFont->GetWorld();
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Matrix	UIElement::GetReletiveTransform()	const
{
	return m_reletiveTransform;
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
DWORD UIElement::GetColor() const
{
	return m_ElemntFont->GetColor();
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
U32 UIElement::GetID() const
{
	return m_ElementId;
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
UIType UIElement::GetType()	const
{
	return m_Type;
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
