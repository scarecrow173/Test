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
	//	関数ポインタ以外の解決策としてはクラス化するぐらいかな？関数の規模的にクラス化せずに行く
	m_TextureLoader["DefaultTexture"]	= LoadDefaultTextureFromFile;
	m_TextureLoader["CubeTexture"]		= LoadCubeTextureFromFile;

	m_TextureCreator["DefaultTexture"]	= CreateDefaultTexture;
	m_TextureCreator["CubeTexture"]		= CreateCubeTexture;
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
TexturePool::~TexturePool()
{
//	auto it = m_PrimitiveCreator.begin(); 
	//while (it != m_PrimitiveCreator.end())
	//{
	//	SAFE_DELETE(it->second);
	//	it = m_PrimitiveCreator.erase(it);
	//}
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
RefCountedObjectPtr TexturePool::GetTexture(const std::string& dataCode)
{
	std::string dataType, textureType, name;
	SplitDataPath(dataCode, dataType, textureType, name);

	//auto iCreator = m_TextureLoader.find(textureType);

	////	ファクトリがm_TextureLoaderに登録されていなければアサートしてNULLのオブジェクト返す
	//if (iCreator == m_TextureLoader.end())
	//{
	//	assert(0);	
	//	return RefCountedObjectPtr(NULL);
	//}

	auto it = m_ManagedResouce.find(dataCode);
	if (it != m_ManagedResouce.end())
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
RefCountedObject* TexturePool::CreateTexture(const std::string& dataCode, const std::string& dataType, const std::string& textureType, const std::string& name)
{
	//まだリファクタリングできそうちょっと後回し
	if (!(dataType == "file" || dataType == "data"))
		return NULL;

	if (dataType == "file")
	{
		auto iLoader = m_TextureLoader.find(textureType);
		if (iLoader == m_TextureLoader.end())
			return NULL;
		m_ManagedResouce[dataCode] = m_TextureLoader[textureType](name);
	}
	else if (dataType == "data")
	{
		auto iCreator = m_TextureCreator.find(textureType);
		if (iCreator == m_TextureCreator.end())
			return NULL;
		m_ManagedResouce[dataCode] = m_TextureCreator[textureType]();
	}


	return m_ManagedResouce[dataCode];
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
void TexturePool::SplitDataPath(std::string src, std::string& dataType, std::string& primitiveType, std::string& name)
{
	static StringEncoder encoder;

	encoder.DeleteSpace(src);
	dataType		= encoder.SplitFront(src, ":");
	primitiveType	= encoder.SplitFront(src, "-");
	name			= src;

	assert(dataType			!= "");
	assert(primitiveType	!= "");
	assert(name				!= "");
}
//---------------------------------------------------------------------------------------
//!	@brief		: 変換が重い可能性
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
ITexture* TexturePool::LoadDefaultTextureFromFile(const std::string& filePath)
{
	DefaultTexture* out = NEW DefaultTexture();
	
	IDirect3DTexture9* tex = NULL;

	USES_CONVERSION;

	D3DXCreateTextureFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		A2W(filePath.c_str()),
		&tex);

	out->SetTexture(&tex);
	return out;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
ITexture* TexturePool::LoadCubeTextureFromFile(const std::string& filePath)
{
	CubeTexture* out = NEW CubeTexture();

	IDirect3DCubeTexture9* tex = NULL;

	USES_CONVERSION;

	D3DXCreateCubeTextureFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		A2W(filePath.c_str()),
		&tex);

	out->SetTexture(&tex);
	return out;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
Graphics::ITexture* TexturePool::CreateDefaultTexture()
{
	DefaultTexture* out = NEW DefaultTexture();
	
	IDirect3DTexture9* tex = NULL;

	out->SetTexture(&tex);

	return out;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
Graphics::ITexture* TexturePool::CreateCubeTexture()
{
	CubeTexture* out = NEW CubeTexture();

	IDirect3DCubeTexture9* tex = NULL;

	out->SetTexture(&tex);

	return out;
}
//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================