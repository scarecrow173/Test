//=======================================================================================
//!	@file	:	PhongShader.h
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
//!	@class	:	PhongShader
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class PhongShader : public IShaderObject
{
public:
	PhongShader();
	virtual ~PhongShader();

	virtual bool	Initilize();
	virtual void	Draw();

	//F32				GetFadeValue() const;
	//VertexFloat3	GetFadeColor() const;
	//void			SetFadeValue(const F32 alpha);
	//void			SetFadeColor(const VertexFloat3& color);

	//void			Reset();

private:
	D3DXHANDLE		m_hMaterial;
	D3DXHANDLE		m_hWorld;
	D3DXHANDLE		m_hView;
	D3DXHANDLE		m_hProjection;
	D3DXHANDLE		m_hLightDir;
	D3DXHANDLE		m_hEyePos;
	//D3DXHANDLE		m_hFadeColor;
	//F32				m_FadeValue;
	//VertexFloat3	m_FadeColor;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================