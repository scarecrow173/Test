//=======================================================================================
//!	@file	:	MotionBlur.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsShaderObject.h"
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
class MotionBlur : public AbsShaderObject
{
public:
	MotionBlur();
	virtual ~MotionBlur();

	RTTI_IS_A(MotionBlur);

	virtual bool	Initilize();
	virtual void	Draw();


	void			AddBlurringTarget(AbsShaderObject* obj);
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
	std::vector<AbsShaderObject*>	m_AffectedShaders;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================