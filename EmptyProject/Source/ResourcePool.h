//=======================================================================================
//!	@file	:	ResourcePool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <hash_map>
#include <unordered_map>
#include "RefCountedObjectPtr.h"
namespace AK
{
namespace Graphics
{

//=======================================================================================
//!	@class	:	ResourcePool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ResourcePool
{
public:
	virtual RefCountedObjectPtr GetResource(const std::string& dataCode) = 0;

protected:
	ResourcePool();
	virtual ~ResourcePool();

	void SplitDataPath(std::string src, std::string& dataType, std::string& primitiveType, std::string& name);

	std::hash_map<std::string, RefCountedObjectPtr>					m_ManagedResource;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================