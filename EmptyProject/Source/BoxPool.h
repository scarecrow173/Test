//=======================================================================================
//!	@file	:	BoxPool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "Singleton.h"
#include "PrimitivePool.h"
#include "BoxFactory.h"
#include "RefCountedObjectPtr.h"
#include <string>

#ifdef __POOL__TEST_TYPE01__
namespace AK
{
//=======================================================================================
//!	@class	:	BoxPool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BoxPool : public Singleton<BoxPool>, public PrimitivePool
{
public:
	friend Singleton<BoxPool>;

private:
	BoxPool(){ m_PrimitiveCreator = NEW Graphics::BoxFactory(); };
	virtual ~BoxPool(){};

};
//=======================================================================================
//		inline method
//=======================================================================================


};
#endif
//===============================================================
//	End of File
//===============================================================