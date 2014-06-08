//=======================================================================================
//!	@file	:	AbsCollisionObject.h
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
//!	@class	:	AbsCollisionObject
//!	@brief	:	コリジョン用インターフェース
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class AbsCollisionObject
{
public:
	AbsCollisionObject();
	AbsCollisionObject(Vector3 position, Vector3 center, Vector3 speed);
	virtual ~AbsCollisionObject();

	void Update(std::vector<AbsCollisionObject*>& collision);
	void Update();

	RTTI_IS_A_BASE(AbsCollisionObject);
	virtual bool Check(AbsCollisionObject* obj)	= 0;
	virtual bool Check(CollisionBox* obj)		= 0;
	virtual bool Check(CollisionSphere* obj)	= 0;
	virtual F32	 GetTime(AbsCollisionObject& obj);
	

	bool	IsActive()				const;
	bool	IsGravity()				const;
	bool	IsReflection()			const;
	bool	IsAttenuation()			const;
	Vector3	GetSpeed()				const;
	Vector3 GetPosition()			const;
	Vector3 GetClossetPoint()		const;
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
	void	PushCollisionList(AbsCollisionObject* obj);
	void	EraseCollisionList(const AbsCollisionObject* obj);
protected:
	void AssertError();
	virtual void _AssretError(){};	//	継承先で追加のアサート


	static const F32 GRAVITY_POWER;

	bool		m_IsActive;
	bool		m_IsGravity;
	bool		m_IsReflection;
	bool		m_IsAttenuation;
	bool		m_IsHit;
	Vector3		m_Speed;
	Vector3		m_Position;
	Vector3		m_CenterPos;
	Vector3		m_ClossetPoint;
	F32			m_ReflectionFactor;
	F32			m_AttenuationFactor;

	std::vector<AbsCollisionObject*> m_CollisionList;
};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================