//=======================================================================================
//!	@file	:	EventTracker.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <Singleton.h>

namespace AK
{
namespace Event
{
class IEventListener;
//=======================================================================================
//!	@class	:	EventTrackerBase
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class EventTrackerBase
{
public:
	EventTrackerBase();
	virtual ~EventTrackerBase();
	void EntryListener(IEventListener* _listener);
	void ExitListener(IEventListener* _listener);
	bool Exist(IEventListener* _listener);
	virtual void Update()							= 0;
protected:
	std::vector<IEventListener*>		m_ListenerList;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline EventTrackerBase::EventTrackerBase()
{}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline EventTrackerBase::~EventTrackerBase()
{}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline void EventTrackerBase::EntryListener(IEventListener* _listener)
{
	auto findIt = std::find(m_ListenerList.begin(), m_ListenerList.end(), _listener);
	if (findIt == m_ListenerList.end())
		m_ListenerList.push_back(_listener);
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline void EventTrackerBase::ExitListener(IEventListener* _listener)
{
	auto findIt = std::find(m_ListenerList.begin(), m_ListenerList.end(), _listener);
	if (findIt != m_ListenerList.end())
		m_ListenerList.erase(findIt);
}
//-------------------------------------------------------------
//!	@brief		: âüÇ≥ÇÍÇΩèuä‘
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline bool EventTrackerBase::Exist(IEventListener* _listener)
{
	return (std::find(m_ListenerList.begin(), m_ListenerList.end(), _listener) != m_ListenerList.end());
}

//---------------------------------------------------------------------------------------
//input event
//
void UpdateEventKeybord();
//=======================================================================================
//!	@class	:	KeyDownTriggerTracker
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class KeyDownTriggerTracker : public Singleton<KeyDownTriggerTracker>, public EventTrackerBase
{
public:
	friend Singleton<KeyDownTriggerTracker>;
	virtual void Update();
};
//=======================================================================================
//!	@class	:	KeyUPTriggerTracker
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class KeyUPTriggerTracker : public Singleton<KeyUPTriggerTracker>, public EventTrackerBase
{
public:	
	friend Singleton<KeyUPTriggerTracker>;
	virtual void Update();
private:

};
//=======================================================================================
//!	@class	:	KeyLeftTriggerTracker
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class KeyLeftTriggerTracker : public Singleton<KeyLeftTriggerTracker>, public EventTrackerBase
{
public:	
	friend Singleton<KeyLeftTriggerTracker>;
	virtual void Update();
private:

};
//=======================================================================================
//!	@class	:	KeyRightTriggerTracker
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class KeyRightTriggerTracker : public Singleton<KeyRightTriggerTracker>, public EventTrackerBase
{
public:	
	friend Singleton<KeyRightTriggerTracker>;
	virtual void Update();
private:

};
//=======================================================================================
//!	@class	:	KeyEnterTriggerTracker
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class KeyEnterTriggerTracker : public Singleton<KeyEnterTriggerTracker>, public EventTrackerBase
{
public:
	friend Singleton<KeyEnterTriggerTracker>;
	virtual void Update();
};

//=======================================================================================
//		inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================