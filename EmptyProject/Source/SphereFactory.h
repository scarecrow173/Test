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
#include "ReferCountType.h"
namespace AK
{
namespace Graphics
{
class ResourceManager;
//=======================================================================================
//!	@class	:	SphereFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SphereFactory
{
public:
	friend ResourceManager;

private:
	SphereFactory();
	virtual ~SphereFactory();

	
	IRenderer*				CreateSphere();
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