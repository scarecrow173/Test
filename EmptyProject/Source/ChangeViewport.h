//=======================================================================================
//!	@file	:	ChangeViewport.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsShaderObject.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	ChangeViewport
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ChangeViewport : public AbsShaderObject
{
public:
	ChangeViewport();
	virtual ~ChangeViewport();

	virtual void	Draw();
	virtual bool	Initilize();

	void			ChangeViewprot();

	void			SetViewport(const D3DVIEWPORT9& viewport);
	D3DVIEWPORT9	GetViewport() const;

	void			SetDrawStep(const U32 drawstep);


private:
	D3DVIEWPORT9	m_Viewprot;
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================