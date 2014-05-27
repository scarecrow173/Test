//=======================================================================================
//!	@file	:	BallStateLaunchStandby.cpp
//!	@brief	:	BallStateLaunchStandbyクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "BallStateLaunchStandby.h"
#include "BallStateLaunch.h"
#include "Ball.h"
#include "Paddle.h"
using namespace AK;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BallStateLaunchStandby::BallStateLaunchStandby()
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
BallStateLaunchStandby::~BallStateLaunchStandby()
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
void BallStateLaunchStandby::EntryAction(Ball* stateUser)
{}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateLaunchStandby::InputAction(Ball* stateUser)
{
	m_Keyboard.Update();
	auto respawn = stateUser->GetPaddle()->GetTransform()->GetTranslation();
	respawn.y += 110.f;
	stateUser->GetCollision()->SetPosition(respawn);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateLaunchStandby::ExitAction(Ball* stateUser)
{}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
IState<Ball>* BallStateLaunchStandby::TransitionAction()
{
	if (m_Keyboard.IsTrigger(KEY_BUTTON1))
		return NEW BallStateLaunch();

	return this;
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