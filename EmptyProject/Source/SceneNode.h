//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	���R �l�\
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

	void				Update()PURE;
	virtual SceneNode*	ChangeScene()PURE;
	virtual bool		Initialize() PURE;

protected:

private:

};


};
//===============================================================
//	End of File
//===============================================================