//=======================================================================================
//!	@file	:	MaterialPool.h
//!	@author	:	���R �l�\
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

	//���O�������ƍl���Ȃ��ች�����邽�߂̃��\�b�h��������Ȃ�
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