//=======================================================================================
//!	@file	:	AbsNode.cpp
//!	@brief	:	AbsNode�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "AbsNode.h"
#include "GameObject.h"
#include <algorithm>
using namespace AK;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
U32 AbsNode::NODE_ID = 0;
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
AbsNode::AbsNode(AbsNode* parent)
	:	m_Handle	(++NODE_ID)
	,	m_IsActive	(true)
	,	m_Parent	(parent)
{
	if (parent)
		parent->AttachNode(this);
	Start();
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
AbsNode::~AbsNode()
{
	if (!m_Children.empty())
	{
		auto it = m_Children.begin(); 
		while (it != m_Children.end())
		{
			SAFE_DELETE(*it);
			it = m_Children.erase(it);
		}
	}
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h���A�^�b�`����i�q�ɂ���j
//!	@param[in]	: �A�^�b�`����m�[�h
//-------------------------------------------------------------
void AbsNode::AttachNode(AbsNode* _node)
{
	auto it = std::find(m_Children.begin(), m_Children.end(), _node);
	if (it == m_Children.end())
		m_Children.push_back(_node);
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h���������ăf�^�b�`����
//!	@param[in]	: �f�^�b�`�������m�[�h�̃n���h��
//!	@return		: �A�^�b�`����Ă�����f�^�b�`���|�C���^��Ԃ��B�Ȃ����NULL
//-------------------------------------------------------------
AbsNode* AbsNode::DetachNode(U32 findHandle)
{
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		if ((*it)->m_Handle == findHandle)
		{
			AbsNode* out = *it;
            m_Children.erase(it);
			return (out);
		}
	}
	return NULL;
}
//-------------------------------------------------------------
//!	@brief		: Active�t���O�̎擾
//!	@return		: �A�N�e�B�u�Ȃ�true
//-------------------------------------------------------------
bool AbsNode::GetActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: �A�N�e�B�u��؂�ւ���Bm_IsActive��true�łȂ���Update()����Ȃ�
//!	@param[in]	: �t���O
//-------------------------------------------------------------
void AbsNode::SetActive(const bool active)
{
	m_IsActive = active;
	if (active)
		Start();
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h�̃n���h�����擾
//!	@return		: �n���h��
//-------------------------------------------------------------
U32	AbsNode::GetHandle() const
{
	return m_Handle;
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h�̃n���h�����擾
//!	@return		: �n���h��
//-------------------------------------------------------------
AbsNode* AbsNode::GetParent() const
{
	return m_Parent;
}
//-------------------------------------------------------------
//!	@brief		: �X�V�i�e���q�̏��j
//-------------------------------------------------------------
void AbsNode::UpdateNodeTree()
{
	if (!m_IsActive)
		return;

	Update();
	
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		if ((*it)->m_IsActive)
			(*it)->UpdateNodeTree();
	}
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h����(���݂̃m�[�h�̎q�ɂȂ��Ă���Ό����\)
//!	@param[in]	: �����������m�[�h�̃n���h��
//!	@return		: ���������Ȃ�m�[�h�̃|�C���^�B���s�Ȃ�NULL
//-------------------------------------------------------------
AbsNode* AbsNode::FindNode(U32 findHandle)
{
	if (m_Handle == findHandle)
		return this;
	AbsNode* out = NULL;
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		out = (*it)->FindNode(findHandle);
		if (out != NULL)
			return out;
	}
	return NULL;
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h����(���݂̃m�[�h�̎q�ɂȂ��Ă���Ό����\)
//!	@param[in]	: �����������m�[�h�̃n���h��
//!	@return		: ���������Ȃ�m�[�h�̃|�C���^�B���s�Ȃ�NULL
//-------------------------------------------------------------
GameObject*	AbsNode::FindNode(Collision::AbsCollisionObject* collison)
{
	GameObject* thisPointer = RTTI_PTR_DYNAMIC_CAST(GameObject, (this));
	if (thisPointer && thisPointer->GetCollision() == collison)
		return thisPointer;


	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		auto obj = RTTI_PTR_DYNAMIC_CAST(GameObject, (*it));
		if (!obj)
			continue;
		if (obj->GetCollision() == collison)
			return (obj);
	}
	return NULL;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void AbsNode::Start()
{

}
//===============================================================
//	End of File
//===============================================================