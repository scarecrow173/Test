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
#include "PrimitivePool.h"
#include "MaterialPool.h"
#include "TexturePool.h"

using namespace AK;
using namespace Graphics;
using namespace Collision;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
static const U32 SPEED_MODE_MAX = 6;
static const F32 SpeedMode[SPEED_MODE_MAX] = 
{
	1.f,
	1.5f,
	2.f,
	2.5f,
	3.f
};
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Paddle::Paddle(AbsNode* parent, Vector3 pos)
	:	GameObject			(parent, pos)
	,	m_Item				(NULL)
	,	m_Speed				(2.2f)
	,	m_Size				(1.f, 1.f, 1.f)
	,	m_CurrentSpeedMode	((SPEED_MODE_MAX / 2) - 1)
{
	static const F32 PADDLE_WIDTH	= 100.f;
	static const F32 PADDLE_HEIGHT	= 25.f;

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:BOX-Box01"));
	
	m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/Paddle.csv"));
	//TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/gra_effect_starAAlpha.png");

	m_Size.x = PADDLE_WIDTH;
	m_Size.y = PADDLE_HEIGHT;
	m_Size.z = 50.f;

	m_Transform = std::make_shared<TransformObject>(pos, m_Size);

	m_Renderer->SetTransform(m_Transform);

	m_Collision = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), PADDLE_WIDTH, PADDLE_HEIGHT, 50.f);
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

	std::vector<AbsCollisionObject*> l_list;
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
	Item* item			= RTTI_PTR_DYNAMIC_CAST(Item, obj);

	if (!item)
		return;

	switch (item->GetType())
	{
	case POWER_UP:
		PowerUp();
		break;
	case SPEED_UP:
		SpeedUp();
		break;
	case SPEED_DOWN:
		SpeedDown();
		break;
	case EXTEND_PADLLE:
		ExpandPadlle();
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

	m_Transform->SetTranslation(m_Collision->GetPosition());
	m_Transform->SetScaling(m_Size);

	m_Transform->UpdateTransform();
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Paddle::PowerUp()
{
	Stage1* stage		= RTTI_PTR_DYNAMIC_CAST(Stage1, m_Parent);
	assert(stage);
	stage->GetBall()->SetPowerup(true);
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Paddle::SpeedUp()
{
	m_CurrentSpeedMode += m_CurrentSpeedMode  < SPEED_MODE_MAX ? 1 : 0;
	m_Speed = SpeedMode[m_CurrentSpeedMode];
	//m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/PaddleSpeedUp.csv"));

}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Paddle::SpeedDown()
{
	m_CurrentSpeedMode -= m_CurrentSpeedMode  > 0 ? 1 : 0;
	m_Speed = SpeedMode[m_CurrentSpeedMode];
	//m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/PaddleSpeedDown.csv"));

}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Paddle::ExpandPadlle()
{
	CollisionBox* box	= RTTI_PTR_DYNAMIC_CAST(CollisionBox, m_Collision);
	assert(box);

	const F32 width		= box->GetWidth();
	Vector3 pos			= box->GetPosition();

	m_Size.x *= 1.1f;
	pos.x -= ((width - width * 1.1f) * 0.5f);
	box->SetPosition(pos);
	box->SetWidth(width * 1.1f);
}
//===============================================================
//	End of File
//===============================================================
