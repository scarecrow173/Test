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
	AttachNode(m_NowScene);

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
RootNode::~RootNode()
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
RootNode*	RootNode::Create()
{
	if (m_Instance)
		return m_Instance;

	m_Instance = NEW RootNode();
	return m_Instance;
	
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
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
	SceneNode* newScene = m_NowScene->ChangeScene();
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