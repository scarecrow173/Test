//=======================================================================================
//!	@file	:	Paddle.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/05/08
//=======================================================================================
#pragma once
#include "GameObject.h"
#include "InputKeyboard.h"
namespace AK
{
class Item;
class Ball;
//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Paddle : public GameObject
{
public:
	Paddle(AbsNode* parent, Vector3 pos);
	virtual ~Paddle();

	RTTI_IS_A(Paddle);
	virtual void	Update();
	virtual void	Start();
	virtual void	Affect(GameObject* obj);
	void			SetSpeed(const F32 speed);
	F32				GetSpeed() const;


private:
	void			Move();
	void			PowerUp();
	void			SpeedUp();
	void			SpeedDown();
	void			ExpandPadlle();


	InputKeyboard	m_Keyboard;
	Item*			m_Item;
	F32				m_Speed;
	Vector3			m_Size;
	U32				m_CurrentSpeedMode;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================