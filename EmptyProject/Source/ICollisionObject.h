//=======================================================================================
//!	@file	:	ICollisionObject.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "MyMath.h"
#include "DebugUtill.h"
namespace AK
{
namespace Collision
{
class CollisionBox;
class CollisionSphere;
//=======================================================================================
//!	@class	:	ICollisionObject
//!	@brief	:	コリジョン用インターフェース
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ICollisionObject
{
public:
	ICollisionObject();
	ICollisionObject(Vector3 position, Vector3 center, Vector3 speed);
	virtual ~ICollisionObject();

	void Update(std::vector<ICollisionObject*>& collision);
	void Update();
	
	virtual bool Check(ICollisionObject* obj)PURE;
	virtual bool Check(CollisionBox* obj)	PURE;
	virtual bool Check(CollisionSphere* obj)PURE;
	virtual F32	 GetTime(ICollisionObject& obj);

	

	bool	IsActive()				const;
	bool	IsGravity()				const;
	bool	IsReflection()			const;
	bool	IsAttenuation()			const;
	Vector3	GetSpeed()				const;
	Vector3 GetPosition()			const;
	F32		GetReflectionFactor()	const;
	F32		GetAttenuationFactor()	const;

	void	SetActive(const bool active);
	void	SetGravity(const bool gravity);
	void	SetReflection(const bool reflection);
	void	SetAttenuation(const bool attenuation);
	void	SetSpeed(const Vector3 speed);
	void	SetPosition(const Vector3 position);
	void	SetReflectionFactor(const F32 reflection);
	void	SetAttenuationFactor(const F32 attenuation);
	void	PushCollisionList(ICollisionObject* obj);
	void	EraseCollisionList(const ICollisionObject* obj);
	Vector3		m_Normal;
protected:
	void AssertError();
	virtual void _AssretError(){};

	static U32	IDAssignment;
	static const F32 GRAVITY_POWER;

	bool		m_IsActive;
	bool		m_IsGravity;
	bool		m_IsReflection;
	bool		m_IsAttenuation;
	bool		m_IsHit;
	Vector3		m_Speed;
	Vector3		m_Position;
	Vector3		m_CenterPos;
	F32			m_ReflectionFactor;
	F32			m_AttenuationFactor;

	U32			m_ID;

	std::vector<ICollisionObject*> m_CollisionList;
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================