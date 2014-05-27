//=======================================================================================
//!	@file	:	SpherePool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "Singleton.h"
#include "PrimitivePool.h"
#include "SphereFactory.h"
#include "RefCountedObjectPtr.h"
#include <string>
#ifdef __POOL__TEST_TYPE01__
namespace AK
{
//=======================================================================================
//!	@class	:	SpherePool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SpherePool : public Singleton<SpherePool>, public PrimitivePool
{
public:
	friend Singleton<SpherePool>;

private:
	SpherePool(){ m_PrimitiveCreator = NEW Graphics::SphereFactory(); };
	virtual ~SpherePool(){};

};
//=======================================================================================
//		inline method
//=======================================================================================


};
#endif
//===============================================================
//	End of File
//===============================================================