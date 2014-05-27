//=======================================================================================
//!	@file	:	ResourceManager.cpp
//!	@brief	:	ResourceManagerクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
////!	@brief		: コンストラクタ
////-------------------------------------------------------------
//ResourceManager::ResourceManager()
//	:	m_SphereFactory	(NULL)
//	,	m_BoxFactory	(NULL)
//{
////	m_BoxFactory	= NEW BoxFactory();
////	m_SphereFactory = NEW SphereFactory();
//}
////-------------------------------------------------------------
////!	@brief		: デストラクタ
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
////!	@brief		: インスタンス作成
////!	@return		: インスタンス
////---------------------------------------------------------------------------------------
//ResourceManager* ResourceManager::Create()
//{
//	if (!m_Instance)
//		m_Instance = NEW ResourceManager();
//	return m_Instance;
//}
////---------------------------------------------------------------------------------------
////!	@brief		: インスタンス削除
////---------------------------------------------------------------------------------------
//void ResourceManager::Destroy()
//{
//	SAFE_DELETE(m_Instance);
//}
////-------------------------------------------------------------
////!	@brief		: リソースの取得
////!	@param[in]	: リソースの名前(ファイルから読み込むときはファイルパスかな？)
////!	@param[in]	: リソースタイプの指定。ファイルから読み込むときはFROM_FILEを使う(未実装)
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
////		assert(0);//現在はファイル読み込み未実装なので
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