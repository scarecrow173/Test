//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "BlockSystem.h"
#include "ICollisonObject.h"
#include "Block.h"
#include "GraphicsManager.h"
#include "Ball.h"
#include "CSVReader.h"

using namespace AK;
using namespace Collision;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
BlockSystem::BlockSystem(INode* parent)
	:	INode	(parent)
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
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlockSystem::Update()
{

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
bool BlockSystem::CreateStageBlocks(std::string& filePath, IShaderObject* shader)
{
	assert(m_Ball);

	Matrix view,proj;
	view = GraphicsManager::GetInstance()->GetView();
	proj = GraphicsManager::GetInstance()->GetProjection();
	auto StageData = CSVReader::ReadInteger(filePath);

	for (int i = 0; i < StageData.row * StageData.column; ++i)
	{
		if (StageData.Data[i] == 0)
			continue;

		Vector3 vec3(450.f - ((i % StageData.row) * 125.f) , 450.f - ((i / StageData.row) * 100.f), 0);
		Block* block = NEW Block(this, vec3, StageData.Data[i]);
		this->AttachNode(block);
		shader->AddRenderer(block->GetRenderer());
		m_Ball->GetCollison()->PushCollisonList(block->GetCollison());
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
	//return m_Children.empty();
}
//-------------------------------------------------------------
//!	@brief		: �u���b�N�̍폜
//!	@param[in]	: �폜�������u���b�N�̃R���W����
//-------------------------------------------------------------
void BlockSystem::DeleteBlock(ICollisonObject* obj)
{
	auto it = m_BlockList.begin();
	while (it != m_BlockList.end())
	{
		if (obj == (*it)->GetCollison())
		{
			if ((*it)->Death())
			{
				m_Ball->PopItem((*it)->GetPosition());
				it = m_BlockList.erase(it);
				continue;
			}
		}
		++it;
	}
	//	��2 : Cast����������Ȃ�
	//for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	//{
	//	if (obj == ((Block*)(*it))->GetCollison())
	//		((Block*)(*it))->Death();
	//}
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