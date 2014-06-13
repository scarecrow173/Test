//=======================================================================================
//!	@file	:	UITextureRenderer.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsRenderer.h"
#include "TextureAnimationController.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	UITextureRenderer
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class UITextureRenderer : public AbsRenderer
{
public:
	//UITextureRenderer(TextureAnimationController& info);
	UITextureRenderer(TextureAnimationController* info);
	virtual ~UITextureRenderer();

	virtual void	Draw();

private:
	DWORD							m_Color;
	TextureAnimationController*		m_TextureRect;
	D3DRENDERSTATETYPE				m_RenderState;


};
//=======================================================================================
//		inline method
//=======================================================================================
};
};
//===============================================================
//	End of File
//===============================================================