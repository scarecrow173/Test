//=======================================================================================
//!	@file	:	ResourceManager.cpp
//!	@brief	:	ResourceManager�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
//
//#include "ResourceManager.h"
//#include "BoxFactory.h"
//#include "SphereFactory.h"
//
//using namespace AK;
//using namespace Graphics;
////=======================================================================================
////		Constants Definitions
////=======================================================================================
//ResourceManager*	ResourceManager::m_Instance = NULL;
////-------------------------------------------------------------
////!	@brief		: �R���X�g���N�^
////-------------------------------------------------------------
//ResourceManager::ResourceManager()
//	:	m_SphereFactory	(NULL)
//	,	m_BoxFactory	(NULL)
//{
////	m_BoxFactory	= NEW BoxFactory();
////	m_SphereFactory = NEW SphereFactory();
//}
////-------------------------------------------------------------
////!	@brief		: �f�X�g���N�^
////-------------------------------------------------------------
//ResourceManager::~ResourceManager()
//{
////	SAFE_DELETE(m_BoxFactory);
////	SAFE_DELETE(m_SphereFactory);
//}
////=======================================================================================
////		public method
////=======================================================================================
////---------------------------------------------------------------------------------------
////!	@brief		: �C���X�^���X�쐬
////!	@return		: �C���X�^���X
////---------------------------------------------------------------------------------------
//ResourceManager* ResourceManager::Create()
//{
//	if (!m_Instance)
//		m_Instance = NEW ResourceManager();
//	return m_Instance;
//}
////---------------------------------------------------------------------------------------
////!	@brief		: �C���X�^���X�폜
////---------------------------------------------------------------------------------------
//void ResourceManager::Destroy()
//{
//	SAFE_DELETE(m_Instance);
//}
////-------------------------------------------------------------
////!	@brief		: ���\�[�X�̎擾
////!	@param[in]	: ���\�[�X�̖��O(�t�@�C������ǂݍ��ނƂ��̓t�@�C���p�X���ȁH)
////!	@param[in]	: ���\�[�X�^�C�v�̎w��B�t�@�C������ǂݍ��ނƂ���FROM_FILE���g��(������)
////!	@return		: example
////-------------------------------------------------------------
////IResource* ResourceManager::GetResource(const std::string& name, RESOURCE_TYPE type)
////{
////
////	auto it = m_ResourceList.find(name);
////	if (it != m_ResourceList.end())
////		return it->second->Clone();
////
////
////	if (type & FROM_FILE)
////		assert(0);//���݂̓t�@�C���ǂݍ��ݖ������Ȃ̂�
////
////	switch(type & ~FROM_FILE)
////	{
//////	case PRIMITIVE_BOX:
//////		m_ResourceList[name] = m_BoxFactory->CreateBox();
////		break;
////	case PRIMITIVE_SPHERE:
//////		m_ResourceList[name] = m_SphereFactory->CreateSphere();
////		break;
////	default:
////		return NULL;
////	}
////	return m_ResourceList[name]->Clone();
////}
////-------------------------------------------------------------
////!	@brief		: example
////!	@param[in]	: example
////!	@return		: example
////-------------------------------------------------------------
////U32 ResourceManager::ReleaseResouce(const std::string& name)
////{
////	auto it = m_ResouceList.find(name);
////	if (it == m_ResouceList.end())
////	{
////		assert(0);
////		return 0;
////	}
////	//it->second->SubRef();
////	return 0;//it->second->GetRefCount();
////}
////=======================================================================================
////		protected method
////=======================================================================================
//
////=======================================================================================
////		private method
////=======================================================================================
//
////===============================================================
////	End of File
////===============================================================
//

//!<