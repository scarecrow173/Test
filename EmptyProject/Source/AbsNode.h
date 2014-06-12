//=======================================================================================
//!	@file	:	AbsNode.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>


namespace AK
{
namespace Collision{ class AbsCollisionObject; };
class GameObject;
//=======================================================================================
//!	@class	:	AbsNode
//!	@brief	:	ノードのインターフェース
//!	@par	:	ゲーム上のオブジェクトをこれを継承して一括管理するため
//!	@note	:	
//=======================================================================================
class AbsNode
{
public:
	AbsNode(AbsNode* parent);
	virtual ~AbsNode();

	RTTI_IS_A_BASE(AbsNode);
	
	void		AttachNode(AbsNode* node);
	AbsNode*	DetachNode(U32 findHandle);
	AbsNode*	FindNode(U32 findHandle);
	GameObject*	FindNode(Collision::AbsCollisionObject* collison);

	bool		GetActive()	const;
	void		SetActive(const bool active);
	U32			GetHandle() const;
	AbsNode*	GetParent() const;

	void	UpdateNodeTree();
	virtual void	Update()	= 0;
	virtual void	Start();


protected:
	static U32	NODE_ID;

	U32					m_Handle;
	bool				m_IsActive;
	std::vector<AbsNode*>	m_Children;
	AbsNode*				m_Parent;

};



};

//===============================================================
//	End of File
//===============================================================