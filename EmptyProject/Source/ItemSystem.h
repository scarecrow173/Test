//=======================================================================================
//!	@file	:	ItemSystem.h
//!	@author	:	���R �l�\
//!	@date	:	2014/05/08
//=======================================================================================
#pragma once
#include "INode.h"

namespace AK
{

namespace Graphics{ class IShaderObject; };
namespace Collision{ class ICollisionObject; };
class Item;
class Ball;

//=======================================================================================
//!	@class	:	ItemSystem
//!	@brief	:	�u���b�N�Ǘ��p�N���X
//!	@par	:	�u���b�N�̍쐬��폜�B�u���b�N����0�Ȃ�N���A�Ȃ̂ł��̔��������B
//!	@note	:	example
//=======================================================================================
class ItemSystem : public INode
{
public:
	ItemSystem(INode* parent);
	virtual ~ItemSystem();

	
	virtual void Update();
	virtual void Start();
	
	Item*	GetItem(const U32 id);
	void	AddItem(Item* item);

private:
	std::vector<Item*>			m_ItemList;

};

};
//===============================================================
//	End of File
//===============================================================