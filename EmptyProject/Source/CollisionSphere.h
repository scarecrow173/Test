//=======================================================================================
//!	@file	:	CollisionSphere.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "ICollisionObject.h"
#include "DebugUtill.h"
namespace AK
{
namespace Collision
{
//=======================================================================================
//!	@class	:	CollisionSphere
//!	@brief	:	è’ìÀå`èÛãÖ
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class CollisionSphere : public ICollisionObject
{
public:
	friend CollisionBox;

	CollisionSphere();
	CollisionSphere(Vector3 position, Vector3 center, Vector3 speed, F32 radius);

	virtual ~CollisionSphere();
	
	RTTI_IS_A(CollisionBox);
	virtual bool Check(ICollisionObject* obj);
	virtual bool Check(CollisionBox* box);
	virtual bool Check(CollisionSphere* sphere);
	virtual F32	 GetTime(ICollisionObject& obj);

	F32	 GetRadius() const {return m_Radius;}

private:
	void _AssretError();

	F32	m_Radius;
};

};
};
//===============================================================
//	End of File
//===============================================================