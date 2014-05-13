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
	,	m_Shader		(NULL)
{
	std::vector<U32> indexSrc;
	IndexData indexData;
	indexData = SphereFactory::GetInstance()->CreateSphere(Vector3(0, 0, 0), 0.2f, ARGBColors::Green, indexSrc);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->Initialize(DXUTGetD3D9Device());
	m_Renderer->AddIndex(indexSrc);
	m_Renderer->ReCreateIndexBuffer();
	m_Renderer->UpdateIndexData(indexData);
	
	Matrix mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);

	m_Renderer->SetWorld(mat);

	m_Collison = NEW CollisionSphere(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), 0.2f);
	m_Collison->SetReflection(true);
	m_Collison->SetReflectionFactor(1.1f);

	
	m_StreamHndle = BASS_StreamCreateFile(FALSE, "Assets/Sound/SE/se_maoudamashii_battle17.mp3", 0, 0, 0);
	
	Matrix view, proj;
	view = GraphicsManager::GetInstance()->GetView();
	proj = GraphicsManager::GetInstance()->GetProjection();

	//	�Ǎ쐬
	auto lv = Math::ScreenToWorld(Vector2(0.f, WINDOW_HEIGHT * 0.5f), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	lv.x += 5.f;
	lv.z = 0.f;
	
	auto rv	 = Math::ScreenToWorld(Vector2(WINDOW_WIDTH, WINDOW_HEIGHT * 0.5f), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	rv.x -= 5.f;
	rv.z = 0.f;
	
	auto tv = Math::ScreenToWorld(Vector2(WINDOW_WIDTH *  0.5f, 0), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	tv.y += 5.f;
	tv.z = 0.f;
	
	auto bv = Math::ScreenToWorld(Vector2( WINDOW_WIDTH *  0.5f, WINDOW_HEIGHT), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	bv.y -= 5.f;
	bv.z = 0.f;

	Wall *left, *right, *top, *bottom;
	
	left	= NEW Wall(this, lv, WALL_LEFT);
	right	= NEW Wall(this, rv, WALL_RIGHT);
	top		= NEW Wall(this, tv, WALL_TOP);
	bottom	= NEW Wall(this, bv, WALL_BOTTOM);

	m_Collison->PushCollisonList(left->GetCollison());
	m_Collison->PushCollisonList(right->GetCollison());
	m_Collison->PushCollisonList(top->GetCollison());
	m_Collison->PushCollisonList(bottom->GetCollison());
	m_BottomLine = bottom->GetCollison();


	m_Collison->PushCollisonList(m_Paddle->GetCollison());
	m_Paddle->GetCollison()->PushCollisonList(left->GetCollison());
	m_Paddle->GetCollison()->PushCollisonList(right->GetCollison());

}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
Ball::~Ball()
{
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::Update()
{
	m_Keyboard.Update();
	std::vector<ICollisonObject*> l_list;
	
	m_Collison->Update(l_list);
	if (!l_list.empty())
	{
		for (auto it = l_list.begin(); it != l_list.end(); ++it)
		{
			if ((*it) == m_BottomLine && !m_IsRespawn)
			{
				AddDeathCount();
				auto respawn = m_Paddle->GetPosition();
				respawn.y += 2.f;
				m_Collison->SetPosition(respawn);
				m_Collison->SetSpeed(Vector3(0.f, 0.f, 0.f));
				m_IsRespawn = true;
			}
			m_BlockSystem->DeleteBlock(*it);
			BASS_ChannelPlay(m_StreamHndle, FALSE);
		}		
	}
	if (m_IsRespawn && m_Keyboard.IsTrigger(KEY_BUTTON1))
	{
		Vector3 resSpeed(0.03f, 0.02f, 0.f);
		resSpeed.x = m_Paddle->GetCollison()->GetSpeed().x > 0 ? 0.03f : -0.03f;
		m_Collison->SetSpeed(resSpeed);
		m_IsRespawn = false;
	}
	if (m_IsRespawn)
	{
		auto respawn = m_Paddle->GetPosition();
		respawn.y += 2.f;
		m_Collison->SetPosition(respawn);
	}
	m_Position = m_Collison->GetPosition();
	Matrix mat;
	D3DXMatrixTranslation(&mat, m_Position.x, m_Position.y, m_Position.z);
	m_Renderer->SetWorld(mat);
	if (m_DeathCount >= 3)
		((Stage1*)m_Parent)->SetEnd(true);
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
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::AddDeathCount()
{
	++m_DeathCount;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::SubDeathCount()
{
	--m_DeathCount;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
U32 Ball::GetDeathCount()
{
	return m_DeathCount;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::SetBottomLine(Collision::ICollisonObject* bottomLine)
{
	m_BottomLine = bottomLine;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Ball::PopItem(Vector3 pos)
{
	assert(m_Shader);
	if (std::rand() % 2 != 0)
		return;
	S32 r = std::rand() % 4;
	Item* pop = NEW Item(m_Paddle, pos, (ITEM_TYPE)r);
	m_Shader->AddRenderer(pop->GetRenderer());
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
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
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================


//!<