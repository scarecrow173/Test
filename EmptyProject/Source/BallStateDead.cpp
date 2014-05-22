//=======================================================================================
//!	@file	:	BallStateDead.cpp
//!	@brief	:	BallStateLaunchStandby�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "BallStateDead.h"
#include "BallStateLaunchStandby.h"
using namespace AK;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
BallStateDead::BallStateDead()
{
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
BallStateDead::~BallStateDead()
{

}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateDead::EntryAction(Ball* stateUser)
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateDead::InputAction(Ball* stateUser)
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateDead::ExitAction(Ball* stateUser)
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
IState<Ball>* BallStateDead::TransitionAction()
{
	return NEW BallStateLaunchStandby();
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