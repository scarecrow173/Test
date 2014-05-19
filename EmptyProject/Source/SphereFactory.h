//=======================================================================================
//!	@file	:	SphereFactory.h
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
class GraphicsManager;
//=======================================================================================
//!	@class	:	SphereFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SphereFactory
{
public:
	
	static SphereFactory*	Create();
	static void				Destroy();
	static SphereFactory*	GetInstance();

	IndexData				CreateSphere(const Vector3 vCenter, const F32 radius, const VertexARGB color, std::vector<U32>& indexArray);
	void					AllClear();
private:
	SphereFactory();
	virtual ~SphereFactory();

	static SphereFactory*	m_Instance;
	U32						m_SphereCount;


};
//=======================================================================================
//	inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�擾
//!	@return		: �C���X�^���X
//-------------------------------------------------------------
inline SphereFactory* SphereFactory::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}



};
};
//===============================================================
//	End of File
//===============================================================