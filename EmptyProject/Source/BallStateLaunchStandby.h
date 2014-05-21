//=======================================================================================
//!	@file	:	BallStateLaunchStandby.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IState.h"
#include "InputKeyboard.h"
namespace AK
{
namespace Collision{ class ICollision; };
class Ball;
class Paddle;
//=======================================================================================
//!	@class	:	BallStateLaunchStandby
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BallStateLaunchStandby : public IState<Ball>
{
public:
	BallStateLaunchStandby();
	virtual ~BallStateLaunchStandby();

	virtual void			EntryAction(Ball* stateUser);
	virtual void			InputAction(Ball* stateUser);
	virtual void			ExitAction(Ball* stateUser);
	virtual IState<Ball>*	TransitionAction();

private:
	InputKeyboard			m_Keyboard;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================