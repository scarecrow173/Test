//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
//!	@brief		: コンストラクタ
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
//!	@brief		: デストラクタ
//-------------------------------------------------------------
ICollisionObject::~ICollisionObject()
{
	m_CollisionList.clear();
}
//-------------------------------------------------------------
//!	@brief		: 更新
//!	@param[in]	: 衝突したコリジョンの格納先
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
//!	@brief		: 更新(衝突考慮しない)
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
//!	@brief		: 衝突時間取得
//!	@param[in]	: 衝突先
//!	@return		: 衝突時間
//-------------------------------------------------------------
F32 ICollisionObject::GetTime(ICollisionObject& obj)
{
	Vector3 A = m_Position - obj.m_Position;
	Vector3 B = m_Speed - obj.m_Speed;
	return  (-(D3DXVec3Dot(&A, &B) / D3DXVec3Dot(&B, &B)));
}
//-------------------------------------------------------------
//!	@brief		: Activeフラグ取得
//!	@return		: Activeフラグ
//-------------------------------------------------------------
bool ICollisionObject::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: Gravityフラグ取得
//!	@return		: Gravityフラグ
//-------------------------------------------------------------
bool ICollisionObject::IsGravity() const
{
	return m_IsGravity;
}
//-------------------------------------------------------------
//!	@brief		: Reflectionフラグ取得
//!	@return		: Reflectionフラグ
//-------------------------------------------------------------
bool ICollisionObject::IsReflection() const
{
	return m_IsReflection;
}
//-------------------------------------------------------------
//!	@brief		: Reflectionフラグ取得
//!	@return		: Reflectionフラグ
//-------------------------------------------------------------
bool ICollisionObject::IsAttenuation() const
{
	return m_IsAttenuation;
}
//-------------------------------------------------------------
//!	@brief		: speed取得
//!	@return		: 移動値
//-------------------------------------------------------------
Vector3	ICollisionObject::GetSpeed() const
{
	return m_Speed;
}
//-------------------------------------------------------------
//!	@brief		: 座標取得
//!	@return		: 座標
//-------------------------------------------------------------
Vector3 ICollisionObject::GetPosition() const
{
	return m_Position;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数取得
//!	@return		: 反射係数
//-------------------------------------------------------------
F32	ICollisionObject::GetReflectionFactor()	const
{
	return m_ReflectionFactor;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数取得
//!	@return		: 反射係数
//-------------------------------------------------------------
F32	ICollisionObject::GetAttenuationFactor()	const
{
	return m_AttenuationFactor;
}
//-------------------------------------------------------------
//!	@brief		: activeフラグセット
//!	@param[in]	: activeフラグ
//-------------------------------------------------------------
void ICollisionObject::SetActive(const bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: gravityフラグセット
//!	@param[in]	: gravityフラグ
//-------------------------------------------------------------
void ICollisionObject::SetGravity(const bool gravity)
{
	m_IsGravity = gravity;
}
//-------------------------------------------------------------
//!	@brief		: reflectionフラグセット
//!	@param[in]	: reflectionフラグ
//-------------------------------------------------------------
void ICollisionObject::SetReflection(const bool reflection)
{
	m_IsReflection = reflection;
}
//-------------------------------------------------------------
//!	@brief		: reflectionフラグセット
//!	@param[in]	: reflectionフラグ
//-------------------------------------------------------------
void ICollisionObject::SetAttenuation(const bool attenuation)
{
	m_IsAttenuation = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: 速度セット
//!	@param[in]	: 速度
//-------------------------------------------------------------
void ICollisionObject::SetSpeed(const Vector3 speed)
{
	m_Speed = speed;
}
//-------------------------------------------------------------
//!	@brief		: 座標セット
//!	@param[in]	: 座標
//-------------------------------------------------------------
void ICollisionObject::SetPosition(const Vector3 position)
{
	m_Position = position;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数セット
//!	@param[in]	: 反射係数
//-------------------------------------------------------------
void ICollisionObject::SetReflectionFactor(const F32 reflection)
{
	m_ReflectionFactor = reflection;
}
//-------------------------------------------------------------
//!	@brief		: 反射係数セット
//!	@param[in]	: 反射係数
//-------------------------------------------------------------
void ICollisionObject::SetAttenuationFactor(const F32 attenuation)
{
	m_AttenuationFactor = attenuation;
}
//-------------------------------------------------------------
//!	@brief		: コリジョンペア追加
//!	@param[in]	: 追加したいコリジョン
//-------------------------------------------------------------
void ICollisionObject::PushCollisionList(ICollisionObject* obj)
{
	auto it = std::find(m_CollisionList.begin(), m_CollisionList.end(), obj);

	if (it == m_CollisionList.end())
		m_CollisionList.push_back(obj);
}
//-------------------------------------------------------------
//!	@brief		: コリジョンペア削除
//!	@param[in]	: 削除したいコリジョン
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
//!	@brief		: アサート
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
