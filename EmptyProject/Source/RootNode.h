//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "INode.h"

namespace AK
{
class SceneNode;

//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class RootNode : public INode
{
public:
	static RootNode*	Create();
	static void			Destroy();
	static RootNode*	GetInstance();


	virtual void		Update();
	

private:
	RootNode();
	virtual ~RootNode();

	static RootNode*	m_Instance;

	SceneNode*			m_NowScene;
	F32					m_Time;

};
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline RootNode* RootNode::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}

};
//===============================================================
//	End of File
//===============================================================