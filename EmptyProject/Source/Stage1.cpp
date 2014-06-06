//=======================================================================================
//!	@file	:	Stage1.cpp
//!	@brief	:	Stage1クラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "DebugUtill.h"
#include "Stage1.h"
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
#include "DefaultShader.h"
#include "MotionBlur.h"


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
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Stage1::Stage1(INode* parent, U32 stageCount)
	:	SceneNode		(parent)
	,	m_IsEnd			(false)
	,	m_IsGameOver	(false)
	,	m_IsStageClear	(false)
	,	m_IsGameClear	(false)
	,	m_IsFading		(false)
	,	m_IsFadeEnd		(false)
	,	m_FadeVolume	(1.f)
	,	m_StageCount	(stageCount)
	,	m_Shader		(NULL)
	,	m_FadeShader	(NULL)
	,	m_Phong			(NULL)
	,	m_CookTorrance	(NULL)
	,	m_FadeRenderer	(NULL)
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
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Stage1::~Stage1()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);
	GraphicsManager::GetInstance()->EraseShaderObject(m_FadeShader);
	SAFE_DELETE(m_Shader);
	SAFE_DELETE(m_FadeShader);

}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 更新
//-------------------------------------------------------------
void Stage1::Update()
{
	DEBUG_PRINT_CHAR("STAGE_01");
	if (m_StageCount >= STAGE_MAX)
		return;
	m_IsStageClear = m_BlockSystem->Clear();

	if (m_IsFading)
		FadeScene();
	else if (m_IsStageClear)
		StageClear();

	if (m_IsFadeEnd)
		SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);

}
//-------------------------------------------------------------
//!	@brief		: シーン変更
//!	@return		: 変更時なら変更先ポインタ
//-------------------------------------------------------------
SceneNode*	Stage1::NextScene()
{
	if (m_IsGameOver || m_IsGameClear)
		return NEW Title(m_Parent);

	if (m_IsFadeEnd && m_IsStageClear)
		return NEW Stage1(m_Parent, ++m_StageCount);

	return this;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Stage1::Initialize()
{
	TRACE(1,"Stage1::Initialize");

	if (m_StageCount >= STAGE_MAX)
		return false;

	SoundManager::GetInstance()->SetVolumeBGM(STAGE_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(STAGE_BGM_NUM, TRUE);
	
	m_Shader = NEW DefaultShader();
	m_Shader->Initilize();
	
	m_FadeShader = NEW ScreenEffect();
	m_FadeShader->Initilize();


	m_CookTorrance = NEW DefaultShader();
	m_CookTorrance->Initilize();
	//m_CookTorrance->SetShaderTechniqueByName("Phong");

	m_FadeRenderer = NEW WindowPolygonRenderer();
	m_FadeRenderer->CreatePolygon();
	m_FadeShader->AddRenderer(m_FadeRenderer);
	VertexFloat3 fadeColor;
	fadeColor.m[0] = 1.f;
	fadeColor.m[1] = 1.f;
	fadeColor.m[2] = 1.f;
	m_FadeShader->SetFadeColor(fadeColor);

	CreatePadle();
	CreateBall();
	CreateBlock();
	CreateWall();
	
	
	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
	
	GraphicsManager::GetInstance()->AddShaderObject(m_FadeShader);

	m_ItemSystem = NEW ItemSystem(this);
	
	AttachNode(m_BlockSystem);
	AttachNode(m_Ball[0]);

	
	return true;
}

//-------------------------------------------------------------
//!	@brief		: アイテムをランダムで生成
//!	@return		: 
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
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
bool Stage1::IsEnd() const
{
	return m_IsEnd;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SetEnd(const bool end)
{
	m_IsEnd = end;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
const Paddle* Stage1::GetPaddle(const U32 index)	const
{
	assert(m_Paddle[index]);
	return m_Paddle[index];
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
const Wall*	Stage1::GetWall(const U32 index) const
{
	assert(m_Wall[index]);
	return m_Wall[index];
}
//-------------------------------------------------------------
//!	@brief		:
//!	@return		:
//-------------------------------------------------------------
Ball*	Stage1::GetBall(const U32 index) const
{
	assert(m_Ball[index]);
	return m_Ball[index];
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
const Item*	Stage1::GetItem(const U32 index) const
{
	return m_ItemSystem->GetItem(index);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SetPaddle(Paddle* paddle, const U32 index)
{
	m_Paddle[index] = paddle;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SetWall(Wall* wall, const U32 index)
{
	m_Wall[index] = wall;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SetBall(Ball* ball, const U32 index)
{
	m_Ball[index] = ball;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: ステージをクリアした場合の
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
void Stage1::StageClear()
{
	SoundManager::GetInstance()->PlaySE(CLEAR_JINGLE, TRUE);
	SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);

	for (auto iChild = m_Children.begin(); iChild != m_Children.end(); ++iChild)
		(*iChild)->SetActive(false);
	
	m_IsFading = true;
	
	m_IsGameClear = m_StageCount >= STAGE_MAX;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
void Stage1::FadeScene()
{
	m_FadeVolume -= 0.01f;
	SoundManager::GetInstance()->SetVolumeBGM(STAGE_BGM_NUM, m_FadeVolume);
	
	if (m_FadeShader)
		m_FadeShader->SetFadeValue(1.f - m_FadeVolume);

	if (m_FadeVolume < 0 && SoundManager::GetInstance()->IsActiveSE(CLEAR_JINGLE) == FALSE)
		m_IsFadeEnd = true;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Stage1::CreateWall()
{
	//	壁作成
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
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Stage1::CreateBall()
{
	//	ボール作成
	const Vector3 ballPos(0.f, -250.f, 0.f);
	m_Ball[0] = NEW Ball(this, ballPos, m_Paddle[0]);
	m_Ball[0]->SetShader(m_CookTorrance);
	m_Shader->AddRenderer(m_Ball[0]->GetRenderer());
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Stage1::CreatePadle()
{
	const Vector3 paddlePos(0.f, -400.f, 0.f);
	m_Paddle[0] = NEW Paddle(this, paddlePos);
	m_Shader->AddRenderer(m_Paddle[0]->GetRenderer());
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
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