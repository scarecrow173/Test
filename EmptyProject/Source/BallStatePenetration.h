//=======================================================================================
//!	@file	:	BallStatePenetration.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "BallStateActive.h"
#include "ICollisionObject.h"
namespace AK
{
//=======================================================================================
//!	@class	:	BallStatePenetration
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BallStatePenetration : public BallStateActive
{
public:
	BallStatePenetration();
	virtual ~BallStatePenetration();

	virtual IState<Ball>*	TransitionAction();
private:
	bool Func(Collision::ICollisionObject* obj);

	Collision::ICollisionObject* m_Collision;
	Collision::ICollisionObject* m_BottomLine;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================