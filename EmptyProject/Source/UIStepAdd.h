//=======================================================================================
//!	@file	:	UIStepAdd.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsShaderObject.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	UIStepAdd
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class UIStepAdd : public AbsShaderObject
{
public:
	UIStepAdd();
	virtual ~UIStepAdd();

	RTTI_IS_A(UIStepAdd);
	virtual bool	Initilize();
	virtual void	Draw();

private:

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================