//=======================================================================================
//!	@file	:	BoxFactory.h
//!	@author	:	小山 瑛圭
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
namespace AK
{

namespace Graphics
{
class PrimitivePool;
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
	// 必ずPrimitivePoolを経由するように
	BoxFactory();
	virtual ~BoxFactory();

	virtual BufferResource*		CreatePrimitive();

	//void				AllClear();


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