//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "ICollisonObject.h"
#include <algorithm>
using namespace AK;
using namespace Collision;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
U32	ICollisonObject::IDAssignment			= 0;
const F32 ICollisonObject::GRAVITY_POWER	= 0.05f;

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
ICollisonObject::ICollisonObject()
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
ICollisonObject::ICollisonObject(Vector3 position, Vector3 center, Vector3 speed)
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
ICollisonObject::~ICollisonObject()
{
	m_CollisonList.clear();
}
//-------------------------------------------------------------
//!	@brief		: �X�V
//!	@param[in]	: �Փ˂����R���W�����̊i�[��
//-------------------------------------------------------------
void ICollisonObject::Update(std::vector<ICollisonObject*>& collision)
{
	F32 speedFactor = 1.f;
	Vector3 v1;
	for (auto it = m_CollisonList.begin(); it != m_CollisonList.end(); ++it)
	{
		if ((*it)->m_IsActive && (*it)->Check(this))
		{
			m_IsHit = true;
			collision.emplace_back(*it);
			DEBUG_PRINT_CHAR("HIT!!");
			F32 t = GetTime(*(*it));
			speedFactor = (t >= 0.f && t <= 1.f) ? t : 1.f;

			auto v2 = m_Position - (*it)->m_Position;
			v1 = m_Position - (m_Position + (m_Speed * speedFactor));
			if (abs(v2.x) > abs(v2.y))
			{
				v1.y = 0.f;
				v1.z = 0.f;
			}
			else
			{
				v1.x = 0.f;
				v1.z = 0.f;
			}
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
		
		CalcParticlePlaneAfterPos(
			&m_Position,
			&velo,
			1.1f,
			speedFactor,
			&v1,
			&m_Position,
			&m_Speed);
		
		m_Speed.z = 0.0f;
		if (abs(m_Speed.x) > 0.1f)
		{
			m_Speed.x = (m_Speed.x > 0.f) ? 0.1f : -0.1f;
		}
		if (abs(m_Speed.y) > 0.1f)
		{
			m_Speed.y = (m_Speed.y > 0.f) ? 0.1f : -0.1f;
		}
	}
	m_IsHit = false;
}
//-------------------------------------------------------------
//!	@brief		: �X�V(�Փˍl�����Ȃ�)
//-------------------------------------------------------------
void ICollisonObject::Update()
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
F32 ICollisonObject::GetTime(ICollisonObject& obj)
{
	Vector3 A = m_Position - obj.m_Position;
	Vector3 B = m_Speed - obj.m_Speed;
	return  (-(D3DXVec3Dot(&A, &B) / D3DXVec3Dot(&B, &B)));
}
//-------------------------------------------------------------
//!	@brief		: Active�t���O�擾
//!	@return		: Active�t���O
//-------------------------------------------------------------
bool ICollisonObject::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: Gravity�t���O�擾
//!	@return		: Gravity�t���O
//-------------------------------------------------------------
bool ICollisonObject::IsGravity() const
{
	return m_IsGravity;
}
//-------------------------------------------------------------
//!	@brief		: Reflection�t���O�擾
//!	@return		: Reflection�t���O
//-------------------------------------------------------------
bool ICollisonObject::IsReflection() const
{
	return m_IsReflection;
}
//-------------------------------------------------------------
//!	@brief		: Reflection�t���O�擾
//!	@return		: Reflection�t���O
//-------------------------------------------------------------
bool ICollisonObject::IsAttenuation() const
{
	return m_IsAttenuation;
}
//-------------------------------------------------------------
//!	@brief		: speed�擾
//!	@return		: �ړ��l
//-------------------------------------------------------------
Vector3	ICollisonObject::GetSpeed() const
{
	return m_Speed;
}
//-------------------------------------------------------------
//!	@brief		: ���W�擾
//!	@return		: ���W
//-------------------------------------------------------------
Vector3 ICollisonObject::GetPosition() const
{
	return m_Position;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���擾
//!	@return		: ���ˌW��
//-------------------------------------------------------------
F32	ICollisonObject::GetReflectionFactor()	const
{
	return m_ReflectionFactor;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���擾
//!	@return		: ���ˌW��
//-------------------------------------------------------------
F32	ICollisonObject::GetAttenuationFactor()	const
{
	return m_AttenuationFactor;
}
//-------------------------------------------------------------
//!	@brief		: active�t���O�Z�b�g
//!	@param[in]	: active�t���O
//-------------------------------------------------------------
void ICollisonObject::SetActive(bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: gravity�t���O�Z�b�g
//!	@param[in]	: gravity�t���O
//-------------------------------------------------------------
void ICollisonObject::SetGravity(bool gravity)
{
	m_IsGravity = gravity;
}
//-------------------------------------------------------------
//!	@brief		: reflection�t���O�Z�b�g
//!	@param[in]	: reflection�t���O
//-------------------------------------------------------------
void ICollisonObject::SetReflection(bool reflection)
{
	m_IsReflection = reflection;
}
//-------------------------------------------------------------
//!	@brief		: reflection�t���O�Z�b�g
//!	@param[in]	: reflection�t���O
//-------------------------------------------------------------
void ICollisonObject::SetAttenuation(bool attenuation)
{
	m_IsAttenuation = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: ���x�Z�b�g
//!	@param[in]	: ���x
//-------------------------------------------------------------
void ICollisonObject::SetSpeed(Vector3 speed)
{
	m_Speed = speed;
}
//-------------------------------------------------------------
//!	@brief		: ���W�Z�b�g
//!	@param[in]	: ���W
//-------------------------------------------------------------
void ICollisonObject::SetPosition(Vector3 position)
{
	m_Position = position;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���Z�b�g
//!	@param[in]	: ���ˌW��
//-------------------------------------------------------------
void ICollisonObject::SetReflectionFactor(F32 reflection)
{
	m_ReflectionFactor = reflection;
}
//-------------------------------------------------------------
//!	@brief		: ���ˌW���Z�b�g
//!	@param[in]	: ���ˌW��
//-------------------------------------------------------------
void ICollisonObject::SetAttenuationFactor(F32 attenuation)
{
	m_AttenuationFactor = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: �R���W�����y�A�ǉ�
//!	@param[in]	: �ǉ��������R���W����
//-------------------------------------------------------------
void ICollisonObject::PushCollisonList(ICollisonObject* obj)
{
	auto it = std::find(m_CollisonList.begin(), m_CollisonList.end(), obj);

	if (it == m_CollisonList.end())
		m_CollisonList.push_back(obj);
}
//-------------------------------------------------------------
//!	@brief		: �R���W�����y�A�폜
//!	@param[in]	: �폜�������R���W����
//-------------------------------------------------------------
void ICollisonObject::EraseCollisonList(ICollisonObject* obj)
{
	auto it = std::find(m_CollisonList.begin(), m_CollisonList.end(), obj);

	if (it == m_CollisonList.end())
		return;

	m_CollisonList.erase(it);
}
//=======================================================================================
//		protected method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �A�T�[�g
//-------------------------------------------------------------
void ICollisonObject::AssertError()
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