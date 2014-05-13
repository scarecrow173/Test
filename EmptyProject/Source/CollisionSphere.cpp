//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "CollisionSphere.h"
#include "CollisionBox.h"

using namespace AK;
using namespace Collision;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
CollisionSphere::CollisionSphere()
	:	ICollisonObject	()
	,	m_Radius		(Math::F32_MAX)
{
}
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
CollisionSphere::CollisionSphere(Vector3 position, Vector3 center, Vector3 speed, F32 radius)
	:	ICollisonObject	(position, center, speed)
	,	m_Radius		(radius)
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
CollisionSphere::~CollisionSphere()
{
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: でぃすぱっち(型を判別)
//!	@param[in]	: コリジョン
//!	@return		: 衝突していればtrue
//-------------------------------------------------------------
bool CollisionSphere::Check(ICollisonObject* obj)
{
	AssertError();
	return obj->Check(this);
}
//-------------------------------------------------------------
//!	@brief		: 球とAABB
//!	@param[in]	: 箱
//!	@return		: 衝突していればtrue
//-------------------------------------------------------------
bool CollisionSphere::Check(CollisionBox* box)
{
	AssertError();
	//DEBUG_PRINT_CHAR("SPHERE → box");
	
	Vector3 max, min;

	Vector3 relativeSpeed = box->m_Speed - m_Speed;

	F32 t = box->GetTime(*this);

	if (t >= 0 && t<= 1.f)
		relativeSpeed *= t;

	box->GetCollisionPos(max, min);

	return (min.x + relativeSpeed.x < m_Position.x + m_Radius && max.x  + relativeSpeed.x > m_Position.x -m_Radius)
		&& (min.y + relativeSpeed.y < m_Position.y + m_Radius && max.y  + relativeSpeed.y > m_Position.y -m_Radius)
		&& (min.z + relativeSpeed.z < m_Position.z + m_Radius && max.z  + relativeSpeed.z > m_Position.z -m_Radius);

}

//-------------------------------------------------------------
//!	@brief		: 球と球
//!	@param[in]	: 球
//!	@return		: 衝突していればtrue
//-------------------------------------------------------------
bool CollisionSphere::Check(CollisionSphere* sphere)
{
	AssertError();
	//DEBUG_PRINT_CHAR("SPHERE → sphere");

	Vector3 relativeSpeed = m_Speed - sphere->m_Speed;

	F32 t = GetTime(*sphere);

	if (t >= 0 && t<= 1.f)
		relativeSpeed *= t;
	
	return Math::Pow((m_Position.x + relativeSpeed.x) - sphere->m_Position.x, 2.f) 
		+ Math::Pow((m_Position.y + relativeSpeed.y) - sphere->m_Position.y, 2.f)
		+ Math::Pow((m_Position.z + relativeSpeed.z) - sphere->m_Position.z, 2.f) 
		<=  Math::Pow(m_Radius + sphere->m_Radius, 2.f);
	
};
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: アサート
//-------------------------------------------------------------
void CollisionSphere::_AssretError()
{
	assert(m_Radius != Math::F32_MAX);
}
//===============================================================
//	End of File
//===============================================================
