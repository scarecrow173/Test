//=======================================================================================
//!	@file	:	Stage1.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
namespace AK
{
namespace Graphics{class IShaderObject;}; 
class BlockSystem;
//=======================================================================================
//!	@class	:	Stage1
//!	@brief	:	Stage1ÉVÅ[Éì
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Stage1: public SceneNode
{
public:
	Stage1(INode* parent);
	virtual ~Stage1();

	void		Update();
	SceneNode*	ChangeScene();
	bool		Initialize();
	bool		IsEnd();
	void		SetEnd(bool end);
protected:

private:
	bool						m_IsEnd;
	Graphics::IShaderObject*	m_Shader;
	BlockSystem*				m_BlockSystem;

};


};
//===============================================================
//	End of File
//===============================================================