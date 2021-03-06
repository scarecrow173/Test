//=======================================================================================
//!	@file	:	Wall.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "GameObject.h"
namespace AK
{
enum WALL_TYPE
{
	WALL_LEFT = 0,
	WALL_RIGHT,
	WALL_TOP,
	WALL_BOTTOM,
};
//=======================================================================================
//!	@class	:	Wall
//!	@brief	:	��
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Wall : public GameObject
{
public:
	Wall(AbsNode* parent, Vector3 pos, WALL_TYPE type);
	virtual ~Wall();

	RTTI_IS_A(Wall);
	virtual void Update();

private:
	WALL_TYPE m_type;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================
