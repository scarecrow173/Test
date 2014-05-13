//=======================================================================================
//!	@file	:	BoxFactory.h
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//=======================================================================================
#pragma once
#include "GraphicsManager.h"
#include "IndexData.h"
#include <vector>
namespace AK
{
namespace Graphics
{
//class GraphicsManager;
//=======================================================================================
//!	@class	:	BoxFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BoxFactory
{
public:
	static BoxFactory*	Create();
	static void			Destroy();
	static BoxFactory*	GetInstance();
	
	IndexData			CreateBox(Vector3 vCenter, Vector3 size, VertexARGB color, std::vector<U32>& indexArray);

private:
	BoxFactory();
	virtual ~BoxFactory();

	static BoxFactory*	m_Instance;
	U32					m_BoxCount;
};
//=======================================================================================
//	inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�擾
//!	@return		: �C���X�^���X
//-------------------------------------------------------------
inline BoxFactory* BoxFactory::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}



};
};
//===============================================================
//	End of File
//===============================================================