//=======================================================================================
//!	@file	:	Title.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"

namespace AK
{
	//=======================================================================================
	//!	@class	:	Title
	//!	@brief	:	�^�C�g���V�[���N���X
	//!	@par	:	example
	//!	@note	:	example
	//=======================================================================================
	class Result : public SceneNode
	{
	public:
		Result(AbsNode* parent);
		virtual ~Result();

		RTTI_IS_A(Result);

		virtual void		Update();
		virtual SceneNode*	NextScene();
		virtual bool		Initialize();

	private:

	};


};
//===============================================================
//	End of File
//===============================================================