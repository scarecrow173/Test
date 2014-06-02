//=======================================================================================
//!	@file	:	CubeTexture.h
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
//!	@class	:	CubeTexture
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class CubeTexture : public ITexture
{
public:
	CubeTexture();
	virtual ~CubeTexture();

	RTTI_IS_A(CubeTexture);

	LPDIRECT3DCUBETEXTURE9	GetTexture() const;
	void					SetTexture(const LPDIRECT3DCUBETEXTURE9* texture);

private:
	LPDIRECT3DCUBETEXTURE9 m_Texture;

};

//=======================================================================================
//		inline method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline CubeTexture::CubeTexture()
	:	m_Texture	(NULL)
{
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline CubeTexture::~CubeTexture()
{
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline LPDIRECT3DCUBETEXTURE9 CubeTexture::GetTexture() const
{
	return m_Texture;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
inline void	CubeTexture::SetTexture(const LPDIRECT3DCUBETEXTURE9* texture)
{
	assert(*texture);
	m_Texture = *texture;
}

};
};
//===============================================================
//	End of File
//===============================================================