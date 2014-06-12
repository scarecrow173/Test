//=======================================================================================
//!	@file	:	AnimationInfo.cpp
//!	@brief	:	AnimationInfoクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "TextureAnimationController.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
TextureAnimationController::TextureAnimationController(RECT oneRect, U32 widthNum, U32 heightNum, F32 interval)
	:	m_Rect					(oneRect)
	,	m_OneRect				(oneRect)
	,	m_WidthNum				(widthNum)
	,	m_HeightNum				(heightNum)
	,	m_CurrentWidthNum		(0)
	,	m_CurrentHeightNum		(0)
	,	m_AnimationInterval		(0.05f)
	,	m_CurrentAnimationTime	(0.f)
	,	m_AnimationType			(AnimationType::LOOP)
	,	m_IsEnd					(false)
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
TextureAnimationController::~TextureAnimationController()
{}
	
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void TextureAnimationController::Update(F32 elapsedTime)
{
	//	TODO:リファクタリング
	if (m_IsEnd)
	{
		return;
	}
	m_CurrentAnimationTime += elapsedTime;


	if (m_AnimationInterval > m_CurrentAnimationTime)
	{
		return;
	}
	m_CurrentAnimationTime -= m_AnimationInterval;

	m_Rect.right			= (m_CurrentWidthNum + 1)	* m_OneRect.right;
	m_Rect.left				= (m_CurrentWidthNum)		* m_OneRect.right;

	if (++m_CurrentWidthNum < m_WidthNum)
	{
		return;
	}
	m_CurrentWidthNum		= 0;
	m_Rect.bottom			= (m_CurrentHeightNum + 1)	* m_OneRect.bottom;
	m_Rect.top				= (m_CurrentHeightNum)		* m_OneRect.bottom;

	if (++m_CurrentHeightNum < m_HeightNum)
	{
		return;
	}

	switch(m_AnimationType)
	{
	case AnimationType::NORMAL:
		m_IsEnd = true;
		break;
	case AnimationType::LOOP:
		m_CurrentHeightNum = 0;
		break;
	default:
		break;
	}
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
	m_IsEnd	= false;
	m_Rect	= m_OneRect;
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
