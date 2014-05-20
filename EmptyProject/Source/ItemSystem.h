//=======================================================================================
//!	@file	:	ItemSystem.h
//!	@author	:	小山 瑛圭
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
//!	@brief	:	ブロック管理用クラス
//!	@par	:	ブロックの作成や削除。ブロック数が0ならクリアなのでその判定もする。
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