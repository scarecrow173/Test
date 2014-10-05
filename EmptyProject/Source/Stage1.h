//=======================================================================================
//!	@file	:	Stage1.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
#include "MyMath.h"
#include "SafeArray.h"
#include "WindowPolygonRenderer.h"
#include "ScreenEffect.h"
#include "DefaultShader.h"
#include "DrawFonts.h"
#include "UIStepDefault.h"
#include "UIStepAdd.h"
#include "UITextureRenderer.h"
namespace AK
{
namespace Graphics{class AbsShaderObject;}; 
class BlockSystem;
class Ball;
class Wall;
class Paddle;
class Item;
class ItemSystem;

enum StageStartStep
{
	SLIDE_IN_STAGEFONT = 0,
	STOP_STAGEFONT,
	SLIDE_OUT_STAGEFONT,
	SLIDE_IN_STARTFONT,
	STOP_STARTFONT,
	SLIDE_OUT_STARTFONT,
	START_STAGE_END
};
enum StageClearStep
{
	START_STAGECLEAR = 0,
	DOWN_CLEARFONT,
	FADE_SCENE,
	//DOWN_CLEARFONT,
	//DOWN_CLEARFONT,
	STAGE_CLEAR_END,
};
//=======================================================================================
//!	@class	:	Stage1
//!	@brief	:	Stage1ÉVÅ[Éì
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Stage1: public SceneNode
{
public:
	Stage1(AbsNode* parent, U32 stageCount);
	virtual ~Stage1();

	RTTI_IS_A(Stage1);
	virtual void		Update();
	virtual SceneNode*	NextScene();
	virtual bool		Initialize();

	void				PopItem(Vector3 pos);

	
	bool				IsEnd()								const;
	bool				IsGameOver()						const;
	const Paddle*		GetPaddle(const U32 index = 0)		const;
	const Wall*			GetWall(const U32 index)			const;
	Ball*				GetBall(const U32 index = 0)		const;
	const Item*			GetItem(const U32 index = 0)		const;
	void				SetEnd(const bool end);
	void				SetGameOver(const bool gameOver);
	void				SetPaddle(Paddle* paddle, const U32 id = 0);
	void				SetWall(Wall* wall, const U32 id);
	void				SetBall(Ball* ball, const U32 id = 0);

private:
	void				StageClear();
	void				FadeScene();

	bool				CreateWall();
	bool				CreateBall();
	bool				CreatePadle();
	bool				CreateBlock();
	bool				CreateFont();
	bool				CreateFontArea();

	void				StartStage();
	void				SlideInStageFont();
	void				StopStageFont();
	void				SlideOutStageFont();
	void				SlideInStartFont();
	void				StopStartFont();
	void				SlideOutStartFont();

	void				StartStageClear();
	void				DownClearFont();

	void				UpdateScore();
	//void				StageClear();


	void				SetChildrenActive(const bool active);



	static const U32				STAGE_MAX	= 4;
	static const U32				PADDLE_NUM	= 1;
	static const U32				WALL_NUM	= 4;
	static const U32				BALL_NUM	= 1;

	static std::string				StageDataPath[STAGE_MAX];
	bool							m_IsEnd;
	bool							m_IsGameOver;
	bool							m_IsStageClear;
	bool							m_IsGameClear;
	bool							m_IsStartStage;

	StageStartStep					m_StartStep;
	StageClearStep					m_ClearStep;

	F32								m_FadeVolume;
	Graphics::AbsShaderObject*		m_Shader;
	Graphics::ScreenEffect*			m_FadeShader;
	Graphics::DefaultShader*		m_Simple;
	Graphics::DefaultShader*		m_CookTorrance;
	Graphics::DrawFonts*			m_LStageFont;
	Graphics::DrawFonts*			m_RStageFont;
	Graphics::DrawFonts*			m_StartFont;
	Graphics::DrawFonts*			m_ClearFont;
	Graphics::DrawFonts*			m_TimeFont;
	Graphics::DrawFonts*			m_TimeNumFont;
	Graphics::DrawFonts*			m_ScoreFont;
	Graphics::DrawFonts*			m_ScoreNumFont;
	Graphics::UIStepDefault*		m_OpacityStep;
	Graphics::UIStepAdd*			m_AddStep;
	Graphics::UITextureRenderer*	m_ScoreArea;

	Graphics::WindowPolygonRenderer* m_FadeRenderer;
	U32								m_StageCount;

	BlockSystem*					m_BlockSystem;
	SafeArray<Paddle*, PADDLE_NUM> 	m_Paddle;
	SafeArray<Wall*, WALL_NUM>		m_Wall;
	ItemSystem*						m_ItemSystem;
	SafeArray<Ball*, BALL_NUM>		m_Ball;


	F32								m_StopCount;
	U32								m_CrrentScore;

};


};
//===============================================================
//	End of File
//===============================================================