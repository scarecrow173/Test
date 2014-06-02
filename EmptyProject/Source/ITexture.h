//=======================================================================================
//!	@file	:	ITexture.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <hash_map>
#include <unordered_map>
#include "RefCountedObject.h"
#include "Singleton.h"

namespace AK
{
namespace Graphics
{
namespace TextureType
{
	enum TextureType
	{
		ITexture,
		DefaultTexture,
		CubeTexture
	};
};
//=======================================================================================
//!	@class	:	ITexture
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ITexture : public RefCountedObject
{
public:
	RTTI_IS_A(ITexture);

	//virtual ITexture*	GetTexture() const PURE;
	//virtual void		SetTexture(const ITexture* texture) PURE;
};

//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================