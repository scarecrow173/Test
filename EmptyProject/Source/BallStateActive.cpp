//=======================================================================================
//!	@file	:	BallStateActive.cpp
//!	@brief	:	BallStateActiveクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "BallStateActive.h"
#include "BallStateDead.h"
#include "BallStateLaunchStandby.h"
#include "BlockSystem.h"
#include "Ball.h"
#include "SoundManager.h"

using namespace AK;
using namespace Collision;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BallStateActive::BallStateActive()
	:	m_Collision	(NULL)
	,	m_NextState	(0x00000000)
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
BallStateActive::~BallStateActive()
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
void BallStateActive::EntryAction(Ball* stateUser)
{
	m_Collision		= stateUser->GetCollision();
	m_BottomLine	= stateUser->GetBottomLine();
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateActive::InputAction(Ball* stateUser)
{
	std::vector<AbsCollisionObject*> l_list;
	
	const Vector3 before = m_Collision->GetSpeed();
	m_Collision->Update(l_list);

	if (!l_list.empty())
	{
		for (auto it = l_list.begin(); it != l_list.end(); ++it)
		{
			Func(*it);
			if (stateUser->GetBlockSystem()->DeleteBlock(*it) && stateUser->IsPowerup())
				m_Collision->SetSpeed(before);
		}
	}
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateActive::ExitAction(Ball* stateUser)
{}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
IState<Ball>* BallStateActive::TransitionAction()
{
	if (m_NextState & NEXT_DEAD)
		return NEW BallStateDead();
	return this;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BallStateActive::Func(AbsCollisionObject* obj)
{
	if (obj != m_BottomLine)
		return;
   	m_NextState = NEXT_DEAD;
	m_Collision->SetSpeed(Vector3(0.f, 0.f, 0.f));
	Sound::SoundManager::GetInstance()->PlaySE(0,TRUE);
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