//=======================================================================================
//!	@file	:	MaterialPool.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <hash_map>
#include <unordered_map>
#include "RefCountedObjectPtr.h"
#include "Material.h"
#include "Singleton.h"

typedef AK::Graphics::Material* (*MaterialLoader)(const std::string&);
typedef AK::Graphics::Material*	(*MaterialCreator)();

namespace AK
{
//=======================================================================================
//!	@class	:	MaterialPool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class MaterialPool : public Singleton<MaterialPool>
{
public:
	friend Singleton<MaterialPool>;
	RefCountedObjectPtr GetMaterial(const std::string& dataCode);

protected:
	MaterialPool();
	virtual ~MaterialPool();

	void SplitDataPath(std::string src, std::string& dataType, std::string& materialType, std::string& name);
	//名前をちゃんと考えなきゃ何をするためのメソッドかわからん
	RefCountedObjectPtr SelectByDataType(const std::string& dataCode, const std::string& dataType, const std::string& materialType, const std::string& name);

	static Graphics::Material* CreateDefaultMaterial();
	static Graphics::Material* LoadCSVMaterial(const std::string& filePath);

	std::hash_map<std::string, RefCountedObjectPtr>		m_ManagedResouce;
	std::unordered_map<std::string, MaterialCreator>	m_MaterialCreator;
	std::unordered_map<std::string, MaterialLoader>		m_MaterialLoader;

};

//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================