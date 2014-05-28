//=======================================================================================
//!	@file	:	AutoPerformance.cpp
//!	@brief	:	AutoPerformance�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
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
//!	@brief		: �R���X�g���N�^
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
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
RootNode::~RootNode()
{
}
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�쐬
//!	@return		: �C���X�^���X
//-------------------------------------------------------------
RootNode*	RootNode::Create()
{
	if (!m_Instance)
		m_Instance = NEW RootNode();
	return m_Instance;
	
}
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�폜
//-------------------------------------------------------------
void RootNode::Destroy()
{
	SAFE_DELETE(m_Instance);
}
//-------------------------------------------------------------
//!	@brief		: �X�V
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