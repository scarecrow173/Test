//=======================================================================================
//!	@file	:	DefaultTexture.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <hash_map>
#include <unordered_map>
#include "ITexture.h"
#include "Singleton.h"

namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	DefaultTexture
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class DefaultTexture : public ITexture
{
public:
	DefaultTexture();
	virtual ~DefaultTexture();

	RTTI_IS_A(TextureType::TextureType, DefaultTexture);

	LPDIRECT3DTEXTURE9	GetTexture() const;
	void				SetTexture(const LPDIRECT3DTEXTURE9* texture);
private:
	LPDIRECT3DTEXTURE9	m_Texture;
};

//=======================================================================================
//		inline method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline DefaultTexture::DefaultTexture()
	:	m_Texture	(NULL)
{
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline DefaultTexture::~DefaultTexture()
{
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline LPDIRECT3DTEXTURE9 DefaultTexture::GetTexture() const
{
	return m_Texture;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline void	DefaultTexture::SetTexture(const LPDIRECT3DTEXTURE9* texture)
{
	assert(*texture);
	m_Texture = *texture;
}
};
};
//===============================================================
//	End of File
//===============================================================