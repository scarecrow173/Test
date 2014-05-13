//=======================================================================================
//!	@file	:	SquareFactory.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "GraphicsManager.h"
#include "IndexData.h"
#include <vector>

namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	SquareFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SquareFactory
{
public:
	static SquareFactory*	Create();
	static void				Destroy();
	static SquareFactory*	GetInstance();
	
	IndexData				CreateSquare(Vector3 vCenter, Vector2 size, VertexARGB color, std::vector<U32>& indexArray);

private:
	SquareFactory();
	virtual ~SquareFactory();

	static SquareFactory*	m_Instance;
	U32						m_SquareCount;

};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�擾
//!	@return		: �C���X�^���X
//-------------------------------------------------------------
inline SquareFactory* SquareFactory::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}
};
};
//===============================================================
//	End of File
//===============================================================