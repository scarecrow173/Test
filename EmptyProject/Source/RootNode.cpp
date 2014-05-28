//=======================================================================================
//!	@file	:	AutoPerformance.cpp
//!	@brief	:	AutoPerformanceクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "RootNode.h"
#include "SceneNode.h"
#include "Title.h"
using namespace AK;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
RootNode*	RootNode::m_Instance = NULL;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
RootNode::RootNode()
	:	INode		(NULL)	
	,	m_Time		(0.f)
	,	m_NowScene	(NULL)
{
	m_NowScene = NEW Title(this);
	m_NowScene->Initialize();
	AttachNode(m_NowScene);

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
RootNode::~RootNode()
{
}
//-------------------------------------------------------------
//!	@brief		: インスタンス作成
//!	@return		: インスタンス
//-------------------------------------------------------------
RootNode*	RootNode::Create()
{
	if (!m_Instance)
		m_Instance = NEW RootNode();
	return m_Instance;
	
}
//-------------------------------------------------------------
//!	@brief		: インスタンス削除
//-------------------------------------------------------------
void RootNode::Destroy()
{
	SAFE_DELETE(m_Instance);
}
//-------------------------------------------------------------
//!	@brief		: 更新
//-------------------------------------------------------------
void RootNode::Update()
{
	SceneNode* newScene = m_NowScene->NextScene();
	if (newScene != m_NowScene)
	{
		if (DetachNode(m_NowScene->GetHandle()))
			SAFE_DELETE(m_NowScene);
		m_NowScene = newScene;
		m_NowScene->Initialize();
		AttachNode(m_NowScene);
	}
}
//=======================================================================================
//		End Of File
//=======================================================================================