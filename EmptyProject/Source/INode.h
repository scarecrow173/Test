//=======================================================================================
//!	@file	:	INode.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>


namespace AK
{
namespace Collision{ class ICollisionObject; };
class GameObject;
//=======================================================================================
//!	@class	:	INode
//!	@brief	:	ノードのインターフェース
//!	@par	:	ゲーム上のオブジェクトをこれを継承して一括管理するため
//!	@note	:	
//=======================================================================================
class INode
{
public:
	INode(INode* parent);
	virtual ~INode();

	RTTI_IS_A_BASE(INode);
	
	void		AttachNode(INode* node);
	INode*		DetachNode(U32 findHandle);
	INode*		FindNode(U32 findHandle);
	GameObject*	FindNode(Collision::ICollisionObject* collison);

	bool		GetActive()	const;
	void		SetActive(const bool active);
	U32			GetHandle() const;
	INode*		GetParent() const;

	void	UpdateNodeTree();
	virtual void	Update()	PURE;
	virtual void	Start();


protected:
	static U32	NODE_ID;

	U32					m_Handle;
	bool				m_IsActive;
	std::vector<INode*>	m_Children;
	INode*				m_Parent;

};



};

//===============================================================
//	End of File
//===============================================================