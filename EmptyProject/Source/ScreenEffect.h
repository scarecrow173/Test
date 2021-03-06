//=======================================================================================
//!	@file	:	ScreenEffect.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsShaderObject.h"
#include "Elements.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	ScreenEffect
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ScreenEffect : public AbsShaderObject
{
public:
	ScreenEffect();
	virtual ~ScreenEffect();

	RTTI_IS_A(ScreenEffect);

	virtual bool	Initilize();
	virtual void	Draw();

	F32				GetFadeValue() const;
	VertexFloat3	GetFadeColor() const;
	void			SetFadeValue(const F32 alpha);
	void			SetFadeColor(const VertexFloat3& color);

protected:

private:
	D3DXHANDLE		m_hFadeValue;
	D3DXHANDLE		m_hFadeColor;
	F32				m_FadeValue;
	VertexFloat3	m_FadeColor;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================