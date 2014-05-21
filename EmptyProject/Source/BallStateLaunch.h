//=======================================================================================
//!	@file	:	BallStateLaunch.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IState.h"
#include "MyMath.h"
namespace AK
{
namespace Collision{ class ICollision; };
class Ball;
class Paddle;
//=======================================================================================
//!	@class	:	BallStateLaunch
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BallStateLaunch : public IState<Ball>
{
public:
	BallStateLaunch();
	virtual ~BallStateLaunch();

	virtual void			EntryAction(Ball* stateUser);
	virtual void			InputAction(Ball* stateUser);
	virtual void			ExitAction(Ball* stateUser);
	virtual IState<Ball>*	TransitionAction();

private:
	Vector3					m_LaunchPower;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================