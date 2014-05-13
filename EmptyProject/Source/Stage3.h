//=======================================================================================
//!	@file	:	Stage3.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
namespace AK
{


//=======================================================================================
//!	@class	:	Stage3
//!	@brief	:	Stage3�V�[��
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Stage3: public SceneNode
{
public:
	Stage3(INode* parent);
	virtual ~Stage3();

	void		Update();
	SceneNode*	ChangeScene();
	bool		Initialize();

protected:

private:

};


};
//===============================================================
//	End of File
//===============================================================