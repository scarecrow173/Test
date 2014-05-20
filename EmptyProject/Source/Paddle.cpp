//=======================================================================================
//!	@file	:	Paddle.cpp
//!	@brief	:	Paddleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "Paddle.h"
#include "BoxFactory.h"
#include "TriangleRenderer.h"
#include "CollisionBox.h"
#include "Colors.h"
#include "Item.h"
#include "Stage1.h"
#include "Ball.h"

using namespace AK;
using namespace Graphics;
using namespace Collision;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Paddle::Paddle(INode* parent, Vector3 pos)
	:	GameObject	(parent, pos)
	,	m_Item		(NULL)
	,	m_Speed		(3.f)
	,	m_Size		(1.f, 1.f, 1.f)
{
	static const F32 WIDTH	= 400.f;
	static const F32 HEIGHT	= 80.f;

	std::vector<U32> indexSrc;
	IndexData indexData;
	indexData = BoxFactory::GetInstance()->CreateBox(Vector3(0, 0, 0), Vector3(WIDTH, HEIGHT, 50.f), ARGBColors::Magenta, indexSrc);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->Initialize(DXUTGetD3D9Device());
	m_Renderer->AddIndex(indexSrc);
	m_Renderer->ReCreateIndexBuffer();
	m_Renderer->UpdateIndexData(indexData);

	Matrix mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);

	m_Renderer->SetWorld(mat);

	m_Collision = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), WIDTH, HEIGHT, 50.f);
	m_Collision->SetReflection(true);
	m_Collision->SetAttenuation(true);
	m_Collision->SetAttenuationFactor(0.91f);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Paddle::~Paddle()
{}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: 更新
//-------------------------------------------------------------
void Paddle::Update()
{
	TRACE(1, "Paddle::Update");
	m_Keyboard.Update();

	std::vector<ICollisionObject*> l_list;
	m_Collision->Update(l_list);

	Move();


}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Paddle::Start()
{
}
//-------------------------------------------------------------
//!	@brief		: 効果付け
//!	@param[in]	: 効果オブジェクト
//-------------------------------------------------------------
void Paddle::Affect(GameObject* obj)
{
	Item* item = dynamic_cast<Item*>(obj);
	if (!item)
		return;
	CollisionBox* box = static_cast<CollisionBox*>(m_Collision);
	Ball* ball = static_cast<Stage1*>(m_Parent)->GetBall();
	const F32 width = box->GetWidth();
	Vector3 pos		= box->GetPosition();

	switch (item->GetType())
	{
	case POWER_UP:
		ball->SetPowerup(true);
		break;
	case SPEED_UP:
		m_Speed *= 1.1f;
		break;
	case SPEED_DOWN:
		m_Speed *= 0.9f;
		break;
	case EXTEND_PADLLE:
		m_Size.x *= 1.1f;
		pos.x -= ((width - width * 1.1f) * 0.5f);
		box->SetPosition(pos);
		box->SetWidth(width * 1.1f);
		break;
	default:
		break;
	}

}
//-------------------------------------------------------------
//!	@brief		: 左右の移動値セット（上下には動かない）
//!	@param[in]	: example
//-------------------------------------------------------------
void Paddle::SetSpeed(const F32 speed)
{
	m_Speed = speed;
}
//-------------------------------------------------------------
//!	@brief		: 移動値取得
//-------------------------------------------------------------
F32	Paddle::GetSpeed() const
{
	return m_Speed;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: マトリクスで移動と拡大率変更
//-------------------------------------------------------------
void Paddle::Move()
{
	Vector3 speed = m_Collision->GetSpeed();

	if (m_Keyboard.IsKeyDown(KEY_LEFT))
		speed.x += m_Speed;
	if (m_Keyboard.IsKeyDown(KEY_RIGHT))
		speed.x -= m_Speed;

	m_Collision->SetSpeed(speed);

	m_Position = m_Collision->GetPosition();
	Matrix translation, scale;
	D3DXMatrixTranslation(&translation, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixScaling(&scale, m_Size.x, m_Size.y, m_Size.z);
	m_Renderer->SetWorld(scale * translation);
}
//===============================================================
//	End of File
//===============================================================
