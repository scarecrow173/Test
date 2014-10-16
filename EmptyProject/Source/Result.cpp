//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "Result.h"
#include "GraphicsManager.h"
#include "SoundManager.h"
#include "RootNode.h"
#include "InputKeyboard.h"
#include "Stage1.h"
#include "TexturePool.h"


using namespace AK;
using namespace Sound;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
static const U32 RESULT_BGM_NUM = 2;
namespace
{
	InputKeyboard keyboard;
}
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Result::Result(AbsNode* parent, U32 _stageCount, F32 _time, U32 _score)
: SceneNode(parent)
, m_Time(_time)
, m_Score(_score)
, m_StageCount(_stageCount)
, m_Minute(_time / 60)
, m_Sec(m_Minute != 0 ? (U32)_time % m_Minute : _time)
, m_TmpTime(0)
, m_CurrentMinute(0)
, m_CurrentSec(0)
, m_CurrentScore(0)
, m_FadeVolume(1.f)
, m_IsEnd(false)
, m_IsFading(false)
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Result::~Result()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_FadeOutScreen);
	GraphicsManager::GetInstance()->EraseShaderObject(m_OpacityStep);

	SAFE_DELETE(m_OpacityStep);
	SAFE_DELETE(m_ResultText);
	SAFE_DELETE(m_ScoreText);
	SAFE_DELETE(m_TimeText);
	SAFE_DELETE(m_FadeOutRenderer);
	SAFE_DELETE(m_FadeOutScreen);
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 更新
//-------------------------------------------------------------
void Result::Update()
{
	DEBUG_PRINT_CHAR("RESULT");
	::keyboard.Update();
	
	m_CurrentScore = CalcSpring(m_CurrentScore, m_Score);
	m_ScoreNumber->SetNumber(m_CurrentScore);
	
	{
		m_TmpTime = CalcSpring(m_TmpTime, m_Time);
		m_CurrentMinute = m_TmpTime / 60;
		m_CurrentSec = m_TmpTime % 60;

		m_MinuteNumber->SetNumber(m_CurrentMinute);
		m_SecNumber->SetNumber(m_CurrentSec);
	}

	CheckBeginFade();
	if (m_IsFading)
		FadeOutScene();
}
//-------------------------------------------------------------
//!	@brief		: シーン変更
//!	@return		: 変更時なら変更先ポインタ
//-------------------------------------------------------------
SceneNode*	Result::NextScene()
{
	if (m_IsEnd)
		return NEW Stage1(m_Parent, m_StageCount);
	return this;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Result::Initialize()
{
	SoundManager::GetInstance()->SetVolumeBGM(RESULT_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(RESULT_BGM_NUM, TRUE);

	m_OpacityStep = NEW UIStepDefault();
	m_OpacityStep->Initilize();
	m_OpacityStep->SetActive(true);

	m_FadeOutScreen = NEW ScreenEffect();
	m_FadeOutScreen->Initilize();

	m_FadeOutRenderer = NEW WindowPolygonRenderer();
	m_FadeOutRenderer->CreatePolygon();
	m_FadeOutScreen->AddRenderer(m_FadeOutRenderer);

	VertexFloat3 fadeColor;
	fadeColor.m[0] = 1.f;
	fadeColor.m[1] = 1.f;
	fadeColor.m[2] = 1.f;
	m_FadeOutScreen->SetFadeColor(fadeColor);
	m_FadeOutScreen->SetFadeValue(0.f);
	m_FadeOutScreen->SetActive(false);

	m_ResultText = NEW UITextureRenderer(NEW TextureAnimationController(1024, 256, 1, 1));
	m_ResultText->SetTransform(std::make_shared<TransformObject>(Vector3(-32.f, 0.f, 0.f), Vector3(0.5f, 0.5f, 1.f)));
	m_ResultText->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/ResultText.png"));
	m_OpacityStep->AddRenderer(m_ResultText);

	const F32 score_y = 128.f;
	const F32 score_scale = 0.25f;
	
	const F32 time_y = 256.f;
	const F32 time_scale = 0.25f;

	m_ScoreText = NEW UITextureRenderer(NEW TextureAnimationController(1024, 256, 1, 1));
	m_ScoreText->SetTransform(std::make_shared<TransformObject>(Vector3(32.f, score_y, 0.f), Vector3(score_scale, 0.5f, 1.f)));
	m_ScoreText->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/Score.png"));
	m_OpacityStep->AddRenderer(m_ScoreText);
	
	m_TimeText = NEW UITextureRenderer(NEW TextureAnimationController(1024, 256, 1, 1));
	m_TimeText->SetTransform(std::make_shared<TransformObject>(Vector3(32.f, time_y, 0.f), Vector3(time_scale, 0.5f, 1.f)));
	m_TimeText->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/Time.png"));
	m_OpacityStep->AddRenderer(m_TimeText);

	m_ScoreNumber = NEW NumberPlateRenderer();
	m_ScoreNumber->SetNumber(m_Score);
	m_ScoreNumber->SetTransform(std::make_shared<TransformObject>(Vector3(512.f, score_y, 0.f), Vector3(1.f, 1.f, 1.f)));
	m_ScoreNumber->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/number.png"));
	m_OpacityStep->AddRenderer(m_ScoreNumber);



	m_MinuteNumber = NEW NumberPlateRenderer();
	m_MinuteNumber->SetNumber(m_Minute);
	m_MinuteNumber->SetTransform(std::make_shared<TransformObject>(Vector3(512.f - 192.f, time_y, 0.f), Vector3(1.f, 1.f, 1.f)));
	m_MinuteNumber->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/number.png"));
	m_OpacityStep->AddRenderer(m_MinuteNumber);

	m_ColonText = NEW UITextureRenderer(NEW TextureAnimationController(1024, 256, 1, 1));
	m_ColonText->SetTransform(std::make_shared<TransformObject>(Vector3(512.f - 128.f, time_y, 0.f), Vector3(1.f, 1.f, 1.f)));
	m_ColonText->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/Colon.png"));
	m_OpacityStep->AddRenderer(m_ColonText);

	m_SecNumber = NEW NumberPlateRenderer();
	m_SecNumber->SetNumber(m_Sec);
	m_SecNumber->SetTransform(std::make_shared<TransformObject>(Vector3(512.f, time_y, 0.f), Vector3(1.f, 1.f, 1.f)));
	m_SecNumber->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/number.png"));
	m_OpacityStep->AddRenderer(m_SecNumber);

	GraphicsManager::GetInstance()->AddShaderObject(m_OpacityStep);
	GraphicsManager::GetInstance()->AddShaderObject(m_FadeOutScreen);
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
	return true;

}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Result::CheckBeginFade()
{
	if (m_IsFading || !::keyboard.IsTrigger(KEY_BUTTON1))
		return;
	m_IsFading = true;
	if (m_FadeOutScreen)
		m_FadeOutScreen->SetActive(m_IsFading);
	SoundManager::GetInstance()->PlaySE(11, TRUE);
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Result::FadeOutScene()
{
	m_FadeVolume -= 0.01f;

	SoundManager::GetInstance()->SetVolumeBGM(RESULT_BGM_NUM, m_FadeVolume);
	if (m_FadeOutScreen)
		m_FadeOutScreen->SetFadeValue(1.f - m_FadeVolume);
	if (m_FadeVolume < 0.f)
	{
		m_IsEnd = true;
		SoundManager::GetInstance()->PauseBGM(RESULT_BGM_NUM);
	}
}

//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
U32	Result::CalcSpring(U32 _current, const U32 _target)
{
	//	ここでやらずにスコアが増えたタイミングでやったほうがいい
	//	ただ更新し続けることも考慮しなきゃいけないのでとりあえずこれで
	const U32 distance = _target - _current;
	static const F32 K = 0.1f;
	return _current + ((U32)(distance * K) <= 1 ? distance : (U32)(distance * K));
}
//-------------------------------------------------------------
//!	@brief		: タイトル用ブロック読み込み
//-------------------------------------------------------------

//-------------------------------------------------------------
//!	@brief		: ブロックを動かす
//-------------------------------------------------------------

//===============================================================
//	End of File
//===============================================================