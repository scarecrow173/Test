//=======================================================================================
//!	@file	:	Ball.cpp
//!	@brief	:	Ball�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "Ball.h"
#include "TriangleRenderer.h"
#include "SphereFactory.h"
#include "CollisionSphere.h"
#include "CollisionBox.h"
#include "Colors.h"
#include "BlockSystem.h"
#include "Wall.h"
#include "Stage1.h"
#include "Paddle.h"
#include "Item.h"
#include "IShaderObject.h"
#include "SoundManager.h"
#include "BallStateLaunchStandby.h"
#include "ResourceManager.h"
#include "PrimitivePool.h"

using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
Ball::Ball(INode* parent, Vector3 pos, Paddle* paddle)
	:	GameObject		(parent, pos)
	,	m_DeathCount	(0)
	,	m_BlockSystem	(NULL)
	,	m_BottomLine	(0)
	,	m_Paddle		(paddle)
	,	m_IsRespawn		(true)
	,	m_IsPowerup		(false)
	,	m_Shader		(NULL)
	,	m_PowerupCount	(0)
	,	m_State			(NEW BallStateLaunchStandby())
{

	m_Radius = 30.f;
	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetPrimitive("data:SHPERE-Ball"));
	m_Transform = std::make_shared<TransformObject>(pos, Vector3(m_Radius, m_Radius, m_Radius));

	m_Renderer->SetTransform(m_Transform);

	m_Collision = NEW CollisionSphere(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), m_Radius);
	m_Collision->SetReflection(true);
	m_Collision->SetReflectionFactor(1.1f);

}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
Ball::~Ball()
{
	SAFE_DELETE(m_State);
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �X�V
//-------------------------------------------------------------
void Ball::Update()
{

	m_State->InputAction(this);
	auto nextState = m_State->TransitionAction();
	if (nextState != m_State)
	{
		m_State->ExitAction(this);
		SAFE_DELETE(m_State);
		m_State = nextState;
		m_State->EntryAction(this);
	}
	UpdateMatrix();

	TRACE(1, "Ball::Update.End");
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::Start()
{}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::SetBlockSystem(BlockSystem* system)
{
	m_BlockSystem = system;
}
//-------------------------------------------------------------
//!	@brief		: ���񂾉񐔉��Z(+1)
//-------------------------------------------------------------
void Ball::AddDeathCount()
{
	++m_DeathCount;
}
//-------------------------------------------------------------
//!	@brief		: ���񂾉񐔌��Z(�c�@�𑝂₷���Ƃ������)
//-------------------------------------------------------------
void Ball::SubDeathCount()
{
	--m_DeathCount;
}
//-------------------------------------------------------------
//!	@brief		: �c�@�擾
//-------------------------------------------------------------
U32 Ball::GetDeathCount() const
{
	return m_DeathCount;
}
//-------------------------------------------------------------
//!	@brief		: ���S���C���o�^
//-------------------------------------------------------------
void Ball::SetBottomLine(Collision::ICollisionObject* bottomLine)
{
	m_BottomLine = bottomLine;
}
//-------------------------------------------------------------
//!	@brief		: ���S���C���擾
//-------------------------------------------------------------
ICollisionObject* Ball::GetBottomLine() const
{
	return m_BottomLine;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::SetShader(IShaderObject* shader)
{
	m_Shader = shader;
}
//-------------------------------------------------------------
//!	@brief		: �p���[�A�b�v�t���O�Z�b�g+�������Ԃ̃Z�b�g
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::SetPowerup(const bool powerup)
{
	if (powerup)
		m_PowerupCount = 120;
	m_IsPowerup = powerup;
}
//-------------------------------------------------------------
//!	@brief		: �p���[�A�b�v�t���O�Z�b�g
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool Ball::IsPowerup() const
{
	return m_IsPowerup;
}
//-------------------------------------------------------------
//!	@brief		: �p���[�A�b�v�t���O�Z�b�g
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Paddle*	Ball::GetPaddle() const
{
	return m_Paddle;
}
//-------------------------------------------------------------
//!	@brief		: �p���[�A�b�v�t���O�Z�b�g
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
BlockSystem* Ball::GetBlockSystem() const
{
	return m_BlockSystem;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: ���S��
//-------------------------------------------------------------
bool Ball::Death(ICollisionObject* obj)
{
	if (obj != m_BottomLine && !m_IsRespawn)
		return false;
	AddDeathCount();
	Respawn();
	m_Collision->SetSpeed(Vector3(0.f, 0.f, 0.f));
	m_IsRespawn = true;
	Sound::SoundManager::GetInstance()->PlaySE(0,TRUE);

	if (m_DeathCount >= 3)
		((Stage1*)m_Parent)->SetEnd(true);
	return true;
}
//-------------------------------------------------------------
//!	@brief		: ����
//-------------------------------------------------------------
void Ball::Respawn()
{
	if (!m_IsRespawn)
			return ;
	auto respawn = m_Paddle->GetTransform()->GetTranslation();
	respawn.y += 110.f;
	m_Collision->SetPosition(respawn);
}
//-------------------------------------------------------------
//!	@brief		: �e����
//-------------------------------------------------------------
void Ball::Launch()
{
	if (!m_IsRespawn)
		return;
	if (!m_Keyboard.IsTrigger(KEY_BUTTON1))
		return;
	Vector3 resSpeed(10.f, 5.f, 0.f);
	resSpeed.x = m_Paddle->GetCollision()->GetSpeed().x > 0 ? 10.f : -10.f;
	m_Collision->SetSpeed(resSpeed);
	m_IsRespawn = false;
}
//-------------------------------------------------------------
//!	@brief		: �����i�ړ��̂݁j
//-------------------------------------------------------------
void Ball::UpdateMatrix()
{
	m_Transform->SetTranslation(m_Collision->GetPosition());
	m_Transform->UpdateTransform();
}
//-------------------------------------------------------------
//!	@brief		: �p���[�A�b�v�i���݂͊ђʁB��莞�Ԃŉ����j
//-------------------------------------------------------------
void Ball::Powerup()
{
	if (--m_PowerupCount > 0)
		return;
	m_PowerupCount = 0;
	SetPowerup(false);
}

//===============================================================
//	End of File
//===============================================================


//!<