//=======================================================================================
//!	@file	:	Stage1.cpp
//!	@brief	:	Stage1�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
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
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
Stage1::Stage1(INode* parent, U32 stageCount)
	:	SceneNode	(parent)
	,	m_IsEnd		(false)
	,	m_FadeVolume(1.f)
	,	m_StageCount(stageCount)
	,	m_Shader	(NEW UseFixed())
{}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
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
//!	@brief		: �X�V
//-------------------------------------------------------------
void Stage1::Update()
{
	DEBUG_PRINT_CHAR("STAGE_01");
}
//-------------------------------------------------------------
//!	@brief		: �V�[���ύX
//!	@return		: �ύX���Ȃ�ύX��|�C���^
//-------------------------------------------------------------
SceneNode*	Stage1::ChangeScene()
{
	//static U32 count = 0;
	//if (++count % 300 == 0)
	//	return NEW Stage2();

	//if (m_IsEnd || (m_StageCount >= STAGE_MAX)){}
		//return NEW Title(m_Parent);
	if (!m_IsEnd && m_BlockSystem->Clear())
	{
		SoundManager::GetInstance()->PlaySE(CLEAR_JINGLE, TRUE);
		SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);
		m_IsEnd = true;
	}
		//return NEW Stage1(m_Parent, ++m_StageCount);

	SetActive(!m_IsEnd);
	m_FadeVolume -= m_IsEnd ? 0.01f : 0.f;
	SoundManager::GetInstance()->SetVolumeBGM(STAGE_BGM_NUM, m_FadeVolume);

	if (m_FadeVolume < 0.f && SoundManager::GetInstance()->IsActiveSE(CLEAR_JINGLE) == FALSE)
	{
		SoundManager::GetInstance()->PauseBGM(STAGE_BGM_NUM);
		return (m_StageCount >= STAGE_MAX) ? (SceneNode*)(NEW Title(m_Parent)) : (m_BlockSystem->Clear()) ? (SceneNode*)(NEW Stage1(m_Parent, ++m_StageCount)) : (SceneNode*)(NEW Title(m_Parent));
	}
	return this;
}
//-------------------------------------------------------------
//!	@brief		: ������
//!	@return		: ����(true),���s(false)
//-------------------------------------------------------------
bool Stage1::Initialize()
{
	SoundManager::GetInstance()->SetVolumeBGM(STAGE_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(STAGE_BGM_NUM, TRUE);

	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
	m_BlockSystem = NEW BlockSystem(this);
	


	Matrix view,proj;
	view = GraphicsManager::GetInstance()->GetView();
	proj = GraphicsManager::GetInstance()->GetProjection();

	//auto paddlePos = Math::ScreenToWorld(Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT - 10.f), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	Vector3 paddlePos(0.f, -400.f, 0.f);
	Paddle* paddle = NEW Paddle(this, paddlePos);
	
	//	�{�[���쐬
	//auto ballPos = Math::ScreenToWorld(Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	Vector3 ballPos(0.f, -250.f, 0.f);
	Ball* ball = NEW Ball(this, ballPos, paddle);
	
	m_Shader->AddRenderer(paddle->GetRenderer());


	m_Shader->AddRenderer(ball->GetRenderer());
	m_BlockSystem->SetBall(ball);
	m_BlockSystem->CreateStageBlocks(StageDataPath[m_StageCount], m_Shader);


	ball->SetBlockSystem(m_BlockSystem);
	ball->SetShader(m_Shader);

	

	AttachNode(m_BlockSystem);
	AttachNode(ball);

	
	return true;
}
//-------------------------------------------------------------
//!	@brief		: ������
//!	@return		: ����(true),���s(false)
//-------------------------------------------------------------
bool Stage1::IsEnd()
{
	return m_IsEnd;
}
//-------------------------------------------------------------
//!	@brief		: ������
//!	@return		: ����(true),���s(false)
//-------------------------------------------------------------
void Stage1::SetEnd(bool end)
{
	m_IsEnd = end;
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