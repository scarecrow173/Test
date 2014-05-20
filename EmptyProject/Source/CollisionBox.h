//=======================================================================================
//!	@file	:	CollisionBox.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "ICollisionObject.h"
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
class CollisionBox : public ICollisionObject
{
public:
	friend CollisionSphere;

	CollisionBox();
	CollisionBox(Vector3 positon, Vector3 center, Vector3 speed, F32 width, F32 height, F32 depth);
	virtual ~CollisionBox();

	bool	Check(ICollisionObject* obj);
	bool	Check(CollisionBox* box);
	bool	Check(CollisionSphere* sphere);

	void	GetCollisionPos(Vector3& max, Vector3& min);


	F32		GetWidth()	const;
	F32		GetHeight()	const;
	F32		GetDepth()	const;
	Vector3	GetCenter()	const;

	void	SetWidth(const F32 width);
	void	SetHeight(const F32 height);
	void	SetDepth(const F32 depth);
	void	SetCenter(const Vector3 center);

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