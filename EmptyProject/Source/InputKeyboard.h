//=======================================================================================
//!	@file	:	InputKeyboard.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "Input.h"
namespace AK
{

//=======================================================================================
//!	@class	:	InputKeyboard
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class InputKeyboard : public Input
{
public:
	InputKeyboard();
	virtual ~InputKeyboard();

	virtual bool IsTrigger(INPUT_KEY key)	const;
	virtual bool IsKeyDown(INPUT_KEY key)	const;
	virtual bool IsKeyRelease(INPUT_KEY key)const;
	virtual void Update();
	

private:
	U8	m_KeyState;
	U8	m_BeforeKeyState;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================
