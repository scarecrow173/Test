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
//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Paddle : public GameObject
{
public:
	Paddle(INode* parent, Vector3 pos);
	virtual ~Paddle();

	virtual void	Update();
	virtual void	Start();
	void	PushItem(Item* item);
	void	SetSpeed(const F32 speed);
	F32		GetSpeed();
protected:

private:
	InputKeyboard	m_Keyboard;
	Item*			m_Item;
	F32				m_Speed;


};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================