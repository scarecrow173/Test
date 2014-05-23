//=======================================================================================
//!	@file	:	ResourceManager.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <string>
#include <hash_map>
#include "ReferCountType.h"
#include "IResource.h"
namespace AK
{
namespace Graphics
{
class SphereFactory;
class BoxFactory;

enum RESOURCE_TYPE
{
	FROM_FILE		= 0x80000000,
	PRIMITIVE_BOX	= 0x00000001,
	PRIMITIVE_SPHERE= 0x00000002,
};
//=======================================================================================
//!	@class	:	ResourceManager
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ResourceManager
{
public:
	static ResourceManager*	Create();
	static void				Destroy();
	static ResourceManager*	GetInstance();

	IResource* GetResouce(const std::string& name, RESOURCE_TYPE type);
	//U32 ReleaseResouce(const std::string& name);

private:
	ResourceManager();
	virtual ~ResourceManager();

	static ResourceManager*	m_Instance;

	SphereFactory*			m_SphereFactory;
	BoxFactory*				m_BoxFactory;
	std::hash_map<std::string, IResource*>	m_ResouceList;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: インスタンス取得
//!	@return		: インスタンス
//-------------------------------------------------------------
inline ResourceManager* ResourceManager::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}
};
};
//===============================================================
//	End of File
//===============================================================