//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
UIElement::UIElement(U32 _id, UIType _type)
	:	m_ElemntFont	(nullptr)
	,	m_ElementId		(_id)
	,	m_Type			(_type)
	,	m_ElementName	(L"NULL")
{
	m_ElemntFont = NEW DrawFonts(32, 32, "ＭＳ Ｐゴシック");
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
//!	@brief		: デストラクタ
//-------------------------------------------------------------
UIElement::~UIElement()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_ElemntFont);
	SAFE_DELETE(m_ElemntFont);
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
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
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetElementName(const std::wstring& _elementName)
{
	m_ElementName = _elementName;
	m_ElemntFont->SetDrawString(m_ElementName);
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetColor(const DWORD _color)
{
	m_ElemntFont->SetColor(_color);
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetTransform(Matrix& _transform)
{
	m_ElemntFont->SetWorld(_transform);
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIElement::SetReletiveTransform(Matrix& _transform)
{
	m_reletiveTransform = _transform;
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Matrix UIElement::GetTransform() const
{
	return m_ElemntFont->GetWorld();
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Matrix	UIElement::GetReletiveTransform()	const
{
	return m_reletiveTransform;
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
DWORD UIElement::GetColor() const
{
	return m_ElemntFont->GetColor();
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
U32 UIElement::GetID() const
{
	return m_ElementId;
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
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
