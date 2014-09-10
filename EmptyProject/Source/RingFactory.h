//=======================================================================================
//!	@file	:	RingFactory.h
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
//!	@class	:	RingFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class RingFactory : public IPrimitiveFactory
{
public:
	friend PrimitivePool;


private:
	RingFactory();
	virtual ~RingFactory();
	
	virtual BufferResource*			CreatePrimitive();
	
	static RingFactory*		m_Instance;
	U32						m_RingCount;

};
//=======================================================================================
//	inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================