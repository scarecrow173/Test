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
#include "RootNode.h"
#include "TexturePool.h"
#include "RingWaveEffect.h"

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
	"Assets/CSV/Stage/Stage04.csv",
//	"Assets/CSV/Stage/LastStage.csv",
};
static const U32 STAGE_BGM_NUM	= 3;
static const U32 CLEAR_JINGLE	= 9;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Stage1::Stage1(AbsNode* parent, U32 stageCount)
	:	SceneNode		(parent)
	,	m_IsEnd			(false)
	,	m_IsGameOver	(false)
	,	m_IsStageClear	(false)
	,	m_IsGameClear	(false)
	,	m_IsStartStage	(false)
	,	m_FadeVolume	(1.f)
	,	m_StageCount	(stageCount)
	,	m_Shader		(NULL)
	,	m_FadeShader	(NULL)
	,	m_Simple		(NULL)
	,	m_CookTorrance	(NULL)
	,	m_FadeRenderer	(NULL)
	,	m_LStageFont	(NULL)
	,	m_RStageFont	(NULL)
	,	m_StartFont		(NULL)
	,	m_ClearFont		(NULL)
	,	m_TimeFont		(NULL)
	,	m_TimeNumFont	(NULL)
	,	m_ScoreFont		(NULL)
	,	m_ScoreNumFont	(NULL)
	,	m_OpacityStep	(NULL)
	,	m_AddStep		(NULL)
	,	m_ScoreArea		(NULL)
	,	m_BlockSystem	(NULL)
	,	m_ItemSystem	(NULL)
	,	m_StopCount		(0.f)
	,	m_CrrentScore	(0)
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
	GraphicsManager::GetInstance()->EraseShaderObject(m_LStageFont);
	GraphicsManager::GetInstance()->EraseShaderObject(m_RStageFont);
	GraphicsManager::GetInstance()->EraseShaderObject(m_StartFont);
	GraphicsManager::GetInstance()->EraseShaderObject(m_ClearFont);
	GraphicsManager::GetInstance()->EraseShaderObject(m_ScoreFont);
	GraphicsManager::GetInstance()->EraseShaderObject(m_ScoreNumFont);
	GraphicsManager::GetInstance()->EraseShaderObject(m_OpacityStep);
	GraphicsManager::GetInstance()->EraseShaderObject(m_AddStep);

	SAFE_DELETE(m_Shader);
	SAFE_DELETE(m_FadeShader);
	SAFE_DELETE(m_FadeRenderer);
	SAFE_DELETE(m_CookTorrance);
	SAFE_DELETE(m_LStageFont);
	SAFE_DELETE(m_RStageFont);
	SAFE_DELETE(m_StartFont);
	SAFE_DELETE(m_ClearFont);
	SAFE_DELETE(m_ScoreFont);
	SAFE_DELETE(m_ScoreNumFont);
	SAFE_DELETE(m_OpacityStep);
	SAFE_DELETE(m_AddStep);
	SAFE_DELETE(m_ScoreArea)
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

	UpdateScore();
	if (m_StageCount >= STAGE_MAX)
		return;

	m_IsGameClear = m_IsStageClear ?  m_StageCount >= STAGE_MAX : false;

	if (m_BlockSystem->Clear())
		StageClear();
		
	if (m_IsStartStage)
		StartStage();
}
//-------------------------------------------------------------
//!	@brief		: シーン変更
//!	@return		: 変更時なら変更先ポインタ
//-------------------------------------------------------------
SceneNode*	Stage1::NextScene()
{
	if (m_IsGameOver || m_IsGameClear)
		return NEW Title(m_Parent);

	if (m_IsStageClear)
	{
		SoundManager::GetInstance()->m_delta.Stop();
		SoundManager::GetInstance()->m_delta.Reset();
		return NEW Stage1(m_Parent, ++m_StageCount);
	}
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

	RootNode::GetInstance()->GetStopWatch()->Reset();
	RootNode::GetInstance()->GetStopWatch()->Stop();

	SoundManager::GetInstance()->SetVolumeBGM(STAGE_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(STAGE_BGM_NUM, TRUE);
	SoundManager::GetInstance()->m_delta.Reset();
	SoundManager::GetInstance()->m_delta.Start();
	
	m_Shader = NEW DefaultShader();
	m_Shader->Initilize();
	
	m_FadeShader = NEW ScreenEffect();
	m_FadeShader->Initilize();


	m_CookTorrance = NEW DefaultShader();
	m_CookTorrance->Initilize();
	m_CookTorrance->SetShaderTechniqueByName("HalfLambert");

	m_Simple = NEW DefaultShader();
	m_Simple->Initilize();
	m_Simple->SetShaderTechniqueByName("SimpleColor");

	m_OpacityStep	= NEW UIStepDefault();
	m_OpacityStep->Initilize();

	m_FadeRenderer = NEW WindowPolygonRenderer();
	m_FadeRenderer->CreatePolygon();
	m_FadeShader->AddRenderer(m_FadeRenderer);
	VertexFloat3 fadeColor;
	fadeColor.m[0] = 1.f;
	fadeColor.m[1] = 1.f;
	fadeColor.m[2] = 1.f;
	m_FadeShader->SetFadeColor(fadeColor);

	m_AddStep	 = NEW UIStepAdd();
	m_AddStep->Initilize();
	m_AddStep->SetActive(true);

	CreatePadle();
	CreateBall();
	CreateBlock();
	CreateWall();
	
	//CreateFont();
	//CreateFontArea();

	TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/gra_effect_hitN.png");
	TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/gra_effect_auraA.png");
	TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/gra_effect_lightR.png");

	//Util::RingWaveEffect* ring = NEW Util::RingWaveEffect();


	GraphicsManager::GetInstance()->AddShaderObject(m_OpacityStep);
	GraphicsManager::GetInstance()->AddShaderObject(m_AddStep);
	GraphicsManager::GetInstance()->AddShaderObject(m_Simple);
	//GraphicsManager::GetInstance()->AddShaderObject(m_LStageFont);
	//GraphicsManager::GetInstance()->AddShaderObject(m_RStageFont);
	//GraphicsManager::GetInstance()->AddShaderObject(m_StartFont);
	//GraphicsManager::GetInstance()->AddShaderObject(m_ClearFont);
	//GraphicsManager::GetInstance()->AddShaderObject(m_ScoreFont);
	//GraphicsManager::GetInstance()->AddShaderObject(m_ScoreNumFont);

	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
	
	GraphicsManager::GetInstance()->AddShaderObject(m_FadeShader);


	m_ItemSystem = NEW ItemSystem(this);
	
	AttachNode(m_BlockSystem);
	AttachNode(m_Ball[0]);

	SetChildrenActive(false);

	m_StartStep		= (StageStartStep)0;
	m_StopCount		= 0;
	m_IsStartStage	= true;
	m_ClearStep		= (StageClearStep)0;

	m_CrrentScore = RootNode::GetInstance()->GetScorer()->GetScore();

	
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
	m_AddStep->AddRenderer(pop->GetEffectRenderer());

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
bool Stage1::IsGameOver()const
{
	return m_IsGameOver;
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
void Stage1::SetGameOver(const bool gameOver)
{
	m_IsGameOver = gameOver;
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

	switch(m_ClearStep)
	{
	case START_STAGECLEAR:
		StartStageClear();
		break;
	case DOWN_CLEARFONT:
		DownClearFont();
		break;
	case FADE_SCENE:
		FadeScene();
		break;
	case STAGE_CLEAR_END:
		SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);
		m_IsStageClear = true;
		m_IsGameClear = m_StageCount >= STAGE_MAX - 1;
		break;
	}


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
		m_ClearStep = STAGE_CLEAR_END;
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
	const Vector3 bv(0.f, -offset - 100, 0.f);

	
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
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
bool Stage1::CreateBall()
{
	//	ボール作成
	const Vector3 ballPos(0.f, -290.f, 0.f);
	m_Ball[0] = NEW Ball(this, ballPos, m_Paddle[0]);
	m_CookTorrance->SetShaderTechniqueByName("SimpleColor");
	m_Ball[0]->SetShader(m_CookTorrance);
	m_Shader->AddRenderer(m_Ball[0]->GetRenderer());
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
bool Stage1::CreatePadle()
{
	const Vector3 paddlePos(0.f, -400.f, 0.f);
	m_Paddle[0] = NEW Paddle(this, paddlePos);
	m_Shader->AddRenderer(m_Paddle[0]->GetRenderer());
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
bool Stage1::CreateBlock()
{
 	m_BlockSystem = NEW BlockSystem(this);
	m_Ball[0]->SetBlockSystem(m_BlockSystem);
	m_BlockSystem->SetBall(m_Ball[0]);
	m_BlockSystem->CreateStageBlocks(StageDataPath[m_StageCount], m_Shader, m_Simple);
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
bool Stage1::CreateFont()
{
	
	m_LStageFont = NEW  DrawFonts(32, 32, "ＭＳ Ｐゴシック");
	m_LStageFont->Initilize();
	m_LStageFont->SetDrawString(L"Stage" + std::to_wstring((_ULonglong)m_StageCount+1));
	Matrix firstFontPositon;
	D3DXMatrixTranslation(&firstFontPositon, - (32.f * 2.8f), WINDOW_HEIGHT / 2, 0.f);
	m_LStageFont->SetWorld(firstFontPositon);

	m_RStageFont = NEW DrawFonts(32, 32, "ＭＳ Ｐゴシック");
	m_RStageFont->Initilize();
	m_RStageFont->SetDrawString(L"Stage" + std::to_wstring((_ULonglong)m_StageCount+1));
	Matrix firstFontPositonR;
	D3DXMatrixTranslation(&firstFontPositonR, WINDOW_WIDTH, WINDOW_HEIGHT / 2, 0.f);
	m_RStageFont->SetWorld(firstFontPositonR);

	m_StartFont = NEW DrawFonts(128, 32, "ＭＳ Ｐゴシック");
	m_StartFont->Initilize();
	m_StartFont->SetDrawString(L"Start!!");
	D3DXMatrixTranslation(&firstFontPositon, (WINDOW_WIDTH * 0.5f) - (64.f * 2.5f), WINDOW_HEIGHT / 2, 0.f);
	m_StartFont->SetWorld(firstFontPositon);
	m_StartFont->SetColor(0x00FFFFFF);

	static const F32 CLEAR_FONTS_CENTER_OFFSET	= 64.f * 5.f;
	D3DXMatrixIdentity(&firstFontPositon);
	D3DXMatrixTranslation(&firstFontPositon,  (WINDOW_WIDTH / 2) - CLEAR_FONTS_CENTER_OFFSET, - (256.f), 0.f);

	m_ClearFont = NEW DrawFonts(128, 32, "ＭＳ Ｐゴシック");
	m_ClearFont->Initilize();
	m_ClearFont->SetDrawString(L"StageClear!!");
	m_ClearFont->SetWorld(firstFontPositon);

	m_ScoreFont = NEW DrawFonts(32, 32, "ＭＳ Ｐゴシック");
	m_ScoreFont->Initilize();
	m_ScoreFont->SetDrawString(L"Score:");
	D3DXMatrixIdentity(&firstFontPositon);
	D3DXMatrixTranslation(&firstFontPositon, 16.f, 0, 0.f);
	m_ScoreFont->SetWorld(firstFontPositon);

	m_ScoreNumFont = NEW DrawFonts(32, 32, "ＭＳ Ｐゴシック");
	D3DXMatrixTranslation(&firstFontPositon,  firstFontPositon._41 + (16.f * 5), 0, 0.f);
	m_ScoreNumFont->Initilize();
	m_ScoreNumFont->SetWorld(firstFontPositon);

	
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
bool Stage1::CreateFontArea()
{
	
	m_ScoreArea = NEW UITextureRenderer(NEW TextureAnimationController(512, 512, 1,1));
	m_ScoreArea->SetTransform(std::make_shared<TransformObject>(Vector3(0.f,1.f,0.f), Vector3(0.35f, 0.07f, 1.f)));
	m_ScoreArea->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/e-tex1-2-2.jpg"));
	m_OpacityStep->AddRenderer(m_ScoreArea);


	
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::StartStage()
{
	switch(m_StartStep)
	{
	case SLIDE_IN_STAGEFONT:
		SlideInStageFont();
		break;
	case STOP_STAGEFONT:
		StopStageFont();
		break;
	case SLIDE_OUT_STAGEFONT:
		SlideOutStageFont();
		break;
	case SLIDE_IN_STARTFONT:
		SlideInStartFont();
		break;
	case STOP_STARTFONT:
		StopStartFont();
		break;
	case SLIDE_OUT_STARTFONT:
		SlideOutStartFont();
		break;
	case START_STAGE_END:
		m_IsStartStage = false;
		SetChildrenActive(true);
		RootNode::GetInstance()->GetStopWatch()->Start();
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SlideInStageFont()
{
	//static const F32 SLIDE_SPEED				= 5.f;
	//static const F32 STAGE_FONTS_CENTER_OFFSET	= 16.f * 3.f;
	//
	//Matrix fontsPositionL;
	//Matrix fontsPositionR;
	//fontsPositionL	= m_LStageFont->GetWorld();
	//D3DXMatrixTranslation(&fontsPositionL, fontsPositionL._41 + SLIDE_SPEED, fontsPositionL._42, 0.f);
	//m_LStageFont->SetWorld(fontsPositionL);

	//fontsPositionR	= m_RStageFont->GetWorld();
	//D3DXMatrixTranslation(&fontsPositionR, fontsPositionR._41 - SLIDE_SPEED, fontsPositionR._42, 0.f);
	//m_RStageFont->SetWorld(fontsPositionR);

	//if(fontsPositionL._41 >= (WINDOW_WIDTH / 2) - STAGE_FONTS_CENTER_OFFSET)
		m_StartStep = STOP_STAGEFONT;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::StopStageFont()
{
	//static const U32 END_COUNT = 90;
	//++m_StopCount;

	//if (m_StopCount > END_COUNT)
	{
		m_StopCount = 0;
		m_StartStep = SLIDE_OUT_STAGEFONT;
	}
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SlideOutStageFont()
{
	//static const F32 SLIDE_SPEED = 20.f;
	//Matrix fontsPositionL;
	//Matrix fontsPositionR;

	//fontsPositionL	= m_LStageFont->GetWorld();
	//D3DXMatrixTranslation(&fontsPositionL, fontsPositionL._41 + SLIDE_SPEED, fontsPositionL._42, 0.f);
	//m_LStageFont->SetWorld(fontsPositionL);

	//fontsPositionR	= m_RStageFont->GetWorld();
	//D3DXMatrixTranslation(&fontsPositionR, fontsPositionR._41 - SLIDE_SPEED, fontsPositionR._42, 0.f);
	//m_RStageFont->SetWorld(fontsPositionR);

	//if (fontsPositionL._41 > WINDOW_WIDTH)
		m_StartStep = SLIDE_IN_STARTFONT;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SlideInStartFont()
{
	//static const DWORD ADDING_ALPHA = 16;
	//DWORD color = m_StartFont->GetColor();
	//color += ADDING_ALPHA << 24;
	//m_StartFont->SetColor(color);


	//if ((255 - ADDING_ALPHA) <= (color >> 24))
	{
		//m_StartFont->SetColor(0xFFFFFFFF);
		m_StartStep = STOP_STARTFONT;
	}
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::StopStartFont()
{
	//static const U32 END_COUNT = 20;
	//++m_StopCount;
	//
	//if (m_StopCount >= END_COUNT)
	{
		m_StopCount = 0;
		m_StartStep = SLIDE_OUT_STARTFONT;
	}
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SlideOutStartFont()
{
	//static const DWORD ADDING_ALPHA = 16;
	//DWORD color = m_StartFont->GetColor();
	//color -= ADDING_ALPHA << 24;
	//m_StartFont->SetColor(color);


	//if ((ADDING_ALPHA) >= (color >> 24))
	{
		//m_StartFont->SetColor(0x00000000);
		m_StartStep = START_STAGE_END;
	}
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::StartStageClear()
{
	SoundManager::GetInstance()->PlaySE(CLEAR_JINGLE, TRUE);
	SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);

	SetChildrenActive(false);
	
	m_IsGameClear = m_StageCount >= STAGE_MAX;

	m_ClearStep = DOWN_CLEARFONT;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::DownClearFont()
{
	//static const F32 SLIDE_SPEED = 10.f;
	//Matrix fontsPosition;
	//fontsPosition	= m_ClearFont->GetWorld();
	//D3DXMatrixTranslation(&fontsPosition, fontsPosition._41, fontsPosition._42 + SLIDE_SPEED, 0.f);
	//m_ClearFont->SetWorld(fontsPosition);

	//if (fontsPosition._42 > WINDOW_HEIGHT)
		m_ClearStep = FADE_SCENE;

}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::UpdateScore()
{
	//	ここでやらずにスコアが増えたタイミングでやったほうがいい
	//	ただ更新し続けることも考慮しなきゃいけないのでとりあえずこれで
	const U32 targetScore	= RootNode::GetInstance()->GetScorer()->GetScore();
	const U32 distance		= targetScore - m_CrrentScore;
	static const F32 K		= 0.1f;
	m_CrrentScore			+= (U32)(distance * K) <= 1 ? distance : (U32)(distance * K);

 	//m_ScoreNumFont->SetDrawString(std::to_wstring((_ULonglong)m_CrrentScore));
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
void Stage1::SetChildrenActive(const bool active)
{
	for (auto iChild = m_Children.begin(); iChild != m_Children.end(); ++iChild)
		(*iChild)->SetActive(active);
}
//===============================================================
//	End of File
//===============================================================