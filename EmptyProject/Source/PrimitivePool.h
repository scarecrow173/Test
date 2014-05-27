//=======================================================================================
//!	@file	:	PrimitivePool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <hash_map>
#include "IPrimitiveFactory.h"
#include "RefCountedObjectPtr.h"
#include "BoxFactory.h"
#include "SphereFactory.h"
#include "TEST_PrimitivePool_defind.h"
namespace AK
{

//=======================================================================================
//!	@class	:	PrimitivePool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#ifdef __POOL__TEST_TYPE01__
class PrimitivePool
{
public:
	RefCountedObjectPtr GetPrimitive(const std::string& name)
	{
		assert(m_PrimitiveCreator);
		auto it = m_ManagedResouce.find(name);
		if (it != m_ManagedResouce.end())
			return RefCountedObjectPtr(it->second);

		m_ManagedResouce[name] = m_PrimitiveCreator->CreatePrimitive();
		return RefCountedObjectPtr(m_ManagedResouce[name]);
	};

protected:
	PrimitivePool() : m_PrimitiveCreator (NULL) {};
	virtual ~PrimitivePool()
	{
		SAFE_DELETE(m_PrimitiveCreator);
	};



	Graphics::IPrimitiveFactory*					m_PrimitiveCreator;
	std::hash_map<std::string, RefCountedObject*>	m_ManagedResouce;

};
#elif defined __POOL__TEST_TYPE02__

template<class T>
class PrimitivePool : public Singleton<PrimitivePool<T>>
{
public:
	friend Singleton<PrimitivePool<T>>;

	RefCountedObjectPtr GetPrimitive(const std::string& name)
	{
		assert(m_PrimitiveCreator);
		auto it = m_ManagedResouce.find(name);
		if (it != m_ManagedResouce.end())
			return RefCountedObjectPtr(it->second);

		m_ManagedResouce[name] = m_PrimitiveCreator->CreatePrimitive();
		return RefCountedObjectPtr(m_ManagedResouce[name]);
	};

protected:
	PrimitivePool() : m_PrimitiveCreator (NEW T()) {};
	virtual ~PrimitivePool()
	{
		SAFE_DELETE(m_PrimitiveCreator);
	};



	Graphics::IPrimitiveFactory*					m_PrimitiveCreator;
	std::hash_map<std::string, RefCountedObject*>	m_ManagedResouce;

};

typedef PrimitivePool<Graphics::BoxFactory>		BoxPool;
typedef PrimitivePool<Graphics::SphereFactory>	SpherePool;
#endif 
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================
