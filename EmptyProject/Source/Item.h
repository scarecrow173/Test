//=======================================================================================
//!	@file	:	Item.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include "GameObject.h"
#include "Paddle.h"
namespace AK
{
enum ITEM_TYPE
{
	POWER_UP = 0,
	SPEED_UP,
	SPEED_DOWN,
	EXTEND_PADLLE
};
//=======================================================================================
//!	@class	:	Item
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Item : public GameObject
{
public:
	Item(Paddle* parent, Vector3 pos, ITEM_TYPE type);
	virtual ~Item();

	virtual void	Update();
	virtual void	Start();

	void	ItemAffect(GameObject* obj);

protected:

private:
	ITEM_TYPE	m_Type;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================