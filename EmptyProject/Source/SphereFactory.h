//=======================================================================================
//!	@file	:	SphereFactory.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/5/01
//=======================================================================================
#pragma once
#include "GraphicsManager.h"
#include "IndexData.h"
#include <vector>
#include <hash_map>
#include <string>
#include "ReferenceCounter.h"
#include "IPrimitiveFactory.h"
#include "TEST_PrimitivePool_defind.h"

namespace AK
{
#ifdef __POOL__TEST_TYPE01__

class SpherePool;

#elif defined __POOL__TEST_TYPE02__

template <class T>
class PrimitivePool;

#endif

namespace Graphics
{

class ResourceManager;
//=======================================================================================
//!	@class	:	SphereFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SphereFactory : public IPrimitiveFactory
{
public:
#ifdef __POOL__TEST_TYPE01__
	friend SpherePool;
#elif defined __POOL__TEST_TYPE02__
	friend PrimitivePool<SphereFactory>;
#endif

private:
	SphereFactory();
	virtual ~SphereFactory();

	
	virtual BufferResource*			CreatePrimitive();
	void					AllClear();
	
	
	
	static SphereFactory*	m_Instance;
	U32						m_SphereCount;

};
//=======================================================================================
//	inline method
//=======================================================================================




};
};
//===============================================================
//	End of File
//===============================================================