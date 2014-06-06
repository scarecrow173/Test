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

namespace AK
{

namespace Graphics
{

class PrimitivePool;
//=======================================================================================
//!	@class	:	SphereFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SphereFactory : public IPrimitiveFactory
{
public:
	friend PrimitivePool;


private:
	SphereFactory();
	virtual ~SphereFactory();
	
	virtual BufferResource*			CreatePrimitive();
	
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