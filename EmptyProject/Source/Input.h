//=======================================================================================
//!	@file	:	Input.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

namespace AK
{
enum INPUT_KEY
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_BUTTON1,
	KEY_BUTTON2,
	KEY_BUTTON3,
	KEY_BUTTON4,

};
//=======================================================================================
//!	@class	:	Input
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Input
{
public:
	virtual bool IsTrigger(INPUT_KEY key)	const	= 0;
	virtual bool IsKeyDown(INPUT_KEY key)	const	= 0;
	virtual bool IsKeyRelease(INPUT_KEY key)const	= 0;
	virtual void Update()						= 0;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================
