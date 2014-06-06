//=======================================================================================
//!	@file	:	MaterialPool.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "ResourcePool.h"
#include "RefCountedObjectPtr.h"
#include "Material.h"
#include "IMaterialFactory.h"
#include "Singleton.h"

namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	MaterialPool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class MaterialPool : public Singleton<MaterialPool>, public ResourcePool
{
public:
	friend Singleton<MaterialPool>;
	RefCountedObjectPtr GetResource(const std::string& dataCode);

protected:
	MaterialPool();
	virtual ~MaterialPool();

	//名前をちゃんと考えなきゃ何をするためのメソッドか分からない
	RefCountedObjectPtr SelectByDataType(const std::string& dataCode, const std::string& dataType, const std::string& materialType, const std::string& name);

	std::unordered_map<std::string, IMaterialFactory*>	m_MaterialCreator;
};

//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================