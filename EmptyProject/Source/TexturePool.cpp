//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "TexturePool.h"
#include "StringEncoder.h"
#include "DefaultTexture.h"
#include "CubeTexture.h"
#include "GraphicsManager.h"
#include "DefaultTextureFactory.h"
#include "CubeTextureFactory.h"
#include <string>

#include <atlbase.h>
#include <atlconv.h>

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
TexturePool::TexturePool()
{
	m_TextureCreator["DefaultTexture"]	= NEW DefaultTextureFactory();
	m_TextureCreator["CubeTexture"]		= NEW CubeTextureFactory();
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
TexturePool::~TexturePool()
{
	auto it = m_TextureCreator.begin();
	while (it != m_TextureCreator.end())
	{
		SAFE_DELETE(it->second);
		it = m_TextureCreator.erase(it);
	}
}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 形状ごとの共有リソースを取得
//							タイプ(dataかfile)		　テクスチャタイプ				名前orファイルパス
//!	@param[in]	: 例: dataCode = "file				:	DefaultTexture		-	Assets/Texture/sample.png"
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr TexturePool::GetResource(const std::string& dataCode)
{
	std::string dataType, textureType, name;
	SplitDataPath(dataCode, dataType, textureType, name);

	auto it = m_ManagedResource.find(dataCode);
	if (it != m_ManagedResource.end())
		return RefCountedObjectPtr(it->second);

	return RefCountedObjectPtr(CreateTexture(dataCode, dataType, textureType, name));

}
//=======================================================================================
//		protected method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr TexturePool::CreateTexture(const std::string& dataCode, const std::string& dataType, const std::string& textureType, const std::string& name)
{
	auto iCreator = m_TextureCreator.find(textureType);

	//まだリファクタリングできそうちょっと後回し
	if (!(dataType == "file" || dataType == "data") || (iCreator == m_TextureCreator.end()))
		return RefCountedObjectPtr(NULL);

	if (dataType == "file")
	{
		m_ManagedResource[dataCode] = RefCountedObjectPtr(m_TextureCreator[textureType]->CreateTextureFromFile(name));
	}
	else if (dataType == "data")
	{
		m_ManagedResource[dataCode] = RefCountedObjectPtr(m_TextureCreator[textureType]->CreateTexture());
	}


	return m_ManagedResource[dataCode];
}
//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================