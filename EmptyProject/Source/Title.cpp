//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
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
#include "RadialBlur.h"
#include "MotionBlur.h"
#include "DrawFonts.h"
#include "ChangeViewport.h"
#include "RootNode.h"
#include "RingWaveEffect.h"
#include "UIElement.h"
#include "MenuRevolver.h"

using namespace AK;
using namespace Sound;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
static const U32 TITLE_BGM_NUM = 2;
InputKeyboard keyboard;

Util::RingWaveEffect* ring;
UIElement* title = nullptr;
Util::MenuRevolver* revolv = nullptr;
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
Title::Title(AbsNode* parent)
	:	SceneNode			(parent)
	,	m_IsEnd				(false)
	,	m_IsFading			(false)
	,	m_FadeVolume		(1.f)
	,	m_Shader			(NULL)
	,	m_FadeOutScreen		(NULL)
	,	m_FadeOutRenderer	(NULL)
	,	m_Floating			(0.0f)
{
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
Title::~Title()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);
	GraphicsManager::GetInstance()->EraseShaderObject(m_FadeOutScreen);

	auto it = m_TitleBlock.begin();
	while(it != m_TitleBlock.end())
	{
		SAFE_DELETE(*it);
		it = m_TitleBlock.erase(it);
	}
	
	SAFE_DELETE(m_Shader);

	SAFE_DELETE(m_FadeOutRenderer);
	SAFE_DELETE(m_FadeOutScreen);

}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �X�V
//-------------------------------------------------------------
void Title::Update()
{
	DEBUG_PRINT_CHAR("TITLE");
	
	//keyboard.Update();
	CheckBeginFade();

	FloatingBlock();

	if (ring)
		ring->Update(0.016f);

	if (m_IsFading)
		FadeOutScene();
}
//-------------------------------------------------------------
//!	@brief		: �V�[���ύX
//!	@return		: �ύX���Ȃ�ύX��|�C���^
//-------------------------------------------------------------
SceneNode*	Title::NextScene()
{
	if (m_IsEnd)
		return NEW Stage1(m_Parent, 0);
	return this;
}
//-------------------------------------------------------------
//!	@brief		: ������
//!	@return		: ����(true),���s(false)
//-------------------------------------------------------------
bool Title::Initialize()
{
	SoundManager::GetInstance()->SetVolumeBGM(TITLE_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(TITLE_BGM_NUM, TRUE);

//	RootNode::GetInstance()->GetScore()->Reset();

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
	m_FadeOutScreen->SetFadeColor(fadeColor);
	m_FadeOutScreen->SetFadeValue(0.f);
	m_FadeOutScreen->SetActive(false);


	ring = NEW Util::RingWaveEffect();
	title = NEW UIElement(0);
	auto elem2 = NEW UIElement(1);
	auto elem3 = NEW UIElement(2);
	auto elem4 = NEW UIElement(3);
	revolv = NEW Util::MenuRevolver();
	
	Matrix uiRelative;
	D3DXMatrixTranslation(&uiRelative, 225, 0,0);
	title->SetReletiveTransform(uiRelative);
	
	D3DXMatrixTranslation(&uiRelative, -25, -260,0);
	elem2->SetReletiveTransform(uiRelative);
	
	D3DXMatrixTranslation(&uiRelative, -275, 0,0);
	elem3->SetReletiveTransform(uiRelative);
	
	D3DXMatrixTranslation(&uiRelative, -25, 200,0);
	elem4->SetReletiveTransform(uiRelative);

	revolv->SetElement(title);
	revolv->SetElement(elem2);
	revolv->SetElement(elem3);
	revolv->SetElement(elem4);

	//LoadTitleBlock();

	/*GraphicsManager::GetInstance()->AddShaderObject(Font);*/
	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
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
//!	@brief		: �^�C�g���p�u���b�N�ǂݍ���
//-------------------------------------------------------------
void Title::LoadTitleBlock()
{
	CSVReader data;
	data.Load("Assets/CSV/Title/Title.csv");
	U32 widthNum	= data[0].GetInteger();
	U32 heightNum	= data[1].GetInteger();
	F32 blockWhidth	= 1000.f / widthNum;	// 1000.f�͉�ʂ̕��B�}�W�b�N�i���o�[��߂悤��
	F32 blockHeight	= 1000.f / heightNum;

	for (U32 i = 0; i < widthNum * heightNum; ++i)
	{
		if (data[i+2].GetInteger() == 0)
			continue;
		
		TriangleRenderer* render = NEW TriangleRenderer();
		render->SetBufferResource( PrimitivePool::GetInstance()->GetResource("data:BOX-Box01") );
		
		auto materialPtr = MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/TitleBlock.csv");
		//auto material = RTTI_PTR_DYNAMIC_CAST(Material, (materialPtr.GetSharedObject()));
		
		render->SetMaterial(materialPtr);

		Vector3 pos;

		// 500.f�͕��̔����B�}�W�b�N�i���o�[...
		pos.x = 500.f - ((i % widthNum) * (blockWhidth) + (blockWhidth * 0.5f)); 
		pos.y = 500.f - ((i / widthNum) * (blockHeight) + (blockHeight * 0.5f));
		pos.z = 0.f;

		render->SetTransform(std::make_shared<TransformObject>(pos, Vector3(blockWhidth, blockHeight, 32.f)));

		m_Shader->AddRenderer(render);
		m_TitleBlock.push_back(render);

	}

}
//-------------------------------------------------------------
//!	@brief		: �u���b�N�𓮂���
//-------------------------------------------------------------
void Title::FloatingBlock()
{
	m_Floating += 0.2f;
	F32 value = sin(m_Floating) * 20.f;

	auto it = m_TitleBlock.begin();
	while (it != m_TitleBlock.end())
	{
		auto transform = (*it)->GetTransform();
		Vector3 pos = transform->GetTranslation();
		pos.y += m_IsFading ? (std::rand() % 10) / 10.f * -20.f : value;
		transform->SetTranslation(pos);
		transform->UpdateTransform();
		++it;
	}
}
//===============================================================
//	End of File
//===============================================================