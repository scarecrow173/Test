//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "MaterialPool.h"
#include "StringEncoder.h"
#include "DefaultTexture.h"
#include "CubeTexture.h"
#include "GraphicsManager.h"
#include "CSVReader.h"
#include "MaterialFactory.h"
#include <string>

#include <atlbase.h>
#include <atlconv.h>

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
MaterialPool::MaterialPool()
{
	m_MaterialCreator["Default"] = NEW MaterialFactory();

}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
MaterialPool::~MaterialPool()
{
	auto it = m_MaterialCreator.begin();
	while (it != m_MaterialCreator.end())
	{
		SAFE_DELETE(it->second);
		it = m_MaterialCreator.erase(it);
	}
}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �`�󂲂Ƃ̋��L���\�[�X���擾
//							�^�C�v(data��file)		�@�}�e���A���^�C�v			���O
//!	@param[in]	: ��: dataCode = "data				:	Default				-	sample"
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr MaterialPool::GetResource(const std::string& dataCode)
{
	std::string dataType, materialType, name;
	SplitDataPath(dataCode, dataType, materialType, name);

	auto it = m_ManagedResource.find(dataCode);
	if (it != m_ManagedResource.end())
		return it->second;


	return SelectByDataType(dataCode, dataType, materialType, name);
}
//=======================================================================================
//		protected method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr MaterialPool::SelectByDataType(const std::string& dataCode, const std::string& dataType, const std::string& materialType, const std::string& name)
{
	auto iCreator = m_MaterialCreator.find(materialType);
	if (iCreator == m_MaterialCreator.end())
		return RefCountedObjectPtr(NULL);

	if (dataType == "file")
	{
		m_ManagedResource[dataCode] = RefCountedObjectPtr(m_MaterialCreator[materialType]->CreateMaterialFromFile(name));
	}
	else if (dataType == "data")
	{
		m_ManagedResource[dataCode] = RefCountedObjectPtr(m_MaterialCreator[materialType]->CreateMaterial());
	}
	else
	{
		assert(0);
		return RefCountedObjectPtr(NULL);
	}

	return m_ManagedResource[dataCode];
}

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================