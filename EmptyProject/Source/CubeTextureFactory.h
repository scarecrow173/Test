//=======================================================================================
//!	@file	:	CubeTextureFactory.h
//!	@author	:	è¨éR âlå\
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
//!	@class	:	CubeTextureFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class CubeTextureFactory : public ITextureFactory
{
public:
	friend TexturePool;

	virtual ITexture* CreateTexture();
	virtual ITexture* CreateTextureFromFile(const std::string& filePath);

private:
	CubeTextureFactory();
	virtual ~CubeTextureFactory();
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================