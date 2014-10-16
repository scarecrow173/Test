//=======================================================================================
//!	@file	:	Title.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
#include "UITextureRenderer.h"
#include "ScreenEffect.h"
#include "WindowPolygonRenderer.h"
#include "UIStepDefault.h"
#include "NumberPlateRenderer.h"

namespace AK
{
	//=======================================================================================
	//!	@class	:	Title
	//!	@brief	:	タイトルシーンクラス
	//!	@par	:	example
	//!	@note	:	example
	//=======================================================================================
	class Result : public SceneNode
	{
	public:
		Result(AbsNode* parent, U32 _stageCount, F32 _time, U32 _score);
		virtual ~Result();

		RTTI_IS_A(Result);

		virtual void		Update();
		virtual SceneNode*	NextScene();
		virtual bool		Initialize();

	private:
		void				CheckBeginFade();
		void				FadeOutScene();
		U32					CalcSpring(U32 _current, const U32 _target);
		

		Graphics::ScreenEffect*				m_FadeOutScreen;
		Graphics::WindowPolygonRenderer*	m_FadeOutRenderer;
		Graphics::UITextureRenderer*		m_ResultText;
		Graphics::UITextureRenderer*		m_ScoreText;
		Graphics::UITextureRenderer*		m_TimeText;
		Graphics::UITextureRenderer*		m_ColonText;
		Graphics::NumberPlateRenderer*		m_ScoreNumber;
		Graphics::NumberPlateRenderer*		m_MinuteNumber;
		Graphics::NumberPlateRenderer*		m_SecNumber;

		Graphics::UIStepDefault*			m_OpacityStep;

		U32 m_Time;
		const U32 m_Minute;
		const U32 m_Sec;
		const U32 m_Score;

		U32 m_TmpTime;
		U32 m_CurrentMinute;
		U32 m_CurrentSec;
		U32 m_CurrentScore;
		U32 m_StageCount;

		F32									m_FadeVolume;
		bool								m_IsEnd;
		bool								m_IsFading;
	};


};
//===============================================================
//	End of File
//===============================================================