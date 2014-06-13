//=======================================================================================
//!	@file	:	AnimationInfo.cpp
//!	@brief	:	AnimationInfoクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "TextureAnimationController.h"
#include "MyMath.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
TextureAnimationController::TextureAnimationController(U32 textureWidth, U32 textureHeight, U32 widthNum, U32 heightNum, F32 interval)
	:	m_TextureWidth			(textureWidth)
	,	m_TextureHeight			(textureHeight)
	,	m_WidthNum				(widthNum)
	,	m_HeightNum				(heightNum)
	,	m_AnimationInterval		(interval)
	,	m_CurrentAnimationTime	(0.f)
	,	m_AnimationType			(AnimationType::NORMAL)
	,	m_IsEnd					(false)
{
	SetRect(&m_Rect, 0, 0, m_TextureWidth / m_WidthNum, m_TextureHeight / heightNum);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
TextureAnimationController::~TextureAnimationController()
{}
	
//=======================================================================================
//		public method
//=======================================================================================
TextureAnimationController& TextureAnimationController::operator = (const TextureAnimationController& other)
{
	assert(0);
	return *this;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void TextureAnimationController::Update(F32 elapsedTime)
{
	if (m_IsEnd)
		return;

	m_CurrentAnimationTime += elapsedTime;

	const U32 frame		= (U32)(m_CurrentAnimationTime / m_AnimationInterval);
	U32 HorizontalNum	= frame % m_WidthNum;
	U32 VerticalNum		= frame / m_WidthNum;

	if (VerticalNum >= m_HeightNum)
	{
		switch(m_AnimationType)
		{
		case AnimationType::NORMAL:
			VerticalNum = m_HeightNum - 1;
			m_IsEnd		= true;
			break;
		case AnimationType::LOOP:
			VerticalNum		= 0;
			HorizontalNum	= 0;
			Reset();
			break;
		default:
			break;
		}
	}
	m_Rect.right			= (HorizontalNum + 1)	* (m_TextureWidth	/ m_WidthNum);
	m_Rect.left				= (HorizontalNum)		* (m_TextureWidth	/ m_WidthNum);
	m_Rect.bottom			= (VerticalNum + 1)		* (m_TextureHeight	/ m_HeightNum);
	m_Rect.top				= (VerticalNum)			* (m_TextureHeight	/ m_HeightNum);


	//if (m_AnimationInterval > m_CurrentAnimationTime)
	//{
	//	return;
	//}
	//m_CurrentAnimationTime -= m_AnimationInterval;

	//m_Rect.right			= (m_CurrentWidthNum + 1)	* m_OneRect.right;
	//m_Rect.left				= (m_CurrentWidthNum)		* m_OneRect.right;

	//if (++m_CurrentWidthNum < m_WidthNum)
	//{
	//	return;
	//}
	//m_CurrentWidthNum		= 0;
	//m_Rect.bottom			= (m_CurrentHeightNum + 1)	* m_OneRect.bottom;
	//m_Rect.top				= (m_CurrentHeightNum)		* m_OneRect.bottom;

	//if (++m_CurrentHeightNum < m_HeightNum)
	//{
	//	return;
	//}

	//switch(m_AnimationType)
	//{
	//case AnimationType::NORMAL:
	//	m_IsEnd = true;
	//	break;
	//case AnimationType::LOOP:
	//	m_CurrentHeightNum = 0;
	//	break;
	//default:
	//	break;
	//}
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void TextureAnimationController::SetType(const AnimationType::AnimationType type)
{
	m_AnimationType = type;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
AnimationType::AnimationType TextureAnimationController::GetType()		const
{
	return m_AnimationType;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void TextureAnimationController::SetInterval(const F32 interval)
{
	m_AnimationInterval = interval;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
F32	TextureAnimationController::GetInterval()	const
{
	return m_AnimationInterval;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void TextureAnimationController::Reset()
{
	m_IsEnd					= false;
	m_CurrentAnimationTime	= 0.f;
	SetRect(&m_Rect, 0, 0, m_TextureWidth / m_WidthNum, m_TextureHeight / m_HeightNum);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
RECT TextureAnimationController::GetRect() const
{
	return m_Rect;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool TextureAnimationController::IsEnd() const
{
	return m_IsEnd;
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
