//=======================================================================================
//!	@file	:	TextureAnimationController.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once


namespace AK
{
namespace Graphics
{
namespace AnimationType
{
	enum AnimationType
	{
		NORMAL,
		LOOP,
	};
};
//=======================================================================================
//!	@class	:	TextureAnimationController
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class TextureAnimationController
{
public:
	TextureAnimationController(RECT, U32, U32, F32 interval = 0.f);
	virtual ~TextureAnimationController();

	void							Update(F32 elapsedTime);

	void							SetType(const AnimationType::AnimationType type);
	AnimationType::AnimationType	GetType()		const;
	void							SetInterval(const F32 type);
	F32								GetInterval()	const;
	void							Reset();
	RECT							GetRect()		const;
	bool							IsEnd()			const;

private:
	RECT							m_Rect;
	const RECT						m_OneRect;
	const U32						m_WidthNum;
	const U32						m_HeightNum;
	U32								m_CurrentWidthNum;
	U32								m_CurrentHeightNum;
	F32								m_AnimationInterval;
	F32								m_CurrentAnimationTime;
	AnimationType::AnimationType	m_AnimationType;
	bool							m_IsEnd;
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================