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
	Stage1(INode* parent, U32 stageCount);
	virtual ~Stage1();

	void		Update();
	SceneNode*	ChangeScene();
	bool		Initialize();
	bool		IsEnd();
	void		SetEnd(bool end);
protected:

private:
	static const U32			STAGE_MAX = 3;
	
	static std::string			StageDataPath[STAGE_MAX];
	bool						m_IsEnd;
	F32							m_FadeVolume;
	Graphics::IShaderObject*	m_Shader;
	BlockSystem*				m_BlockSystem;
	U32							m_StageCount;

};


};
//===============================================================
//	End of File
//===============================================================