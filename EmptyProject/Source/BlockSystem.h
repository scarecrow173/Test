//=======================================================================================
//!	@file	:	BlockSystem.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/05/08
//=======================================================================================
#pragma once
#include "AbsNode.h"

namespace AK
{

namespace Graphics{ class AbsShaderObject; class UIStepAdd; };
namespace Collision{ class AbsCollisionObject; };
class Block;
class Ball;

//=======================================================================================
//!	@class	:	BlockSystem
//!	@brief	:	ブロック管理用クラス
//!	@par	:	ブロックの作成や削除。ブロック数が0ならクリアなのでその判定もする。
//!	@note	:	example
//=======================================================================================
class BlockSystem : public AbsNode
{
public:
	BlockSystem(AbsNode* parent);
	virtual ~BlockSystem();

	RTTI_IS_A(BlockSystem);
	virtual void Update();
	virtual void Start();
	bool CreateStageBlocks(const std::string& filePath, Graphics::AbsShaderObject* shader, Graphics::AbsShaderObject* addStep);
	bool Clear();

	bool DeleteBlock(Collision::AbsCollisionObject* obj);
	void SetBall(Ball* ball);
	

private:
	std::vector<Block*>			m_BlockList;
	Ball*	m_Ball;

};

};
//===============================================================
//	End of File
//===============================================================