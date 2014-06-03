//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "Title.h"
#include "DebugUtill.h"
#include "Stage1.h"
#include "SoundManager.h"
#include "InputKeyboard.h"
#include "CSVReader.h"
#include "BoxFactory.h"
#include "Colors.h"
#include "TriangleRenderer.h"
#include "UseFixed.h"
#include "PrimitivePool.h"
#include "MaterialPool.h"
#include "DefaultShader.h"
#include "BlurFilter.h"

using namespace AK;
using namespace Sound;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
static const U32 TITLE_BGM_NUM = 2;
InputKeyboard keyboard;


//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Title::Title(INode* parent)
	:	SceneNode		(parent)
	,	m_IsEnd			(false)
	,	m_IsFading		(false)
	,	m_FadeVolume	(1.f)
	,	m_Shader		(NULL)
	,	m_FadeOutScreen	(NULL)
	,	m_FadeOutRenderer(NULL)
	,	m_Floating		(0.0f)
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Title::~Title()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);
	GraphicsManager::GetInstance()->EraseShaderObject(m_FadeOutScreen);
	SAFE_DELETE(m_Shader);

	auto it = m_TitleBlock.begin();
	while(it != m_TitleBlock.end())
	{
		SAFE_DELETE(*it);
		it = m_TitleBlock.erase(it);
	}
	
	SAFE_DELETE(m_FadeOutRenderer);
	SAFE_DELETE(m_FadeOutScreen);
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 更新
//-------------------------------------------------------------
void Title::Update()
{
	DEBUG_PRINT_CHAR("TITLE");
	
	keyboard.Update();
	CheckBeginFade();

	FloatingBlock();

	if (m_IsFading)
		FadeOutScene();
}
//-------------------------------------------------------------
//!	@brief		: シーン変更
//!	@return		: 変更時なら変更先ポインタ
//-------------------------------------------------------------
SceneNode*	Title::NextScene()
{
	if (m_IsEnd)
		return NEW Stage1(m_Parent, 0);
	return this;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Title::Initialize()
{
	SoundManager::GetInstance()->SetVolumeBGM(TITLE_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(TITLE_BGM_NUM, TRUE);

	m_Shader = NEW DefaultShader();
	//m_Shader = NEW UseFixed();CookTorrance

	m_Shader->Initilize();
	m_FadeOutScreen = NEW ScreenEffect();
	m_FadeOutScreen->Initilize();

	m_FadeOutRenderer = NEW WindowPolygonRenderer();
	m_FadeOutRenderer->CreatePolygon();
	m_FadeOutScreen->AddRenderer(m_FadeOutRenderer);

	VertexFloat3 fadeColor;
	fadeColor.m[0] = 1.f;
	fadeColor.m[1] = 1.f;
	fadeColor.m[2] = 1.f;
	//fadeColor.m[3] = 0.f;
	m_FadeOutScreen->SetFadeColor(fadeColor);
	m_FadeOutScreen->SetFadeValue(0.f);
	m_FadeOutScreen->SetActive(false);

	LoadTitleBlock();
	BlurFilter* blur = NEW BlurFilter();
	blur->Initilize();
	blur->m_AffectedShaders.push_back(m_Shader);
	GraphicsManager::GetInstance()->AddShaderObject(blur);
	//GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
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
void Title::CheckBeginFade()
{
	if (m_IsFading || !keyboard.IsTrigger(KEY_BUTTON1))
		return;
	m_IsFading = true;
	if (m_FadeOutScreen)
		m_FadeOutScreen->SetActive(m_IsFading);
	SoundManager::GetInstance()->PlaySE(11, TRUE);
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Title::FadeOutScene()
{
	m_FadeVolume -= 0.01f;
	
	SoundManager::GetInstance()->SetVolumeBGM(TITLE_BGM_NUM, m_FadeVolume);
	if (m_FadeOutScreen)
		m_FadeOutScreen->SetFadeValue(1.f - m_FadeVolume);
	if (m_FadeVolume < 0.f)
	{
		m_IsEnd = true;
		SoundManager::GetInstance()->PauseBGM(TITLE_BGM_NUM);
	}
}
//-------------------------------------------------------------
//!	@brief		: タイトル用ブロック読み込み
//-------------------------------------------------------------
void Title::LoadTitleBlock()
{
	CSVReader data;
	data.Load("Assets/CSV/Title/Title.csv");
	U32 widthNum	= data[0].GetInteger();
	U32 heightNum	= data[1].GetInteger();
	F32 blockWhidth	= 1000.f / widthNum;
	F32 blockHeight	= 1000.f / heightNum;

	for (U32 i = 0; i < widthNum * heightNum; ++i)
	{
		if (data[i+2].GetInteger() == 0)
			continue;
		
		TriangleRenderer* render = NEW TriangleRenderer();
		render->SetBufferResource( PrimitivePool::GetInstance()->GetResource("data:BOX-Box01") );
		
		auto materialPtr = MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/TestMaterial.csv");
		//auto material = RTTI_PTR_DYNAMIC_CAST(Material, (materialPtr.GetSharedObject()));
		
		render->SetMaterial(materialPtr);

		Vector3 pos;

		pos.x = 500.f - ((i % widthNum) * (blockWhidth) + (blockWhidth * 0.5f));
		pos.y = 500.f - ((i / widthNum) * (blockHeight) + (blockHeight * 0.5f));
		pos.z = 0.f;

		render->SetTransform(std::make_shared<TransformObject>(pos, Vector3(blockWhidth, blockHeight, 32.f)));

		m_Shader->AddRenderer(render);
		m_TitleBlock.push_back(render);

	}

}
//-------------------------------------------------------------
//!	@brief		: ブロックを動かす
//-------------------------------------------------------------
void Title::FloatingBlock()
{
	m_Floating += 0.2f;
	F32 value = sin(m_Floating);

	auto it = m_TitleBlock.begin();
	while (it != m_TitleBlock.end())
	{
		auto transform = (*it)->GetTransform();
		Vector3 pos = transform->GetTranslation();
		pos.y += m_IsEnd ? -15.f : value;
		transform->SetTranslation(pos);
		transform->UpdateTransform();
		++it;
	}
}
//===============================================================
//	End of File
//===============================================================