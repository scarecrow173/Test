//=======================================================================================
//!	@file	:	BoxFactory.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/5/01
//=======================================================================================
#pragma once
#include "GraphicsManager.h"
#include "IndexData.h"
#include <vector>
#include <hash_map>
#include <string>
#include <iostream>
#include "ReferenceCounter.h"
#include "IPrimitiveFactory.h"
#include "TEST_PrimitivePool_defind.h"
namespace AK
{
class PrimitivePool;
namespace Graphics
{
class ResourceManager;

//=======================================================================================
//!	@class	:	BoxFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BoxFactory : public IPrimitiveFactory
{
public:
	friend PrimitivePool;
private:
	BoxFactory();
	virtual ~BoxFactory();

	virtual BufferResource*		CreatePrimitive();

	void				AllClear();


	static BoxFactory*	m_Instance;
	U32					m_BoxCount;

};
//=======================================================================================
//	inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================