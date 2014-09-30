//=======================================================================================
//!	@file	:	Title.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
#include "AbsRenderer.h"
#include "RefCountedObjectPtr.h"
#include "AbsShaderObject.h"
#include "ScreenEffect.h"
#include "WindowPolygonRenderer.h"
#include "UIStepDefault.h"
#include "UIStepAdd.h"
#include "UITextureRenderer.h"
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
	Title(AbsNode* parent);
	virtual ~Title();

	RTTI_IS_A(Title);
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
	std::vector<Graphics::AbsRenderer*>	m_TitleBlock;
	Graphics::AbsShaderObject*			m_Shader;
	F32									m_Floating;

	Graphics::ScreenEffect*				m_FadeOutScreen;
	Graphics::WindowPolygonRenderer*	m_FadeOutRenderer;
	Graphics::UIStepDefault*			m_OpacityStep;
	Graphics::UITextureRenderer*		m_TitleText;

};


};
//===============================================================
//	End of File
//===============================================================