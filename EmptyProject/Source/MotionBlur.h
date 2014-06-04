//=======================================================================================
//!	@file	:	MotionBlur.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "IShaderObject.h"
#include "Elements.h"
#include "DefaultTexture.h"
#include "WindowPolygonRenderer.h"
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
class MotionBlur : public IShaderObject
{
public:
	MotionBlur();
	virtual ~MotionBlur();

	RTTI_IS_A(MotionBlur);

	virtual bool	Initilize();
	virtual void	Draw();

//	void						SetShaderTechniqueByName(const std::string& techniqueName);
private:


	RefCountedObjectPtr			m_BlurringTextureObjectPtr;
	RefCountedObjectPtr			m_VelocityMapObjectPtr;
	DefaultTexture*				m_BlurringTexture;
	DefaultTexture*				m_VelocityMap;
	IDirect3DSurface9*			m_BlurringSurface;
	IDirect3DSurface9*			m_VelocitySurface;
	IDirect3DSurface9*			m_BlurringDepthSurface;

	D3DXHANDLE					m_hPrevWorld;
	Matrix						m_PrevWorld;
	
	WindowPolygonRenderer*		m_PostProcessingRenderer;
	U32							m_WriteTextureSize;
	std::vector<IShaderObject*>	m_AffectedShaders;
	
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