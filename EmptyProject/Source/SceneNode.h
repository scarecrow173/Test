//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "INode.h"
namespace AK
{


//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SceneNode : public INode
{
public:
	SceneNode(INode* parent) : INode(parent) {};
	virtual ~SceneNode(){};

	RTTI_IS_A(SceneNode);
	virtual void		Update()		PURE;
	virtual SceneNode*	NextScene()		PURE;
	virtual bool		Initialize()	PURE;

protected:

private:

};


};
//===============================================================
//	End of File
//===============================================================