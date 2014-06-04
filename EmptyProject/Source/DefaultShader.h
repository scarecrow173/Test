//=======================================================================================
//!	@file	:	DefaultShader.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IShaderObject.h"
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
class DefaultShader : public IShaderObject
{
public:
	DefaultShader();
	virtual ~DefaultShader();

	RTTI_IS_A(DefaultShader);

	virtual bool	Initilize();
	virtual void	Draw();

	void			SetShaderTechniqueByName(const std::string& techniqueName);
private:
	RefCountedObjectPtr			m_VelocityTextureObjectPtr;
	DefaultTexture*				m_VelocityTexture;
	IDirect3DSurface9*			m_VelocitySurface;
	IDirect3DSurface9*			m_VelocityDepthSurface;

	D3DXHANDLE		m_hVelocityTechnique;

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



	std::unordered_map<U32, Matrix> m_PrevMatrix;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================