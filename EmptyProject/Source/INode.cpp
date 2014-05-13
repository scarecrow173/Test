//=======================================================================================
//!	@file	:	INode.cpp
//!	@brief	:	INode�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "INode.h"
#include <algorithm>
using namespace AK;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
U32 INode::NODE_ID = 0;
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
INode::INode(INode* parent)
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
INode::~INode()
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
void INode::AttachNode(INode* _node)
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
INode* INode::DetachNode(U32 findHandle)
{
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		if ((*it)->m_Handle == findHandle)
		{
			INode* out = *it;
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
bool INode::GetActive()
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: �A�N�e�B�u��؂�ւ���Bm_IsActive��true�łȂ���Update()����Ȃ�
//!	@param[in]	: �t���O
//-------------------------------------------------------------
void INode::SetActive(bool active)
{
	m_IsActive = active;
	if (active)
		Start();
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h�̃n���h�����擾
//!	@return		: �n���h��
//-------------------------------------------------------------
U32	INode::GetHandle()
{
	return m_Handle;
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h�̃n���h�����擾
//!	@return		: �n���h��
//-------------------------------------------------------------
INode* INode::GetParent()
{
	return m_Parent;
}
//-------------------------------------------------------------
//!	@brief		: �X�V�i�e���q�̏��j
//-------------------------------------------------------------
void INode::UpdateChild()
{
	if (!m_IsActive)
		return;

	Update();
	
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		if ((*it)->m_IsActive)
			(*it)->UpdateChild();
	}
}
//-------------------------------------------------------------
//!	@brief		: �m�[�h����(���݂̃m�[�h�̎q�ɂȂ��Ă���Ό����\)
//!	@param[in]	: �����������m�[�h�̃n���h��
//!	@return		: ���������Ȃ�m�[�h�̃|�C���^�B���s�Ȃ�NULL
//-------------------------------------------------------------
INode* INode::FindNode(U32 findHandle)
{
	if (m_Handle == findHandle)
		return this;
	INode* out = NULL;
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		out = (*it)->FindNode(findHandle);
		if (out != NULL)
			return out;
	}
	return NULL;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void INode::Start()
{

}
//===============================================================
//	End of File
//===============================================================