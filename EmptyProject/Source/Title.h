//=======================================================================================
//!	@file	:	Title.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
#include "IRenderer.h"
#include "RefCountedObjectPtr.h"
#include "IShaderObject.h"
namespace AK
{
//=======================================================================================
//!	@class	:	Title
//!	@brief	:	タイトルシーンクラス
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Title: public SceneNode
{
public:
	Title(INode* parent);
	virtual ~Title();

	virtual void		Update();
	virtual SceneNode*	NextScene();
	virtual bool		Initialize();

private:
	void				CheckBeginFade();
	void				FadeOutScene();

	void				LoadTitleBlock();
	void				FloatingBlock();



	bool								m_IsEnd;
	bool								m_IsFading;

	F32									m_FadeVolume;
	std::vector<Graphics::IRenderer*>	m_TitleBlock;
	Graphics::IShaderObject*			m_Shader;
	F32									m_Floating;
};


};
//===============================================================
//	End of File
//===============================================================