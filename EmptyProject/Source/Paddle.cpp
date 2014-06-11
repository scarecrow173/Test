//=======================================================================================
//!	@file	:	Paddle.cpp
//!	@brief	:	Paddle�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
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

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
Paddle::Paddle(AbsNode* parent, Vector3 pos)
	:	GameObject	(parent, pos)
	,	m_Item		(NULL)
	,	m_Speed		(3.f)
	,	m_Size		(1.f, 1.f, 1.f)
{
	static const F32 PADDLE_WIDTH	= 300.f;
	static const F32 PADDLE_HEIGHT	= 40.f;

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
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
Paddle::~Paddle()
{}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �X�V
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
//!	@brief		: ���ʕt��
//!	@param[in]	: ���ʃI�u�W�F�N�g
//-------------------------------------------------------------
void Paddle::Affect(GameObject* obj)
{
	Item* item			= RTTI_PTR_DYNAMIC_CAST(Item, obj);
	CollisionBox* box	= RTTI_PTR_DYNAMIC_CAST(CollisionBox, m_Collision);
	Stage1* stage		= RTTI_PTR_DYNAMIC_CAST(Stage1, m_Parent);

	if ((!item) || (!box) || (!stage))
		return;


	Ball* ball = stage->GetBall();
	
	const F32 width = box->GetWidth();
	Vector3 pos		= box->GetPosition();

	switch (item->GetType())
	{
	case POWER_UP:
		ball->SetPowerup(true);
		break;
	case SPEED_UP:
		m_Speed *= 1.1f;
		m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/PaddleSpeedUp.csv"));
		break;
	case SPEED_DOWN:
		m_Speed *= 0.9f;
		m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/PaddleSpeedDown.csv"));
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
//!	@brief		: ���E�̈ړ��l�Z�b�g�i�㉺�ɂ͓����Ȃ��j
//!	@param[in]	: example
//-------------------------------------------------------------
void Paddle::SetSpeed(const F32 speed)
{
	m_Speed = speed;
}
//-------------------------------------------------------------
//!	@brief		: �ړ��l�擾
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
//!	@brief		: �}�g���N�X�ňړ��Ɗg�嗦�ύX
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
//===============================================================
//	End of File
//===============================================================
