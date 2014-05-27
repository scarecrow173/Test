//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "ICollisionObject.h"
#include <algorithm>
#include "CollisionBox.h"
#include "CollisionSphere.h"
using namespace AK;
using namespace Collision;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
U32	ICollisionObject::IDAssignment			= 0;
const F32 ICollisionObject::GRAVITY_POWER	= 5.f;

void ClosestPtPoint(Vector3 *p, CollisionBox *b, Vector3 *q)
{
	D3DXVECTOR3 d = *p - b->GetPosition();
    *q = b->GetPosition();
    F32 dist;

	const Vector3 DIRECTION_X(1.f, 0.f, 0.f);
	
	dist = D3DXVec3Dot(&d, &DIRECTION_X);
	
	F32 Width	= b->GetWidth()		* 0.5f;
	F32 Height	= b->GetHeight()	* 0.5f;
	F32 Depth	= b->GetDepth()		* 0.5f;

	if(dist > Width)
	{
		dist = Width;
	}
	if(dist < -Width)
	{
		dist = -Width;
	}
	*q += dist * Vector3(1.f, 0.f, 0.f);

	const Vector3 DIRECTION_Y(0.f, 1.f, 0.f);
	dist = D3DXVec3Dot(&d, &DIRECTION_Y);

	if(dist > Height)
	{
		dist = Height;
	}
	if(dist < -Height)
	{
		dist = -Height;
	}
	*q += dist * Vector3(0.f, 1.f, 0.f);

	const Vector3 DIRECTION_Z(0.f, 0.f, 1.f);
	dist = D3DXVec3Dot(&d, &DIRECTION_Z);

	if(dist > Depth)
	{
		dist = Depth;
	}
	if(dist < -Depth)
	{
		dist = -Depth;
	}
	*q += dist * Vector3(0.f, 0.f, 1.f);

}
bool CalcParticlePlaneAfterPos(
   Vector3* colliPos,
   Vector3* velo,
   F32 res,
   F32 time,
   Vector3* normal,
   Vector3* out_pos,
   Vector3* out_velo
)
{
   // ���ˌ㑬�x���Z�o
   D3DXVECTOR3 N;
   D3DXVec3Normalize(&N, normal);
   (*out_velo) = (*velo) - (1 + res) * D3DXVec3Dot(&N, velo) * N;

   // �ړ��ʒu���v�Z
   (*out_pos) = (*colliPos) + (*out_velo) * time;

   return true;
}
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
ICollisionObject::ICollisionObject()
	:	m_IsActive			(true)
	,	m_IsGravity			(false)
	,	m_IsReflection		(false)
	,	m_IsAttenuation		(false)
	,	m_IsHit				(false)
	,	m_Speed				(Math::F32_MAX, Math::F32_MAX, Math::F32_MAX)
	,	m_Position			(Math::F32_MAX, Math::F32_MAX, Math::F32_MAX)
	,	m_CenterPos			(Math::F32_MAX, Math::F32_MAX, Math::F32_MAX)
	,	m_ReflectionFactor	(1.f)
	,	m_AttenuationFactor	(0.8f)
	,	m_ID				(IDAssignment++)
{

}
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
ICollisionObject::ICollisionObject(Vector3 position, Vector3 center, Vector3 speed)
	:	m_IsActive			(true)
	,	m_IsGravity			(false)
	,	m_IsReflection		(false)
	,	m_IsAttenuation		(false)
	,	m_IsHit				(false)
	,	m_Speed				(speed)
	,	m_Position			(position)
	,	m_CenterPos			(center)
	,	m_ReflectionFactor	(1.f)
	,	m_AttenuationFactor	(0.8f)
	,	m_ID				(IDAssignment++)
{

}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
ICollisionObject::~ICollisionObject()
{
	m_CollisionList.clear();
}
//-------------------------------------------------------------
//!	@brief		: �X�V
//!	@param[in]	: �Փ˂����R���W�����̊i�[��
//-------------------------------------------------------------
void ICollisionObject::Update(std::vector<ICollisionObject*>& collision)
{
	F32 speedFactor = 1.f;
	Vector3 v1;
	for (auto it = m_CollisionList.begin(); it != m_CollisionList.end(); ++it)
	{
		if ((*it)->m_IsActive && (*it)->Check(this))
		{
			m_IsHit = true;
			collision.emplace_back(*it);
			auto v2 = m_Position;
			auto box = dynamic_cast<CollisionBox*>(*it);
			if (box)
				ClosestPtPoint(&v2, box, &v1);
			else
				v1 = m_Position - (m_Position + (m_Speed * speedFactor));

			(*it)->m_Normal = v1;
			v1 = m_Position - v1;
			m_Normal = v1;

			F32 t = GetTime(*(*it));
			speedFactor = (t >= 0.f && t <= 1.f) ? t : 1.f;
			
			D3DXVec3Normalize(&v1, &v1);
		}
	}

	if (m_IsGravity)
		m_Position.y -= GRAVITY_POWER;
	
	m_Speed = m_IsAttenuation ? (m_Speed * m_AttenuationFactor) : m_Speed;
	
	m_Position += m_Speed * speedFactor;
	
	if (m_IsHit && m_IsReflection)
	{
		Vector3 velo = m_Speed;
		
		CalcParticlePlaneAfterPos(&m_Position, &velo, 1.1f, speedFactor,
			&v1, &m_Position, &m_Speed);
		
		m_Speed.z = 0.0f;
		if (abs(m_Speed.x) > 15.f)
		{
			m_Speed.x = (m_Speed.x > 0.f) ? 15.f : -15.f;
		}
		if (abs(m_Speed.y) > 15.f)
		{
			m_Speed.y = (m_Speed.y > 0.f) ? 15.f : -15.f;
		}
	}
	m_IsHit = false;
}
//-------------------------------------------------------------
//!	@brief		: �X�V(�Փˍl�����Ȃ�)
//-------------------------------------------------------------
void ICollisionObject::Update()
{
	if (!m_IsActive)
		return;
	
	if (m_IsGravity)
		m_Position.y -= GRAVITY_POWER;

	m_Position += m_Speed;


}
//-------------------------------------------------------------
//!	@brief		: �Փˎ��Ԏ擾
//!	@param[in]	: �Փː�
//!	@return		: �Փˎ���
//-------------------------------------------------------------
F32 ICollisionObject::GetTime(ICollisionObject& obj)
{
	Vector3 A = m_Position - obj.m_Position;
	Vector3 B = m_Speed - obj.m_Speed;
	return  (-(D3DXVec3Dot(&A, &B) / D3DXVec3Dot(&B, &B)));
}
//-------------------------------------------------------------
//!	@brief		: Active�t���O�擾
//!	@return		: Active�t���O
//-------------------------------------------------------------
bool ICollisionObject::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: Gravity�t���O�擾
//!	@return		: Gravity�t���O
//-------------------------------------------------------------
bool ICollisionObject::IsGravity() const
{
	return m_IsGravity;
}
//-------------------------------------------------------------
//!	@brief		: Reflection�t���O�擾
//!	@return		: Reflection�t���O
//-------------------------------------------------------------
bool ICollisionObject::IsReflection() const
{
	return m_IsReflection;
}
//-------------------------------------------------------------
//!	@brief		: Reflection�t���O�擾
//!	@return		: Reflection�t���O
//-------------------------------------------------------------
bool ICollisionObject::IsAttenuation() const
{
	return m_IsAttenuation;
}
//-------------------------------------------------------------
//!	@brief		: speed�擾
//!	@return		: �ړ��l
//-------------------------------------------------------------
Vector3	ICollisionObject::GetSpeed() const
{
	return m_Speed;
}
//-------------------------------------------------------------
//!	@brief		: ���W�擾
//!	@return		: ���W
//-------------------------------------------------------------
Vector3 ICollisionObject::GetPosition() const
{
	return m_Position;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���擾
//!	@return		: ���ˌW��
//-------------------------------------------------------------
F32	ICollisionObject::GetReflectionFactor()	const
{
	return m_ReflectionFactor;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���擾
//!	@return		: ���ˌW��
//-------------------------------------------------------------
F32	ICollisionObject::GetAttenuationFactor()	const
{
	return m_AttenuationFactor;
}
//-------------------------------------------------------------
//!	@brief		: active�t���O�Z�b�g
//!	@param[in]	: active�t���O
//-------------------------------------------------------------
void ICollisionObject::SetActive(const bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: gravity�t���O�Z�b�g
//!	@param[in]	: gravity�t���O
//-------------------------------------------------------------
void ICollisionObject::SetGravity(const bool gravity)
{
	m_IsGravity = gravity;
}
//-------------------------------------------------------------
//!	@brief		: reflection�t���O�Z�b�g
//!	@param[in]	: reflection�t���O
//-------------------------------------------------------------
void ICollisionObject::SetReflection(const bool reflection)
{
	m_IsReflection = reflection;
}
//-------------------------------------------------------------
//!	@brief		: reflection�t���O�Z�b�g
//!	@param[in]	: reflection�t���O
//-------------------------------------------------------------
void ICollisionObject::SetAttenuation(const bool attenuation)
{
	m_IsAttenuation = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: ���x�Z�b�g
//!	@param[in]	: ���x
//-------------------------------------------------------------
void ICollisionObject::SetSpeed(const Vector3 speed)
{
	m_Speed = speed;
}
//-------------------------------------------------------------
//!	@brief		: ���W�Z�b�g
//!	@param[in]	: ���W
//-------------------------------------------------------------
void ICollisionObject::SetPosition(const Vector3 position)
{
	m_Position = position;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���Z�b�g
//!	@param[in]	: ���ˌW��
//-------------------------------------------------------------
void ICollisionObject::SetReflectionFactor(const F32 reflection)
{
	m_ReflectionFactor = reflection;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���Z�b�g
//!	@param[in]	: ���ˌW��
//-------------------------------------------------------------
void ICollisionObject::SetAttenuationFactor(const F32 attenuation)
{
	m_AttenuationFactor = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: �R���W�����y�A�ǉ�
//!	@param[in]	: �ǉ��������R���W����
//-------------------------------------------------------------
void ICollisionObject::PushCollisionList(ICollisionObject* obj)
{
	auto it = std::find(m_CollisionList.begin(), m_CollisionList.end(), obj);

	if (it == m_CollisionList.end())
		m_CollisionList.push_back(obj);
}
//-------------------------------------------------------------
//!	@brief		: �R���W�����y�A�폜
//!	@param[in]	: �폜�������R���W����
//-------------------------------------------------------------
void ICollisionObject::EraseCollisionList(const ICollisionObject* obj)
{
	auto it = std::find(m_CollisionList.begin(), m_CollisionList.end(), obj);

	if (it == m_CollisionList.end())
		return;

	m_CollisionList.erase(it);
}
//=======================================================================================
//		protected method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �A�T�[�g
//-------------------------------------------------------------
void ICollisionObject::AssertError()
{
	assert(m_Position.x != Math::F32_MAX);
	assert(m_Position.y != Math::F32_MAX);
	assert(m_Position.z != Math::F32_MAX);

	assert(m_Speed.x != Math::F32_MAX);
	assert(m_Speed.y != Math::F32_MAX);
	assert(m_Speed.z != Math::F32_MAX);

	assert(m_CenterPos.x != Math::F32_MAX);
	assert(m_CenterPos.y != Math::F32_MAX);
	assert(m_CenterPos.z != Math::F32_MAX);
	_AssretError();
}

//===============================================================
//	End of File
//===============================================================
