//=======================================================================================
//!	@file	:	BlendMultiTexturesShader.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IShaderObject.h"
#include "Elements.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	DefaultShader
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BlendMultiTexturesShader : public IShaderObject
{
public:
	BlendMultiTexturesShader();
	virtual ~BlendMultiTexturesShader();

	RTTI_IS_A(BlendMultiTexturesShader);

	virtual bool	Initilize();
	virtual void	Draw();

	//void			SetShaderTechniqueByName(const std::string& techniqueName);
private:
	//D3DXHANDLE		m_hDiffuse;
	//D3DXHANDLE		m_hAmbient;
	//D3DXHANDLE		m_hSpecular;
	//D3DXHANDLE		m_hEmissive;
	//D3DXHANDLE		m_hPower;
	//D3DXHANDLE		m_hWorld;
	//D3DXHANDLE		m_hView;
	//D3DXHANDLE		m_hProjection;
	//D3DXHANDLE		m_hLightDir;
	//D3DXHANDLE		m_hEyePos;

	std::vector<IDirect3DTexture9*> m_BlendTextures;
	

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================