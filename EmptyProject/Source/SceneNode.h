//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsNode.h"
namespace AK
{


//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SceneNode : public AbsNode
{
public:
	SceneNode(AbsNode* parent) : AbsNode(parent) {};
	virtual ~SceneNode(){};

	RTTI_IS_A(SceneNode);
	virtual void		Update()		= 0;
	virtual SceneNode*	NextScene()		= 0;
	virtual bool		Initialize()	= 0;

protected:

private:

};


};
//===============================================================
//	End of File
//===============================================================