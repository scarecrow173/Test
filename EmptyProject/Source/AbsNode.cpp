//=======================================================================================
//!	@file	:	AbsNode.cpp
//!	@brief	:	AbsNodeクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
//!	@brief		: コンストラクタ
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
//!	@brief		: デストラクタ
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
//!	@brief		: ノードをアタッチする（子にする）
//!	@param[in]	: アタッチするノード
//-------------------------------------------------------------
void AbsNode::AttachNode(AbsNode* _node)
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
//!	@brief		: Activeフラグの取得
//!	@return		: アクティブならtrue
//-------------------------------------------------------------
bool AbsNode::GetActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: アクティブを切り替える。m_IsActiveがtrueでないとUpdate()されない
//!	@param[in]	: フラグ
//-------------------------------------------------------------
void AbsNode::SetActive(const bool active)
{
	m_IsActive = active;
	if (active)
		Start();
}
//-------------------------------------------------------------
//!	@brief		: ノードのハンドルを取得
//!	@return		: ハンドル
//-------------------------------------------------------------
U32	AbsNode::GetHandle() const
{
	return m_Handle;
}
//-------------------------------------------------------------
//!	@brief		: ノードのハンドルを取得
//!	@return		: ハンドル
//-------------------------------------------------------------
AbsNode* AbsNode::GetParent() const
{
	return m_Parent;
}
//-------------------------------------------------------------
//!	@brief		: 更新（親→子の順）
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
//!	@brief		: ノード検索(現在のノードの子になっていれば検索可能)
//!	@param[in]	: 検索したいノードのハンドル
//!	@return		: 検索成功ならノードのポインタ。失敗ならNULL
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
//!	@brief		: ノード検索(現在のノードの子になっていれば検索可能)
//!	@param[in]	: 検索したいノードのハンドル
//!	@return		: 検索成功ならノードのポインタ。失敗ならNULL
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