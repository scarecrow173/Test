//=======================================================================================
//!	@file	:	INode.cpp
//!	@brief	:	INodeクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "INode.h"
using namespace AK;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
U32 INode::NODE_ID = 0;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
INode::INode()
	:	m_Handle	(++NODE_ID)
	,	m_IsActive	(true)
{
	Start();
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
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
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void INode::AttachNode(INode* _node)
{
	m_Children.push_back(_node);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
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
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool INode::GetActive()
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void INode::SetActive(bool active)
{
	m_IsActive = active;
	if (active)
		Start();
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
U32	INode::GetHandle()
{
	return m_Handle;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
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
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
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
inline void INode::Start()
{

}
//===============================================================
//	End of File
//===============================================================