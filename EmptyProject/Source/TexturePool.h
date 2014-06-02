//=======================================================================================
//!	@file	:	TexturePool.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "ResourcePool.h"
#include "RefCountedObjectPtr.h"
#include "ITexture.h"
#include "Singleton.h"

#include "ITextureFactory.h"

namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	TexturePool
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class TexturePool : public Singleton<TexturePool>, public ResourcePool
{
public:
	friend Singleton<TexturePool>;
	RefCountedObjectPtr GetResource(const std::string& dataCode);

protected:
	TexturePool();
	virtual ~TexturePool();


	RefCountedObjectPtr CreateTexture(const std::string& dataCode, const std::string& dataType, const std::string& textureType, const std::string& name);


	std::unordered_map<std::string, ITextureFactory*> m_TextureCreator;

};

//=======================================================================================
//		inline method
//=======================================================================================


};
};
//===============================================================
//	End of File
//===============================================================