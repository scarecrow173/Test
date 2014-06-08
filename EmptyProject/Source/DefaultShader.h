//=======================================================================================
//!	@file	:	DefaultShader.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsShaderObject.h"
#include "Elements.h"
#include "DefaultTexture.h"
#include <unordered_map>
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
class DefaultShader : public AbsShaderObject
{
public:
	DefaultShader();
	virtual ~DefaultShader();

	RTTI_IS_A(DefaultShader);

	virtual bool		Initilize();
	virtual void		Draw();

	void				SetShaderTechniqueByName(const std::string& techniqueName);
	RefCountedObjectPtr	GetVelocityMapObjectPtr() const;

private:

	void				NormalDrawPass();
	void				VelocityMapDrawPass();

	RefCountedObjectPtr			m_VelocityTextureObjectPtr;
	DefaultTexture*				m_VelocityTexture;
	IDirect3DSurface9*			m_VelocitySurface;


	D3DXHANDLE		m_hDiffuse;
	D3DXHANDLE		m_hAmbient;
	D3DXHANDLE		m_hSpecular;
	D3DXHANDLE		m_hEmissive;
	D3DXHANDLE		m_hPower;
	D3DXHANDLE		m_hWorld;
	D3DXHANDLE		m_hView;
	D3DXHANDLE		m_hProjection;
	D3DXHANDLE		m_hPrevWorld;
	D3DXHANDLE		m_hLightDir;
	D3DXHANDLE		m_hEyePos;



	std::unordered_map<AbsRenderer*, Matrix> m_PrevMatrix;

};
//=======================================================================================
//		inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================