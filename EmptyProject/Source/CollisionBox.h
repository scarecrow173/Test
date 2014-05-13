//=======================================================================================
//!	@file	:	CollisionBox.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "ICollisonObject.h"
#include "MyMath.h"
#include "DebugUtill.h"
namespace AK
{
namespace Collision
{
//=======================================================================================
//!	@class	:	CollisionBox
//!	@brief	:	è’ìÀå`èÛî†
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class CollisionBox : public ICollisonObject
{
public:
	friend CollisionSphere;

	CollisionBox();
	CollisionBox(Vector3 positon, Vector3 center, Vector3 speed, F32 width, F32 height, F32 depth);
	virtual ~CollisionBox();

	bool	Check(ICollisonObject* obj);
	bool	Check(CollisionBox* box);
	bool	Check(CollisionSphere* sphere);

	void	GetCollisionPos(Vector3& max, Vector3& min);


	F32		GetWidth();
	F32		GetHeight();
	F32		GetDepth();
	Vector3	GetCenter();

	void	SetWidth(F32 width);
	void	SetHeight(F32 height);
	void	SetDepth(F32 depth);
	void	SetCenter(Vector3 center);

private:
	void	_AssretError();

	F32		m_Width;
	F32		m_Height;
	F32		m_Depth;
	

	
};

};
};
//===============================================================
//	End of File
//===============================================================