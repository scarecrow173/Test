//=======================================================================================
//!	@file	:	DefaultTextureFactory.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "ITextureFactory.h"
namespace AK
{
namespace Graphics
{
class TexturePool;
//=======================================================================================
//!	@class	:	DefaultTextureFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class DefaultTextureFactory : public ITextureFactory
{
public:
	friend TexturePool;

	virtual ITexture* CreateTexture();
	virtual ITexture* CreateTextureFromFile(const std::string& filePath);

private:
	DefaultTextureFactory();
	virtual ~DefaultTextureFactory();
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================