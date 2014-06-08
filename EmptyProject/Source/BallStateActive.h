//=======================================================================================
//!	@file	:	BallStateActive.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IState.h"
#include "AbsCollisionObject.h"
namespace AK
{
enum NEXT_STATE
{
	NEXT_DEAD			= 0x00000001,
	NEXT_PENETRATION	= 0x00000002,
};
class Ball;
//=======================================================================================
//!	@class	:	BallStateActive
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BallStateActive : public IState<Ball>
{
public:
	BallStateActive();
	virtual ~BallStateActive();

	virtual void			EntryAction(Ball* stateUser);
	virtual void			InputAction(Ball* stateUser);
	virtual void			ExitAction(Ball* stateUser);
	virtual IState<Ball>*	TransitionAction();

private:
	void Func(Collision::AbsCollisionObject* obj);

	Collision::AbsCollisionObject*	m_Collision;
	Collision::AbsCollisionObject*	m_BottomLine;

	U32								m_NextState;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================