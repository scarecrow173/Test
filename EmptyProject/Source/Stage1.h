//=======================================================================================
//!	@file	:	Stage1.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "SceneNode.h"
#include "MyMath.h"
#include "SafeArray.h"

namespace AK
{
namespace Graphics{class IShaderObject;}; 
class BlockSystem;
class Ball;
class Wall;
class Paddle;
class Item;
class ItemSystem;
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



	static const U32				STAGE_MAX	= 3;
	static const U32				PADDLE_NUM	= 1;
	static const U32				WALL_NUM	= 4;
	static const U32				BALL_NUM	= 1;

	static std::string				StageDataPath[STAGE_MAX];
	bool							m_IsEnd;
	bool							m_IsGameOver;
	bool							m_IsStageClear;
	bool							m_WillFadeOut;
	F32								m_FadeVolume;
	Graphics::IShaderObject*		m_Shader;
	U32								m_StageCount;

	BlockSystem*					m_BlockSystem;
	SafeArray<Paddle*, PADDLE_NUM> 	m_Paddle;
	SafeArray<Wall*, WALL_NUM>		m_Wall;
	ItemSystem*						m_ItemSystem;
	SafeArray<Ball*, BALL_NUM>		m_Ball;


};


};
//===============================================================
//	End of File
//===============================================================