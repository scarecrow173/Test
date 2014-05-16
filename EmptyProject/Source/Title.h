//=======================================================================================
//!	@file	:	Title.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
#include "IRenderer.h"
#include "IShaderObject.h"
namespace AK
{
//=======================================================================================
//!	@class	:	Title
//!	@brief	:	�^�C�g���V�[���N���X
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Title: public SceneNode
{
public:
	Title(INode* parent);
	virtual ~Title();

	void Update();
	SceneNode*	ChangeScene();
	bool		Initialize();

private:
	bool		m_IsEnd;
	F32			m_FadeVolume;
	std::vector<Graphics::IRenderer*>	m_TitleBlock;
	Graphics::IShaderObject*			m_Shader;
	F32									m_Floating;
};


};
//===============================================================
//	End of File
//===============================================================