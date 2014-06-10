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
	DOWN_CLEARFONT = 0,
	//DOWN_CLEARFONT,
	//DOWN_CLEARFONT,
	START_CLEAR_END,
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
	const Paddle*		GetPaddle(const U32 index = 0)		const;
	const Wall*			GetWall(const U32 index)			const;
	Ball*				GetBall(const U32 index = 0)		const;
	const Item*			GetItem(const U32 index = 0)		const;
	void				SetEnd(const bool end);
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

	void				StartStage();
	void				SlideInStageFont();
	void				StopStageFont();
	void				SlideOutStageFont();
	void				SlideInStartFont();
	void				StopStartFont();
	void				SlideOutStartFont();

	void				DownClearFont();
	//void				StageClear();


	void				SetChildrenActive(const bool active);



	static const U32				STAGE_MAX	= 3;
	static const U32				PADDLE_NUM	= 1;
	static const U32				WALL_NUM	= 4;
	static const U32				BALL_NUM	= 1;

	static std::string				StageDataPath[STAGE_MAX];
	bool							m_IsEnd;
	bool							m_IsGameOver;
	bool							m_IsStageClear;
	bool							m_IsGameClear;
	bool							m_IsFading;
	bool							m_IsFadeEnd;
	bool							m_IsStartStage;

	StageStartStep					m_StartStep;
	StageClearStep					m_ClearStep;

	F32								m_FadeVolume;
	Graphics::AbsShaderObject*		m_Shader;
	Graphics::ScreenEffect*			m_FadeShader;
	Graphics::AbsShaderObject*		m_Phong;
	Graphics::DefaultShader*		m_CookTorrance;
	Graphics::DrawFonts*			m_StageFont;
	Graphics::DrawFonts*			m_StartFont;
	Graphics::DrawFonts*			m_ClearFont;

	Graphics::WindowPolygonRenderer* m_FadeRenderer;
	U32								m_StageCount;

	BlockSystem*					m_BlockSystem;
	SafeArray<Paddle*, PADDLE_NUM> 	m_Paddle;
	SafeArray<Wall*, WALL_NUM>		m_Wall;
	ItemSystem*						m_ItemSystem;
	SafeArray<Ball*, BALL_NUM>		m_Ball;


	F32								m_StopCount;

};


};
//===============================================================
//	End of File
//===============================================================