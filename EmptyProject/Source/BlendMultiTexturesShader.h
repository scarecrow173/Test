//=======================================================================================
//!	@file	:	BlendMultiTexturesShader.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IShaderObject.h"
#include "DefaultTexture.h"
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

	void			SetBackBuffer(IDirect3DSurface9** backbuffer);
	void			AddBlendTexture(IDirect3DTexture9** blendtex);
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
	
	
	IDirect3DSurface9*				m_BackBuffer;
	RefCountedObjectPtr				m_FinalOutPutTextureRefPtr;
	DefaultTexture*					m_FinalOutPutTextureRef;
	IDirect3DSurface9*				m_FinalOutPutSurface;
	std::vector<IDirect3DTexture9*> m_BlendTextures;
	
	D3DXHANDLE						m_hBlendTextureNum;
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================