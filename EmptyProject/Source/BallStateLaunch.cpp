//=======================================================================================
//!	@file	:	BallStateLaunch.cpp
//!	@brief	:	BallStateLaunchクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "BallStateLaunch.h"
#include "BallStateActive.h"
#include "Ball.h"
#include "Paddle.h"
using namespace AK;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BallStateLaunch::BallStateLaunch()
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
BallStateLaunch::~BallStateLaunch()
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
void BallStateLaunch::EntryAction(Ball* stateUser)
{
	// とりあえず固定値
	m_LaunchPower = Vector3(10.f, 5.f, 0.f);
	m_LaunchPower.x = stateUser->GetPaddle()->GetCollision()->GetSpeed().x > 0 ? 10.f : -10.f;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateLaunch::InputAction(Ball* stateUser)
{

}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateLaunch::ExitAction(Ball* stateUser)
{
	stateUser->GetCollision()->SetSpeed(m_LaunchPower);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
IState<Ball>* BallStateLaunch::TransitionAction()
{
	return NEW BallStateActive();
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