//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsNode.h"
#include "Scorer.h"
#include "StopWatch.h"

namespace AK
{
class SceneNode;

//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class RootNode : public AbsNode
{
public:
	static RootNode*	Create();
	static void			Destroy();
	static RootNode*	GetInstance();

	RTTI_IS_A(RootNode);
	virtual void		Update();

	bool				Initialize();
	
	Scorer*				GetScorer();
	StopWatch*			GetStopWatch();

private:
	RootNode();
	virtual ~RootNode();

	static RootNode*	m_Instance;

	SceneNode*			m_NowScene;

	StopWatch			m_StopWatch;
	Scorer				m_Score;

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