//=======================================================================================
//!	@file	:	RadialBlur.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IShaderObject.h"
#include "Elements.h"
#include "DefaultTexture.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	RadialBlur
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BlurFilter : public IShaderObject
{
public:
	BlurFilter();
	virtual ~BlurFilter();

	RTTI_IS_A(BlurFilter);

	virtual bool	Initilize();
	virtual void	Draw();

	void			SetShaderTechniqueByName(const std::string& techniqueName);
		std::vector<IShaderObject*>	m_AffectedShaders;
private:


	RefCountedObjectPtr			m_BlurringTextureObject;
	DefaultTexture*				m_BlurringTexture;
	IDirect3DSurface9*			m_BlurringSurface;
	IDirect3DSurface9*			m_BlurringDepthSurface;
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

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================