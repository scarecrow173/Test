//=======================================================================================
//!	@file	:	IResource.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "RefCountedObject.h"
namespace AK
{

//=======================================================================================
//!	@class	:	IResource
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class IResource//	: public RefCountedObject
{
public:
	virtual IResource* Clone() PURE;
protected:

};
//=======================================================================================
//		inline method
//=======================================================================================
};
//===============================================================
//	End of File
//===============================================================