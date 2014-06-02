//=======================================================================================
//!	@file	:	BlockSystem.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/05/08
//=======================================================================================
#pragma once
#include "INode.h"

namespace AK
{

namespace Graphics{ class IShaderObject; };
namespace Collision{ class ICollisionObject; };
class Block;
class Ball;

//=======================================================================================
//!	@class	:	BlockSystem
//!	@brief	:	ブロック管理用クラス
//!	@par	:	ブロックの作成や削除。ブロック数が0ならクリアなのでその判定もする。
//!	@note	:	example
//=======================================================================================
class BlockSystem : public INode
{
public:
	BlockSystem(INode* parent);
	virtual ~BlockSystem();

	RTTI_IS_A(BlockSystem);
	virtual void Update();
	virtual void Start();
	bool CreateStageBlocks(const std::string& filePath, Graphics::IShaderObject* shader);
	bool Clear();

	bool DeleteBlock(Collision::ICollisionObject* obj);
	void SetBall(Ball* ball);
	

private:
	std::vector<Block*>			m_BlockList;
	Ball*	m_Ball;

};

};
//===============================================================
//	End of File
//===============================================================