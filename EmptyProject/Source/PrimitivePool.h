//=======================================================================================
//!	@file	:	PrimitivePool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "ResourcePool.h"
#include "IPrimitiveFactory.h"
#include "BoxFactory.h"
#include "SphereFactory.h"
#include "RingFactory.h"
#include "Singleton.h"

namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	PrimitivePool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class PrimitivePool : public Singleton<PrimitivePool>, public ResourcePool
{
public:
	friend Singleton<PrimitivePool>;

	RefCountedObjectPtr GetResource(const std::string& dataCode);

protected:
	PrimitivePool();
	virtual ~PrimitivePool();


	std::unordered_map<std::string, Graphics::IPrimitiveFactory*>	m_PrimitiveCreator;
};

//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================
