//=======================================================================================
//!	@file	:	INode.cpp
//!	@brief	:	INodeクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
//!	@brief		: コンストラクタ
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
//!	@brief		: ノードをアタッチする（子にする）
//!	@param[in]	: アタッチするノード
//-------------------------------------------------------------
void INode::AttachNode(INode* _node)
{
	auto it = std::find(m_Children.begin(), m_Children.end(), _node);
	if (it == m_Children.end())
		m_Children.push_back(_node);
}
//-------------------------------------------------------------
//!	@brief		: ノードを検索してデタッチする
//!	@param[in]	: デタッチしたいノードのハンドル
//!	@return		: アタッチされていたらデタッチしポインタを返す。なければNULL
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
//!	@brief		: Activeフラグの取得
//!	@return		: アクティブならtrue
//-------------------------------------------------------------
bool INode::GetActive()
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: アクティブを切り替える。m_IsActiveがtrueでないとUpdate()されない
//!	@param[in]	: フラグ
//-------------------------------------------------------------
void INode::SetActive(bool active)
{
	m_IsActive = active;
	if (active)
		Start();
}
//-------------------------------------------------------------
//!	@brief		: ノードのハンドルを取得
//!	@return		: ハンドル
//-------------------------------------------------------------
U32	INode::GetHandle()
{
	return m_Handle;
}
//-------------------------------------------------------------
//!	@brief		: ノードのハンドルを取得
//!	@return		: ハンドル
//-------------------------------------------------------------
INode* INode::GetParent()
{
	return m_Parent;
}
//-------------------------------------------------------------
//!	@brief		: 更新（親→子の順）
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
//!	@brief		: ノード検索(現在のノードの子になっていれば検索可能)
//!	@param[in]	: 検索したいノードのハンドル
//!	@return		: 検索成功ならノードのポインタ。失敗ならNULL
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