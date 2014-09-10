//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include <EventTracker.h>
#include<IEventListener.h>
#include "InputKeyboard.h"



using namespace AK;
using namespace Event;
//=======================================================================================
//		Constants Definitions
//=======================================================================================


//=======================================================================================
//		Functions
//=======================================================================================
namespace AK
{
	namespace Event
	{
		InputKeyboard keybord;
		void UpdateEventKeybord()
		{
			keybord.Update();
		}
	}
}

//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------

//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void KeyDownTriggerTracker::Update()
{
	if (keybord.IsTrigger(INPUT_KEY::KEY_DOWN))
	{
		for (auto it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
		{
			if ((*it)->IsActive())
				(*it)->Notify(this);
		}
	}
}
//-------------------------------------------------------------
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void KeyUPTriggerTracker::Update()
{
	if (keybord.IsTrigger(INPUT_KEY::KEY_UP))
	{
		for (auto it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
		{
			if ((*it)->IsActive())
				(*it)->Notify(this);
		}
	}
}
//-------------------------------------------------------------
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void KeyLeftTriggerTracker::Update()
{
	if (keybord.IsTrigger(INPUT_KEY::KEY_LEFT))
	{
		for (auto it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
		{
			if ((*it)->IsActive())
				(*it)->Notify(this);
		}
	}
}
//-------------------------------------------------------------
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void KeyRightTriggerTracker::Update()
{
	if (keybord.IsTrigger(INPUT_KEY::KEY_RIGHT))
	{
		for (auto it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
		{
			if ((*it)->IsActive())
				(*it)->Notify(this);
		}
	}
}
//-------------------------------------------------------------
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void KeyEnterTriggerTracker::Update()
{
	if (keybord.IsTrigger(INPUT_KEY::KEY_BUTTON1))
	{
		for (auto it = m_ListenerList.begin(); it != m_ListenerList.end(); ++it)
		{
			if ((*it)->IsActive())
				(*it)->Notify(this);
		}
	}
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
