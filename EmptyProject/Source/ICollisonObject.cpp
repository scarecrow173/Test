//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
   // 反射後速度を算出
   D3DXVECTOR3 N;
   D3DXVec3Normalize(&N, normal);
   (*out_velo) = (*velo) - (1 + res) * D3DXVec3Dot(&N, velo) * N;

   // 移動位置を計算
   (*out_pos) = (*colliPos) + (*out_velo) * time;

   return true;
}
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
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
//!	@brief		: コンストラクタ
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
//!	@brief		: デストラクタ
//-------------------------------------------------------------
ICollisonObject::~ICollisonObject()
{
	m_CollisonList.clear();
}
//-------------------------------------------------------------
//!	@brief		: 更新
//!	@param[in]	: 衝突したコリジョンの格納先
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
//!	@brief		: 更新(衝突考慮しない)
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
//!	@brief		: 衝突時間取得
//!	@param[in]	: 衝突先
//!	@return		: 衝突時間
//-------------------------------------------------------------
F32 ICollisonObject::GetTime(ICollisonObject& obj)
{
	Vector3 A = m_Position - obj.m_Position;
	Vector3 B = m_Speed - obj.m_Speed;
	return  (-(D3DXVec3Dot(&A, &B) / D3DXVec3Dot(&B, &B)));
}
//-------------------------------------------------------------
//!	@brief		: Activeフラグ取得
//!	@return		: Activeフラグ
//-------------------------------------------------------------
bool ICollisonObject::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: Gravityフラグ取得
//!	@return		: Gravityフラグ
//-------------------------------------------------------------
bool ICollisonObject::IsGravity() const
{
	return m_IsGravity;
}
//-------------------------------------------------------------
//!	@brief		: Reflectionフラグ取得
//!	@return		: Reflectionフラグ
//-------------------------------------------------------------
bool ICollisonObject::IsReflection() const
{
	return m_IsReflection;
}
//-------------------------------------------------------------
//!	@brief		: Reflectionフラグ取得
//!	@return		: Reflectionフラグ
//-------------------------------------------------------------
bool ICollisonObject::IsAttenuation() const
{
	return m_IsAttenuation;
}
//-------------------------------------------------------------
//!	@brief		: speed取得
//!	@return		: 移動値
//-------------------------------------------------------------
Vector3	ICollisonObject::GetSpeed() const
{
	return m_Speed;
}
//-------------------------------------------------------------
//!	@brief		: 座標取得
//!	@return		: 座標
//-------------------------------------------------------------
Vector3 ICollisonObject::GetPosition() const
{
	return m_Position;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数取得
//!	@return		: 反射係数
//-------------------------------------------------------------
F32	ICollisonObject::GetReflectionFactor()	const
{
	return m_ReflectionFactor;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数取得
//!	@return		: 反射係数
//-------------------------------------------------------------
F32	ICollisonObject::GetAttenuationFactor()	const
{
	return m_AttenuationFactor;
}
//-------------------------------------------------------------
//!	@brief		: activeフラグセット
//!	@param[in]	: activeフラグ
//-------------------------------------------------------------
void ICollisonObject::SetActive(bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: gravityフラグセット
//!	@param[in]	: gravityフラグ
//-------------------------------------------------------------
void ICollisonObject::SetGravity(bool gravity)
{
	m_IsGravity = gravity;
}
//-------------------------------------------------------------
//!	@brief		: reflectionフラグセット
//!	@param[in]	: reflectionフラグ
//-------------------------------------------------------------
void ICollisonObject::SetReflection(bool reflection)
{
	m_IsReflection = reflection;
}
//-------------------------------------------------------------
//!	@brief		: reflectionフラグセット
//!	@param[in]	: reflectionフラグ
//-------------------------------------------------------------
void ICollisonObject::SetAttenuation(bool attenuation)
{
	m_IsAttenuation = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: 速度セット
//!	@param[in]	: 速度
//-------------------------------------------------------------
void ICollisonObject::SetSpeed(Vector3 speed)
{
	m_Speed = speed;
}
//-------------------------------------------------------------
//!	@brief		: 座標セット
//!	@param[in]	: 座標
//-------------------------------------------------------------
void ICollisonObject::SetPosition(Vector3 position)
{
	m_Position = position;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数セット
//!	@param[in]	: 反射係数
//-------------------------------------------------------------
void ICollisonObject::SetReflectionFactor(F32 reflection)
{
	m_ReflectionFactor = reflection;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数セット
//!	@param[in]	: 反射係数
//-------------------------------------------------------------
void ICollisonObject::SetAttenuationFactor(F32 attenuation)
{
	m_AttenuationFactor = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: コリジョンペア追加
//!	@param[in]	: 追加したいコリジョン
//-------------------------------------------------------------
void ICollisonObject::PushCollisonList(ICollisonObject* obj)
{
	auto it = std::find(m_CollisonList.begin(), m_CollisonList.end(), obj);

	if (it == m_CollisonList.end())
		m_CollisonList.push_back(obj);
}
//-------------------------------------------------------------
//!	@brief		: コリジョンペア削除
//!	@param[in]	: 削除したいコリジョン
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
//!	@brief		: アサート
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
