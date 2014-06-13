//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "BlockSystem.h"
#include "AbsCollisionObject.h"
#include "Block.h"
#include "GraphicsManager.h"
#include "Ball.h"
#include "CSVReader.h"
#include "Stage1.h"
#include "UIStepAdd.h"

using namespace AK;
using namespace Collision;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
BlockSystem::BlockSystem(AbsNode* parent)
	:	AbsNode	(parent)
	,	m_Ball	(NULL)
{

}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
BlockSystem::~BlockSystem()
{
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �X�V
//-------------------------------------------------------------
void BlockSystem::Update()
{
	TRACE(1, "BlockSystem::Update");
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlockSystem::Start()
{
	
}
//-------------------------------------------------------------
//!	@brief		: �X�e�[�W�Ƀu���b�N��z�u
//!	@param[in]	: �u���b�N��
//!	@param[in]	: �s��
//!	@param[in]	: ��
//!	@return		: �쐬�ɐ��������� true
//-------------------------------------------------------------
bool BlockSystem::CreateStageBlocks(const std::string& filePath, AbsShaderObject* shader, UIStepAdd* addStep)
{
	assert(m_Ball);

	Matrix view,proj;
	view = GraphicsManager::GetInstance()->GetView();
	proj = GraphicsManager::GetInstance()->GetProjection();

	CSVReader StageData;
	StageData.Load(filePath.c_str());
	for (U32 i = 0; i < StageData.row * StageData.column; ++i)
	{
		if (StageData[i].GetInteger() == 0)
			continue;

		Vector3 vec3(450.f - ((i % StageData.row) * 125.f) , 400.f - ((i / StageData.row) * 100.f), 0);
		Block* block = NEW Block(this, vec3, StageData[i].GetInteger());
		block->SetSEHandle((i % StageData.row) + 1);
		this->AttachNode(block);
		shader->AddRenderer(block->GetRenderer());
		addStep->AddRenderer(block->GetEffectRenderer());
		addStep->AddRenderer(block->GetHardEffectRenderer());
		m_Ball->GetCollision()->PushCollisionList(block->GetCollision());
		m_BlockList.push_back(block);
	}


	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();



	return true;
}
//-------------------------------------------------------------
//!	@brief		: �Q�[���̃N���A��������
//!	@return		: �����u���b�N��0�Ȃ�true
//-------------------------------------------------------------
bool BlockSystem::Clear()
{
	return m_BlockList.empty();
}
//-------------------------------------------------------------
//!	@brief		: �u���b�N�̍폜
//!	@param[in]	: �폜�������u���b�N�̃R���W����
//-------------------------------------------------------------
bool BlockSystem::DeleteBlock(AbsCollisionObject* obj)
{
	bool isBlock = false;
	auto it = m_BlockList.begin();
	while (it != m_BlockList.end())
	{
		if (obj == (*it)->GetCollision())
		{
			isBlock = true;
			if ((*it)->Death())
			{
				((Stage1*)m_Parent)->PopItem((*it)->GetTransform()->GetTranslation());
				//(*it)->SetActive(false);
				it = m_BlockList.erase(it);
				continue;
			}
		}
		++it;
	}
	return isBlock;

}
//-------------------------------------------------------------
//!	@brief		: �{�[���̃R���W�������Z�b�g(���̃{�[���Ƀu���b�N�̃R���W�������A�^�b�`�����)
//!	@param[in]	: �Z�b�g�������R���W����
//-------------------------------------------------------------
void BlockSystem::SetBall(Ball* ball)
{
	m_Ball = ball;
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