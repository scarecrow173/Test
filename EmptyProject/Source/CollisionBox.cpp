//=======================================================================================
//!	@file	:	CollisionBox.cpp
//!	@brief	:	CollisionBoxクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "CollisionBox.h"
#include "CollisionSphere.h"
using namespace AK;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
CollisionBox::CollisionBox()
	:	ICollisonObject	()
	,	m_Width			(Math::F32_MAX)
	,	m_Height		(Math::F32_MAX)
	,	m_Depth			(Math::F32_MAX)
{
}
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
CollisionBox::CollisionBox(Vector3 position, Vector3 center, Vector3 speed, F32 width, F32 height, F32 depth)
	:	ICollisonObject	(position, center, speed)
	,	m_Width			(width)
	,	m_Height		(height)
	,	m_Depth			(depth)
{

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
CollisionBox::~CollisionBox()
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
bool CollisionBox::Check(ICollisonObject* obj)
{
	AssertError();
	return obj->Check(this);
}
//-------------------------------------------------------------
//!	@brief		: AABBとAABB
//!	@param[in]	: 箱
//!	@return		: 衝突していればtrue
//-------------------------------------------------------------
bool CollisionBox::Check(CollisionBox* box)
{
	AssertError();

	//DEBUG_PRINT_CHAR("BOX → box");
		
	Vector3 max, min, otherMax, otherMin;

	Vector3 relativeSpeed = m_Speed - box->m_Speed;
	
	F32 t = GetTime(*box);

	relativeSpeed *= (t >= 0 && t<= 1.f) ? t : 1.f;
	
	this->GetCollisionPos(max, min);
	box->GetCollisionPos(otherMax, otherMin);

		

	return (min.x + relativeSpeed.x < otherMax.x && max.x  + relativeSpeed.x > otherMin.x)
		&& (min.y + relativeSpeed.y < otherMax.y && max.y  + relativeSpeed.y > otherMin.y)
		&& (min.z + relativeSpeed.z < otherMax.z && max.z  + relativeSpeed.z > otherMin.z);

}
//-------------------------------------------------------------
//!	@brief		: AABBと球
//!	@param[in]	: 球
//!	@return		: 衝突していればtrue
//-------------------------------------------------------------
bool CollisionBox::Check(CollisionSphere* sphere)
{
	AssertError();

	//DEBUG_PRINT_CHAR("BOX → sphere");

	Vector3 max, min;

	Vector3 relativeSpeed = m_Speed - sphere->m_Speed;

	F32 t = GetTime(*sphere);

	if (t >= 0 && t<= 1.f)
		relativeSpeed *= t;

	this->GetCollisionPos(max, min);


	return (min.x + relativeSpeed.x < sphere->m_Position.x + sphere->m_Radius && max.x  + relativeSpeed.x > sphere->m_Position.x - sphere->m_Radius)
		&& (min.y + relativeSpeed.y < sphere->m_Position.y + sphere->m_Radius && max.y  + relativeSpeed.y > sphere->m_Position.y - sphere->m_Radius)
		&& (min.z + relativeSpeed.z < sphere->m_Position.z + sphere->m_Radius && max.z  + relativeSpeed.z > sphere->m_Position.z - sphere->m_Radius);
};
//-------------------------------------------------------------
//!	@brief		: 最大位置を最小位置を取得
//!	@param[in]	: 最大位置格納先
//!	@param[in]	: 最小位置格納先
//-------------------------------------------------------------
void CollisionBox::GetCollisionPos(Vector3& max, Vector3& min)
{
	AssertError();

	F32 halfWidth	= m_Width * 0.5f;
	F32 halfHeight	= m_Height * 0.5f;
	F32 halfDepth	= m_Depth * 0.5f;

	max.x = (m_Position.x + m_CenterPos.x) + halfWidth;
	max.y = (m_Position.y + m_CenterPos.y) + halfHeight;
	max.z = (m_Position.z + m_CenterPos.z) + halfDepth;

	min.x = (m_Position.x + m_CenterPos.x) - halfWidth;
	min.y = (m_Position.y + m_CenterPos.y) - halfHeight;
	min.z = (m_Position.z + m_CenterPos.z) - halfDepth;
}
//-------------------------------------------------------------
//!	@brief		: 幅取得
//!	@return		: 幅
//-------------------------------------------------------------
F32	CollisionBox::GetWidth() const
{
	return m_Width;
}
//-------------------------------------------------------------
//!	@brief		: 高さ取得
//!	@return		: 高さ
//-------------------------------------------------------------
F32	CollisionBox::GetHeight() const
{
	return m_Height;
}
//-------------------------------------------------------------
//!	@brief		: 奥行き取得
//!	@return		: 奥行き
//-------------------------------------------------------------
F32	CollisionBox::GetDepth() const
{
	return m_Depth;
}
//-------------------------------------------------------------
//!	@brief		: 中心位置取得
//!	@return		: 中心位置
//-------------------------------------------------------------
Vector3	CollisionBox::GetCenter() const
{
	return m_CenterPos;
}
//-------------------------------------------------------------
//!	@brief		: 幅のセット
//!	@param[in]	: 幅
//-------------------------------------------------------------
void CollisionBox::SetWidth(const F32 width)
{
	m_Width = width;
}
//-------------------------------------------------------------
//!	@brief		: 高さセット
//!	@param[in]	: 高さ
//-------------------------------------------------------------
void CollisionBox::SetHeight(const F32 height)
{
	m_Height = height;
}
//-------------------------------------------------------------
//!	@brief		: 奥行きセット
//!	@param[in]	: 奥行き
//-------------------------------------------------------------
void CollisionBox::SetDepth(const F32 depth)
{
	m_Depth = depth;
}
//-------------------------------------------------------------
//!	@brief		: 中心位置セット
//!	@param[in]	: 中心位置
//-------------------------------------------------------------
void CollisionBox::SetCenter(const Vector3 center)
{
	m_CenterPos = center;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: アサート
//-------------------------------------------------------------
void CollisionBox::_AssretError()
{
	assert(m_Width	!= Math::F32_MAX);
	assert(m_Height != Math::F32_MAX);
	assert(m_Depth	!= Math::F32_MAX);
	
}
//===============================================================
//	End of File
//===============================================================