//=======================================================================================
//!	@file	:	CollisionSphere.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsCollisionObject.h"
#include "DebugUtill.h"
namespace AK
{
namespace Collision
{
//=======================================================================================
//!	@class	:	CollisionSphere
//!	@brief	:	�Փˌ`��
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class CollisionSphere : public AbsCollisionObject
{
public:
	friend CollisionBox;

	CollisionSphere();
	CollisionSphere(Vector3 position, Vector3 center, Vector3 speed, F32 radius);

	virtual ~CollisionSphere();
	
	RTTI_IS_A(CollisionBox);
	virtual bool Check(AbsCollisionObject* obj);
	virtual bool Check(CollisionBox* box);
	virtual bool Check(CollisionSphere* sphere);
	virtual F32	 GetTime(AbsCollisionObject& obj);

	F32	 GetRadius() const {return m_Radius;}

private:
	virtual void _AssretError();

	F32	m_Radius;
};

};
};
//===============================================================
//	End of File
//===============================================================