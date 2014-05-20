//=======================================================================================
//!	@file	:	Stage1.cpp
//!	@brief	:	Stage1ƒNƒ‰ƒX‚Ìƒƒ“ƒoŠÖ”éŒ¾
//!	@author	:	¬R ‰lŒ\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "DebugUtill.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Title.h"
#include "BlockSystem.h"
#include "Ball.h"
#include "Paddle.h"
#include "GraphicsManager.h"
#include "UseFixed.h"
#include "CollisionBox.h"
#include "CSVReader.h"
#include "BoxFactory.h"
#include "SphereFactory.h"
#include "SoundManager.h"
#include "Wall.h"
#include "Item.h"
#include "ItemSystem.h"


using namespace AK;
using namespace Graphics;
using namespace Sound;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
std::string	Stage1::StageDataPath[STAGE_MAX] = 
{
	"Assets/CSV/Stage/Stage01.csv",
	"Assets/CSV/Stage/Stage02.csv",
	"Assets/CSV/Stage/Stage03.csv",
};
static const U32 STAGE_BGM_NUM	= 3;
static const U32 CLEAR_JINGLE	= 9;
//-------------------------------------------------------------
//!	@brief		: ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//-------------------------------------------------------------
Stage1::Stage1(INode* parent, U32 stageCount)
	:	SceneNode		(parent)
	,	m_IsEnd			(false)
	,	m_FadeVolume	(1.f)
	,	m_StageCount	(stageCount)
	,	m_Shader		(NEW UseFixed())
	,	m_BlockSystem	(NULL)
	,	m_ItemSystem	(NULL)
{
	for (S32 i = 0; i < PADDLE_NUM; ++i)
		m_Paddle[i] = NULL;

	for (S32 i = 0; i < WALL_NUM; ++i)
		m_Wall[i] = NULL;
	
	for (S32 i = 0; i < BALL_NUM; ++i)
		m_Ball[i] = NULL;
}
//-------------------------------------------------------------
//!	@brief		: ƒfƒXƒgƒ‰ƒNƒ^
//-------------------------------------------------------------
Stage1::~Stage1()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);
	SAFE_DELETE(m_Shader);
	BoxFactory::GetInstance()->AllClear();
	SphereFactory::GetInstance()->AllClear();
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: XV
//-------------------------------------------------------------
void Stage1::Update()
{
	TRACE(1,"Stage1::Update");
	DEBUG_PRINT_CHAR("STAGE_01");

}
//-------------------------------------------------------------
//!	@brief		: ƒV[ƒ“•ÏX
//!	@return		: •ÏX‚È‚ç•ÏXæƒ|ƒCƒ“ƒ^
//-------------------------------------------------------------
SceneNode*	Stage1::ChangeScene()
{
	TRACE(1,"Stage1::ChangeScene");
	StageClear();
	FadeScene();

	if (m_FadeVolume < 0.f && SoundManager::GetInstance()->IsActiveSE(CLEAR_JINGLE) == FALSE)
	{
		SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);
		return (m_StageCount >= STAGE_MAX) ? (SceneNode*)(NEW Title(m_Parent)) : (m_BlockSystem->Clear()) ? (SceneNode*)(NEW Stage1(m_Parent, ++m_StageCount)) : (SceneNode*)(NEW Title(m_Parent));
	}
	return this;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
bool Stage1::Initialize()
{
	TRACE(1,"Stage1::Initialize");
	SoundManager::GetInstance()->SetVolumeBGM(STAGE_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(STAGE_BGM_NUM, TRUE);

	CreatePadle();
	CreateBall();
	CreateBlock();
	CreateWall();

	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);

	m_ItemSystem = NEW ItemSystem(this);
	
	AttachNode(m_BlockSystem);
	AttachNode(m_Ball[0]);

	
	return true;
}

//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
void Stage1::PopItem(Vector3 pos)
{
	TRACE(1,"Stage1::PopItem");
	assert(m_Shader);
	if (std::rand() % 4 != 0)
		return;
	S32 r = std::rand() % 4;
	Item* pop = NEW Item(m_ItemSystem, pos, (ITEM_TYPE)r);
	m_Shader->AddRenderer(pop->GetRenderer());
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
	m_ItemSystem->AddItem(pop);

	for (U32 i = 0; i < PADDLE_NUM; ++i)
		pop->AddCollision(m_Paddle[i]->GetCollision());
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
bool Stage1::IsEnd() const
{
	return m_IsEnd;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
void Stage1::SetEnd(const bool end)
{
	m_IsEnd = end;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
const Paddle* Stage1::GetPaddle(const U32 id)	const
{
	assert(id < PADDLE_NUM);
	assert(m_Paddle[id]);
	return m_Paddle[id];
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
const Wall*	Stage1::GetWall(const U32 id) const
{
	assert(id < WALL_NUM);
	assert(m_Wall[id]);
	return m_Wall[id];
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
Ball*	Stage1::GetBall(const U32 id) const
{
	assert(id < BALL_NUM);
	assert(m_Ball[id]);
	return m_Ball[id];
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
const Item*	Stage1::GetItem(const U32 id) const
{
	return m_ItemSystem->GetItem(id);
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
void Stage1::SetPaddle(Paddle* paddle, const U32 id)
{
	assert(id < PADDLE_NUM);
	m_Paddle[id] = paddle;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
void Stage1::SetWall(Wall* wall, const U32 id)
{
	assert(id < WALL_NUM);
	m_Wall[id] = wall;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
void Stage1::SetBall(Ball* ball, const U32 id)
{
	assert(id < BALL_NUM);
	m_Ball[id] = ball;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
void Stage1::StageClear()
{
	if (m_IsEnd || !m_BlockSystem->Clear())
		return;
	SoundManager::GetInstance()->PlaySE(CLEAR_JINGLE, TRUE);
	SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);
	m_IsEnd = true;
	SetActive(!m_IsEnd);
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
void Stage1::FadeScene()
{
	m_FadeVolume -= m_IsEnd ? 0.01f : 0.f;
	SoundManager::GetInstance()->SetVolumeBGM(STAGE_BGM_NUM, m_FadeVolume);
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
bool Stage1::CreateWall()
{
	//	•Çì¬
	const F32 offset = 550.f;
	const Vector3 lv(offset, 0, 0);
	const Vector3 rv(-offset, 0, 0);
	const Vector3 tv(0.f, offset, 0.f);
	const Vector3 bv(0.f, -offset, 0.f);

	
	m_Wall[WALL_LEFT]	= NEW Wall(this, lv, WALL_LEFT);
	m_Wall[WALL_RIGHT]	= NEW Wall(this, rv, WALL_RIGHT);
	m_Wall[WALL_TOP]	= NEW Wall(this, tv, WALL_TOP);
	m_Wall[WALL_BOTTOM]	= NEW Wall(this, bv, WALL_BOTTOM);

	for (S32 i = 0; i < BALL_NUM; ++i)
	{
		m_Ball[i]->GetCollision()->PushCollisionList(m_Wall[WALL_LEFT]->GetCollision());
		m_Ball[i]->GetCollision()->PushCollisionList(m_Wall[WALL_RIGHT]->GetCollision());
		m_Ball[i]->GetCollision()->PushCollisionList(m_Wall[WALL_TOP]->GetCollision());
		m_Ball[i]->GetCollision()->PushCollisionList(m_Wall[WALL_BOTTOM]->GetCollision());
		m_Ball[i]->SetBottomLine(m_Wall[WALL_BOTTOM]->GetCollision());


		m_Ball[i]->GetCollision()->PushCollisionList(m_Paddle[0]->GetCollision());
		m_Paddle[0]->GetCollision()->PushCollisionList(m_Wall[WALL_LEFT]->GetCollision());
		m_Paddle[0]->GetCollision()->PushCollisionList(m_Wall[WALL_RIGHT]->GetCollision());
	}
	return true;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
bool Stage1::CreateBall()
{
	//	ƒ{[ƒ‹ì¬
	const Vector3 ballPos(0.f, -250.f, 0.f);
	m_Ball[0] = NEW Ball(this, ballPos, m_Paddle[0]);
	m_Ball[0]->SetShader(m_Shader);
	m_Shader->AddRenderer(m_Ball[0]->GetRenderer());
	return true;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
bool Stage1::CreatePadle()
{
	const Vector3 paddlePos(0.f, -400.f, 0.f);
	m_Paddle[0] = NEW Paddle(this, paddlePos);
	m_Shader->AddRenderer(m_Paddle[0]->GetRenderer());
	return true;
}
//-------------------------------------------------------------
//!	@brief		: ‰Šú‰»
//!	@return		: ¬Œ÷(true),¸”s(false)
//-------------------------------------------------------------
bool Stage1::CreateBlock()
{
 	m_BlockSystem = NEW BlockSystem(this);
	m_Ball[0]->SetBlockSystem(m_BlockSystem);
	m_BlockSystem->SetBall(m_Ball[0]);
	m_BlockSystem->CreateStageBlocks(StageDataPath[m_StageCount], m_Shader);
	return true;
}
//===============================================================
//	End of File
//===============================================================