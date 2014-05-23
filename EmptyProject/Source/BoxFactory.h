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
#include "ReferCountType.h"

namespace AK
{
namespace Graphics
{
class ResourceManager;
//=======================================================================================
//!	@class	:	BoxFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BoxFactory
{
public:
	friend ResourceManager;

private:
	BoxFactory();
	virtual ~BoxFactory();

	IRenderer*			CreateBox();

	void				AllClear();


	static BoxFactory*	m_Instance;
	U32					m_BoxCount;

	//std::hash_map<const std::string, ReferCountType<IRenderer>>	m_BoxResouce;
};
//=======================================================================================
//	inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================