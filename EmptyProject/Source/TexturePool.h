//=======================================================================================
//!	@file	:	TexturePool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <hash_map>
#include <unordered_map>
#include "RefCountedObjectPtr.h"
#include "ITexture.h"
#include "Singleton.h"

typedef AK::Graphics::ITexture* (*TextureLoader)(const std::string&);
typedef AK::Graphics::ITexture*	(*TextureCreator)();

namespace AK
{
//=======================================================================================
//!	@class	:	TexturePool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class TexturePool : public Singleton<TexturePool>
{
public:
	friend Singleton<TexturePool>;
	RefCountedObjectPtr GetTexture(const std::string& dataCode);

protected:
	TexturePool();
	virtual ~TexturePool();

	void SplitDataPath(std::string src, std::string& dataType, std::string& textureType, std::string& name);

	RefCountedObject* CreateTexture(const std::string& dataCode, const std::string& dataType, const std::string& textureType, const std::string& name);

	static Graphics::ITexture* LoadDefaultTextureFromFile(const std::string& filePath);
	static Graphics::ITexture* LoadCubeTextureFromFile(const std::string& filePath);

	static Graphics::ITexture* CreateDefaultTexture();
	static Graphics::ITexture* CreateCubeTexture();


	std::hash_map<std::string, RefCountedObject*>	m_ManagedResouce;
	std::unordered_map<std::string, TextureLoader>	m_TextureLoader;
	std::unordered_map<std::string, TextureCreator>	m_TextureCreator;
};

//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================