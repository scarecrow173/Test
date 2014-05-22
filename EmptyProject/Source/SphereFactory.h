//=======================================================================================
//!	@file	:	SphereFactory.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//=======================================================================================
#pragma once
#include "GraphicsManager.h"
#include "IndexData.h"
#include <vector>
#include <hash_map>
#include <string>
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
	IRenderer*				CreateSphere(const std::string& name, const VertexARGB color);
	void					AllClear();
private:
	SphereFactory();
	virtual ~SphereFactory();

	static SphereFactory*	m_Instance;
	U32						m_SphereCount;
	std::hash_map<const std::string, IRenderer*>	m_BoxResouce;

};
//=======================================================================================
//	inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: インスタンス取得
//!	@return		: インスタンス
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