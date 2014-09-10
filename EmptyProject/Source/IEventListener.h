//=======================================================================================
//!	@file	:	IEventListener.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include <memory>
#include <vector>

namespace AK
{

namespace Event
{
class EventTrackerBase;
//=======================================================================================
//!	@class	:	IEventListener
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class IEventListener
{
public:
	virtual void Notify(EventTrackerBase* sender)	= 0;
	virtual bool IsActive()	const					= 0;
private:

};
//=======================================================================================
//		inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================