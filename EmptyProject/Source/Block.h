//=======================================================================================
//!	@file	:	Block.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "GameObject.h"
#include "IndexData.h"
#include "Elements.h"
namespace AK
{

//=======================================================================================
//!	@class	:	Block
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Block : public GameObject
{
public:
	Block(INode* parent, Vector3 pos, U32 lifeCount);
	virtual ~Block();

	void	Update();
	void	Start();
	bool	Death();


protected:

private:
	U32						m_LifeCount;
	Graphics::IndexData		m_IndexData;
	Graphics::VertexARGB	m_Color;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================