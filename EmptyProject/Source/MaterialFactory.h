//=======================================================================================
//!	@file	:	MaterialFactory.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IMaterialFactory.h"
namespace AK
{
namespace Graphics
{
class MaterialPool;
//=======================================================================================
//!	@class	:	IMaterialFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class MaterialFactory : public IMaterialFactory
{
public:
	friend MaterialPool;

	virtual Material* CreateMaterial();
	virtual Material* CreateMaterialFromFile(const std::string& filePath);

private:
	MaterialFactory();
	virtual ~MaterialFactory();
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================