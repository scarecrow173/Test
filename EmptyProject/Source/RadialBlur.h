//=======================================================================================
//!	@file	:	RadialBlur.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsShaderObject.h"
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
class RadialBlur : public AbsShaderObject
{
public:
	RadialBlur();
	virtual ~RadialBlur();

	RTTI_IS_A(RadialBlur);

	virtual bool	Initilize();
	virtual void	Draw();

	void			SetShaderTechniqueByName(const std::string& techniqueName);
	void			AddBlurringTarget(AbsShaderObject* obj);
	
	void			SetBlurPower(const F32 power);
	F32				GetBlurPower() const;
	void			SetSamplingNum(const S32 sampling);
	S32				GetSamplingNum() const;
private:

	RefCountedObjectPtr			m_BlurringTextureObject;
	DefaultTexture*				m_BlurringTexture;
	IDirect3DSurface9*			m_BlurringSurface;
	IDirect3DSurface9*			m_BlurringDepthSurface;
	std::vector<AbsShaderObject*>	m_AffectedShaders;

	D3DXHANDLE					m_hBlurPower;
	D3DXHANDLE					m_hSamplingNum;

	U32							m_BlurringTextureWidth;
	U32							m_BlurringTextureHeight;

	F32							m_BluerPower;
	S32							m_SamplingNum;
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================