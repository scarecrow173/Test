//=======================================================================================
//!	@file	:	BlockSystem.h
//!	@author	:	���R �l�\
//!	@date	:	2014/05/08
//=======================================================================================
#pragma once
#include "INode.h"

namespace AK
{

namespace Graphics{ class IShaderObject; };
namespace Collision{ class ICollisonObject; };
class Block;
class Ball;

//=======================================================================================
//!	@class	:	BlockSystem
//!	@brief	:	�u���b�N�Ǘ��p�N���X
//!	@par	:	�u���b�N�̍쐬��폜�B�u���b�N����0�Ȃ�N���A�Ȃ̂ł��̔��������B
//!	@note	:	example
//=======================================================================================
class BlockSystem : public INode
{
public:
	BlockSystem(INode* parent);
	virtual ~BlockSystem();

	
	void Update();
	void Start();
	bool CreateStageBlocks(U32 row, U32 column, Graphics::IShaderObject* shader);
	bool Clear();

	void DeleteBlock(Collision::ICollisonObject* obj);
	void SetBall(Ball* ball);
	

private:
	std::vector<Block*>			m_BlockList;
	Ball*	m_Ball;

};

};
//===============================================================
//	End of File
//===============================================================