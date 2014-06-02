//=======================================================================================
//!	@file	:	INode.h
//!	@author	:	���R �l�\
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
//!	@brief	:	�m�[�h�̃C���^�[�t�F�[�X
//!	@par	:	�Q�[����̃I�u�W�F�N�g��������p�����Ĉꊇ�Ǘ����邽��
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