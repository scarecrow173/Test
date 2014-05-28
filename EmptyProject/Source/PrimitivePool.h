//=======================================================================================
//!	@file	:	PrimitivePool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <hash_map>
#include <unordered_map>
#include "IPrimitiveFactory.h"
#include "RefCountedObjectPtr.h"
#include "BoxFactory.h"
#include "SphereFactory.h"
#include "Singleton.h"

namespace AK
{
//=======================================================================================
//!	@class	:	PrimitivePool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class PrimitivePool : public Singleton<PrimitivePool>
{
public:
	friend Singleton<PrimitivePool>;

	RefCountedObjectPtr GetPrimitive(const std::string& dataCode);

protected:
	PrimitivePool();
	virtual ~PrimitivePool();

	void SplitDataPath(std::string src, std::string& dataType, std::string& primitiveType/*, std::string& name*/);

	std::hash_map<std::string, RefCountedObject*>					m_ManagedResouce;
	std::unordered_map<std::string, Graphics::IPrimitiveFactory*>	m_PrimitiveCreator;
};

//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================
