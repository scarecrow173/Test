//=======================================================================================
//!	@file	:	SquareFactory.h
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
class SquareFactory : public IPrimitiveFactory
{
public:
	friend PrimitivePool;


private:
	SquareFactory();
	virtual ~SquareFactory();

	Vector3 GetVertexPosition(U32 _n);
	Vector2 GetVertexUV(U32 _n);
	
	virtual BufferResource*			CreatePrimitive();
	
	static SquareFactory*		m_Instance;
	U32						m_SquareCount;

};
//=======================================================================================
//	inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================