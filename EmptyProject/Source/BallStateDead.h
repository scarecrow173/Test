//=======================================================================================
//!	@file	:	BallStateDead.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IState.h"
namespace AK
{
class Ball;
//=======================================================================================
//!	@class	:	BallStateDead
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BallStateDead : public IState<Ball>
{
public:
	BallStateDead();
	virtual ~BallStateDead();

	virtual void			EntryAction();
	virtual void			InputAction(Ball* stateUser);
	virtual void			ExitAction();
	virtual IState<Ball>*	TransitionAction();

protected:

private:

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================