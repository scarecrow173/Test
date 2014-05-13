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
#include "Stage2.h"
#include "Title.h"
#include "BlockSystem.h"
#include "Ball.h"
#include "Paddle.h"
#include "GraphicsManager.h"
#include "UseFixed.h"
#include "CollisionBox.h"

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Stage1::Stage1(INode* parent)
	:	SceneNode	(parent)
	,	m_IsEnd		(false)
	,	m_Shader	(NEW UseFixed())
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Stage1::~Stage1()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);
	SAFE_DELETE(m_Shader);
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
}
//-------------------------------------------------------------
//!	@brief		: シーン変更
//!	@return		: 変更時なら変更先ポインタ
//-------------------------------------------------------------
SceneNode*	Stage1::ChangeScene()
{
	//static U32 count = 0;
	//if (++count % 300 == 0)
	//	return NEW Stage2();

	if (m_IsEnd)
		return NEW Title(m_Parent);
	if (m_BlockSystem->Clear())
		return NEW Stage1(m_Parent);



	return this;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Stage1::Initialize()
{

	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
	m_BlockSystem = NEW BlockSystem(this);
	


	Matrix view,proj;
	view = GraphicsManager::GetInstance()->GetView();
	proj = GraphicsManager::GetInstance()->GetProjection();

	auto paddlePos = Math::ScreenToWorld(Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT - 10.f), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	Paddle* paddle = NEW Paddle(this, paddlePos);
	
	//	ボール作成
	auto ballPos = Math::ScreenToWorld(Vector2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, proj);
	Ball* ball = NEW Ball(this, ballPos, paddle);
	
	m_Shader->AddRenderer(paddle->GetRenderer());

	//ball->GetCollison()->PushCollisonList(paddle->GetCollison());


	m_Shader->AddRenderer(ball->GetRenderer());
	m_BlockSystem->SetBall(ball);
	m_BlockSystem->CreateStageBlocks( 8, 2, m_Shader);


	ball->SetBlockSystem(m_BlockSystem);
	ball->SetShader(m_Shader);

	

	AttachNode(m_BlockSystem);
	AttachNode(ball);


	return true;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Stage1::IsEnd()
{
	return m_IsEnd;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
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